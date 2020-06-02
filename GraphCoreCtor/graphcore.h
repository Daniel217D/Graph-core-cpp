#ifndef GRAPHCORE_H
#define GRAPHCORE_H

#include "edge.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

namespace GraphCore{

    class Graph : public QGraphicsScene
    {
        //Q_OBJECT

    public:
        explicit Graph(QWidget *parent = nullptr);
        Vertex& createVertex(int x, int y, VertexStyle* style);
        Edge& createEdge(Vertex* first, Vertex* second, EdgeStyle* style);
        ~Graph();

    protected:
      void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    private:
      QList<Vertex*> vertexies;
      QList<Edge*> edges;
    };

}

#endif // GRAPHCORE_H
