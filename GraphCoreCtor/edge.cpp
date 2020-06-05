#include "edge.h"
#include "QtMath"

namespace GraphCore
{

    EdgeStyle::EdgeStyle(qreal diameter, Qt::GlobalColor color)
    {
        this->diameter = diameter;
        this->color = color;
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

    Edge::Edge(Vertex *first, Vertex *second, EdgeStyle* style, QObject *parent)
        : QObject(parent), QGraphicsItem() //FIXME
    {
        this->first = first;
        this->second = second;
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
           this->style = new EdgeStyle(3, Qt::black);
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

    void printArrow(QPainter *painter, float startX, float startY, float endX, float endY)
    {
        float lons, angle;

        const float ostr = 0.45;        // острота стрелки

        painter->drawLine(startX, startY, endX, endY);

        lons = 10;     // длина лепестков % от длины стрелки
        angle = atan2(endY - startY, endX - startX);             // угол наклона линии

        for(int i = -1; i < 2; i += 2){
            painter->drawLine(endX,
                              endY,
                              endX - lons * cos(angle + i * ostr),
                              endY - lons * sin(angle + i * ostr));
        }
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
            qreal xEnd = sizes.width();
            qreal yEnd = sizes.height();
            switch(getQuarter()){
                case 1:
                    this->setPos(first->x(), second->y());
                    printArrow(painter, 0, yEnd, xEnd, 0); //F->S
                    printArrow(painter, xEnd, 0, 0, yEnd); //S->F
                    break;
                case 2:
                    this->setPos(second->x(), second->y());
                    printArrow(painter, xEnd, yEnd, 0, 0); //F->S
                    printArrow(painter, 0, 0, xEnd, yEnd); //S->F
                    break;
                case 3:
                    this->setPos(second->x(), first->y());
                    printArrow(painter, xEnd, 0, 0, yEnd); //F->S
                    printArrow(painter, 0, yEnd, xEnd, 0); //S->F
                    break;
                case 4:
                    this->setPos(first->x(), first->y());
                    printArrow(painter, 0, 0, xEnd, yEnd);  //F->S
                    printArrow(painter, xEnd, yEnd, 0, 0);  //S->F
                    break;
            }
        }
    }
    
}
