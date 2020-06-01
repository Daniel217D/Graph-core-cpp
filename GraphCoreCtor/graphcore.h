#ifndef GRAPHCORE_H
#define GRAPHCORE_H

#include "vertex.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

namespace GraphCore{

    class Graph : public QGraphicsScene
    {
        Q_OBJECT

    public:
        explicit Graph(QWidget *parent = nullptr);
        void createVertex(int x, int y, VertexStyle* style);
        ~Graph();

    protected:
      void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    private:
      QList<Vertex*> vertexies;

    };

}

#endif // GRAPHCORE_H
