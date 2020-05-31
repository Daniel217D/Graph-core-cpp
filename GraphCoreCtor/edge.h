#ifndef EDGE_H
#define EDGE_H

#include "graphcore.h"

namespace GraphCore{

    enum class EdgeDirection{
        None,
        ToFirst,
        ToSecond,
        All
    };

    class Edge : public QObject, public QGraphicsItem{
        Q_OBJECT

    public:
        Edge(Graph& owner, Vertex& vertex, QObject *parent = nullptr);
        Edge(Graph& owner, Vertex& first, Vertex& second, QObject *parent = nullptr);
        EdgeDirection getDirection() const;
        void setDirection(const EdgeDirection &value);

    private:
        EdgeDirection direction;
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    };

}

#endif // EDGE_H
