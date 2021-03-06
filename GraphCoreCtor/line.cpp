#include "line.h"

namespace GraphCore
{
    Line::Line(EdgeStyle* style, EdgeDirection direction, bool isOriented, QObject* parent)
        : QObject(parent), QGraphicsLineItem()
    {
        setZValue(2);

        this->point = nullptr;
        this->setLine(0, 0, 0, 0);
        this->direction = direction;
        this->style = style;
        this->isOriented = isOriented;

        hide();
    }

    Line::~Line()
    {

    }

    EdgeStyle *Line::getStyle() const
    {
        return style;
    }

    void Line::setStyle(EdgeStyle *value)
    {
        style = value;
        update();
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

    bool Line::getOriented() const
    {
        return isOriented;
    }

    void Line::setOriented(bool value)
    {
        isOriented = value;
        update();
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
