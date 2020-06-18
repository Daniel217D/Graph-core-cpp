#include "line.h"

namespace GraphCore
{
    Line::Line(EdgeStyle* style, EdgeDirection direction, QObject* parent)
        : QObject(parent), QGraphicsLineItem()
    {
        setZValue(2);
        point = nullptr;
        this->setLine(0, 0, 0, 0);
        hide();
        this->direction = direction;
        this->style = style;

        if(this->style == nullptr)
            this->style = new EdgeStyle(3, Qt::black, 10, 0.45); //FIXME
    }

    EdgeStyle *Line::getStyle() const
    {
        return style;
    }

    void Line::setPoint(Vertex *value)
    {
        if (value != nullptr){
            point = value;
            this->setLine(point->x(), point->y(), point->x(), point->y());

            connect(point, &Vertex::lineChanged, this, [&](Vertex* sender, const int x, const int y){
                Q_UNUSED(sender);
                this->setLine(point->x(), point->y(), x, y);
            });

        } else hide();
    }

    EdgeDirection Line::getDirection() const
    {
        return direction;
    }

    void Line::setDirection(const EdgeDirection &value)
    {
        direction = value;
        update();
    }

    void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        EdgeStyle* ptr_style = getStyle();

        if(ptr_style != nullptr){
            EdgeStyle style = *ptr_style;
            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->setPen(QPen(style.getColor(), style.getDiameter()));
            painter->drawLine(line());
        }
    }
}
