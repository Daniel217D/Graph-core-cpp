#include "edge.h"

namespace GraphCore
{

    EdgeStyle::EdgeStyle(qreal diameter, QColor color, qreal arrowLength, qreal arrowAngle)
    {
        this->diameter = diameter;
        this->color = color;
        this->arrowLength = arrowLength;
        this->arrowAngle = arrowAngle;
    }

    EdgeStyle::~EdgeStyle()
    {

    }

    qreal EdgeStyle::getDiameter() const
    {
        return diameter;
    }

    QColor EdgeStyle::getColor() const
    {
        return color;
    }

    qreal EdgeStyle::getArrowLength() const
    {
        return arrowLength;
    }

    qreal EdgeStyle::getArrowAngle() const
    {
        return arrowAngle;
    }

    Edge::Edge(Vertex *first, Vertex *second, EdgeDirection direction, EdgeStyle* style, bool isOriented, QObject *parent)
        : QObject(parent), QGraphicsLineItem()
    {
        setZValue(0);
        this->first = first;
        this->second = second;
        this->direction = direction;
        this->style = style;
        this->isOriented = isOriented;

        this->setLine(first->x(), first->y(), second->x(), second->y());

        if (first != nullptr)
            connect(first, &Vertex::positionChangedByMouse, this, [&](Vertex* sender, int x, int y){
                Q_UNUSED(sender);
                this->setLine(x, y, this->line().p2().x(), this->line().p2().y());
            });

        if (second != nullptr)
            connect(second, &Vertex::positionChangedByMouse, this, [&](Vertex* sender, int x, int y){
                Q_UNUSED(sender);
                this->setLine(this->line().p1().x(), this->line().p1().y(), x, y);
            });
    }

    Edge::~Edge()
    {

    }

    EdgeStyle* Edge::getStyle() const
    {
        return style;
    }

    void Edge::setStyle(EdgeStyle *value)
    {
        style = value;
        update();
    }
    
    Vertex* Edge::getFirst() const
    {
        return first;
    }
    
    Vertex* Edge::getSecond() const
    {
        return second;
    }

    bool Edge::getOriented() const
    {
        return isOriented;
    }

    void Edge::setOriented(bool value)
    {
        isOriented = value;
        update();
    }

    EdgeDirection Edge::getDirection() const
    {
        return direction;
    }

    void Edge::setDirection(const EdgeDirection &value)
    {
        direction = value;
        update();
    }
    
    int Edge::getQuarter() const
    {
        if (first == nullptr || second == nullptr)
            return -1;
        if (first->x() <= second->x() && first->y() <= second->y())
            return 3;
        else if (first->x() > second->x() && first->y() > second->y())
            return 1;
        else if(first->x() <= second->x() && first->y() >= second->y())
            return 0;
        else return 2;
    }

    qreal Edge::getTiltAngle() const
    {
        return (second->y() - first->y()) / (second->x() - first->x());
    }

    void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        EdgeStyle* ptr_style = getStyle();

        if(ptr_style != nullptr){
            EdgeStyle style = *ptr_style;
            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->setPen(QPen(style.getColor(), style.getDiameter()));
            painter->drawLine(line());

            if (isOriented && (getDirection() == EdgeDirection::All || getDirection() == EdgeDirection::ToSecond))
            {
                double angle = atan2(line().p2().y() - line().p1().y(), line().p2().x() - line().p1().x());
                for(int i = -1; i < 2; i += 2)
                    painter->drawLine(line().p2().x(),
                                      line().p2().y(),
                                      line().p2().x() - style.getArrowLength() * cos(angle + i * style.getArrowAngle()),
                                      line().p2().y() - style.getArrowLength() * sin(angle + i * style.getArrowAngle()));
            }

            if (isOriented && (getDirection() == EdgeDirection::All || getDirection() == EdgeDirection::ToFirst)){
            double angle = atan2(line().p1().y() - line().p2().y(), line().p1().x() - line().p2().x());
                for(int i = -1; i < 2; i += 2)
                    painter->drawLine(line().p1().x(),
                                      line().p1().y(),
                                      line().p1().x() - style.getArrowLength() * cos(angle + i * style.getArrowAngle()),
                                      line().p1().y() - style.getArrowLength() * sin(angle + i * style.getArrowAngle()));
            }
        }
    }

    void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
            if(event->button() == Qt::LeftButton)
                needDirectionChanged(this);
            else if (event->button() == Qt::RightButton)
                needDestruction(this);
    }

    QLineF Edge::line() const
        {
            int quarter = getQuarter();

            if (quarter > -1){
                QPointF touchPointStart = getTouchPoint(first->getStyle()->getRadius());
                QPointF touchPointEnd = getTouchPoint(second->getStyle()->getRadius());

                switch(quarter){
                    case 0:
                    return QLineF(this->first->x() - touchPointStart.x(),
                                  this->first->y() + touchPointStart.y(),
                                  this->second->x() + touchPointEnd.x(),
                                  this->second->y() - touchPointEnd.y());
                    case 1:
                    return QLineF(this->first->x() + touchPointStart.x(),
                                  this->first->y() - touchPointStart.y(),
                                  this->second->x() - touchPointEnd.x(),
                                  this->second->y() + touchPointEnd.y());
                    case 2:
                    return QLineF(this->first->x() + touchPointStart.x(),
                                  this->first->y() - touchPointStart.y(),
                                  this->second->x() - touchPointEnd.x(),
                                  this->second->y() + touchPointEnd.y());
                    case 3:
                    return QLineF(this->first->x() - touchPointStart.x(),
                                  this->first->y() + touchPointStart.y(),
                                  this->second->x() + touchPointEnd.x(),
                                  this->second->y() - touchPointEnd.y());
                }
            }

            return QLineF(0, 0, 0, 0);
        }

    QPointF Edge::getTouchPoint(qreal radix) const{
         //Прямая проходящая через вершины (в общем виде)
         qreal a = getTiltAngle();
         const qreal b = -1;
         const qreal c = 0;

         if (a != INFINITY && a != -INFINITY){
             //Расстояние точек пересечения до ближайшей к центру окружности точки
             qreal d = sqrt(radix * radix - (c * c / (a * a + b * b)));

             //Точки пересечения
             qreal mult = sqrt(d * d / (a * a + b * b));
             qreal x = b * mult;
             qreal y = a * mult;

             return QPointF(x, y);
         } else return QPointF(0, a > 0 ? radix : -radix);
    }
    
}
