#include "edge.h"

namespace GraphCore
{

    Edge::Edge(Vertex *first, Vertex *second, QObject *parent)
        : QObject(parent), QGraphicsItem() //FIXME
    {
        this->first = first;
        this->second = second;
        connect(first, &Vertex::positionChanged, this, &Edge::updateLine);\
        connect(second, &Vertex::positionChanged, this, &Edge::updateLine);
    }

    Edge::~Edge()
    {

    }

    void Edge::updateLine()
    {
        update();
    }

    QRectF Edge::boundingRect() const
    {
        //Желательно переосмыслить...
        return QRectF(first->x(), first->y(), second->x(), second->y());
    }

    void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        auto sizes = boundingRect();

        painter->setPen(QPen(Qt::black, 3));
        painter->drawLine(sizes.x(), sizes.y(), sizes.width(), sizes.height());
    }
}
