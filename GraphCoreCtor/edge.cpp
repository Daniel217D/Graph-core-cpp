#include "edge.h"
#include "QtMath"

namespace GraphCore
{

    EdgeStyle::EdgeStyle(qreal diameter, Qt::GlobalColor color, qreal arrowLength, qreal arrowAngle)
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

    Qt::GlobalColor EdgeStyle::getColor() const
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

    Edge::Edge(Vertex *first, Vertex *second, EdgeDirection direction, EdgeStyle* style, QObject *parent)
        : QObject(parent), QGraphicsItem()
    {
        this->first = first;
        this->second = second;
        this->direction = direction;
        this->style = style;

        if (first != nullptr)
            connect(first, &Vertex::positionChangedByMouse, this, [&](){
                update();
            });

        if (second != nullptr)
            connect(second, &Vertex::positionChangedByMouse, this, [&](){
                update();
            });

        if(this->style == nullptr)
           this->style = new EdgeStyle(3, Qt::black, 10, 0.45); //FIXME
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
            return 0;
        if (first->x() <= second->x() && first->y() <= second->y())
            return 4;
        else if (first->x() > second->x() && first->y() > second->y())
            return 2;
        else if(first->x() <= second->x() && first->y() >= second->y())
            return 1;
        else return 3;
    }

    QRectF Edge::boundingRect() const
    {
        auto width = abs(first->x() - second->x());
        auto height = abs(first->y() - second->y());

        return QRectF(0, 0, width, height);
    }

    void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        QRectF sizes = boundingRect();
        EdgeStyle* ptr_style = getStyle();
        if(ptr_style != nullptr){
            EdgeStyle style = *ptr_style;
            painter->setPen(QPen(style.getColor(), style.getDiameter()));

            int quarter = getQuarter() - 1; //TODO: Проверка на 0 (не хватает какой-то вершины)
            bool firstBit = quarter & 1;
            bool secondBit = quarter >> 1;

            qreal startX = firstBit ^ secondBit ? sizes.width() : 0;
            qreal startY = secondBit ? 0 : sizes.height();
            qreal endX = firstBit ^ secondBit ? 0 : sizes.width();
            qreal endY = secondBit ? sizes.height() : 0;

            this->setPos(firstBit ^ secondBit ? second->x() : first->x(),
                         secondBit ? first->y() : second->y());

            painter->drawLine(startX, startY, endX, endY);

            if (getDirection() == EdgeDirection::All || getDirection() == EdgeDirection::ToSecond)
            {
                double angle = atan2(endY - startY, endX - startX);
                for(int i = -1; i < 2; i += 2)
                    painter->drawLine(endX,
                                      endY,
                                      endX - style.getArrowLength() * cos(angle + i * style.getArrowAngle()),
                                      endY - style.getArrowLength() * sin(angle + i * style.getArrowAngle()));
            }

            if (getDirection() == EdgeDirection::All || getDirection() == EdgeDirection::ToFirst){
            double angle = atan2(startY - endY, startX - endX);
                for(int i = -1; i < 2; i += 2)
                    painter->drawLine(startX,
                                      startY,
                                      startX - style.getArrowLength() * cos(angle + i * style.getArrowAngle()),
                                      startY - style.getArrowLength() * sin(angle + i * style.getArrowAngle()));
            }
        }
    }

    void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        if (isLine(event->pos().x(), event->pos().y())){
            if(event->button() == Qt::LeftButton)
                needDirectionChanged(this);
            else if (event->button() == Qt::RightButton)
                needDestruction(this);
        }
    }

    bool Edge::isLine(const int x, const int y)
    {
        auto realCoords = mapToScene(QPointF(x, y));
        auto expectedY = (realCoords.x() - first->x()) * (second->y() - first->y()) / (second->x() - first->x()) + first->y();
        return abs(expectedY  - realCoords.y()) <= style->getDiameter();
    }
    
}
