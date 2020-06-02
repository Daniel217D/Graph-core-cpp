#include "edge.h"

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
            connect(first, &Vertex::positionChanged, this, &Edge::updateLine);
        if (second != nullptr)
            connect(second, &Vertex::positionChanged, this, &Edge::updateLine);
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
    }

    void Edge::updateLine()
    {
        update();
    }

    int Edge::getQuarter() const
    {
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
            switch(getQuarter()){
                case 1:
                    this->setPos(first->x(), second->y());
                    painter->drawLine(0, sizes.height(), sizes.width(), 0);
                    break;
                case 2:
                    this->setPos(second->x(), second->y());
                    painter->drawLine(0, 0, sizes.width(), sizes.height());
                    break;
                case 3:
                    this->setPos(second->x(), first->y());
                    painter->drawLine(sizes.width(), 0, 0, sizes.height());
                    break;
                case 4:
                    this->setPos(first->x(), first->y());
                    painter->drawLine(0, 0, sizes.width(), sizes.height());
                    break;
            }
        }
    }
    
}
