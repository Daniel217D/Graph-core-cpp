#include "edge.h"
#include "vertex.h"
#include "graph.h"

namespace GraphCore{

    Edge::Edge(Graph &owner, Vertex &vertex, QObject *parent)
        : QObject(parent), QGraphicsItem()
    {

    }

    Edge::Edge(Graph &owner, Vertex &first, Vertex &second, QObject *parent)
        : QObject(parent), QGraphicsItem()
    {

    }

    EdgeDirection Edge::getDirection() const
    {
        return this->direction;
    }

    void Edge::setDirection(const EdgeDirection &value)
    {
        this->direction = value;
    }

    QRectF Edge::boundingRect() const
    {

    }

    void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {

    }

}
