#include "graphcore.h"

namespace GraphCore{

    Graph::Graph(QWidget *parent)
    {

    }

    Vertex& Graph::createVertex(int x, int y, VertexStyle *style)
    {
        Vertex* vertex = new Vertex(x, y, style);
        addItem(vertex);
        vertexies.append(vertex);
        return *vertex;
    }

    Edge& Graph::createEdge(Vertex *first, Vertex *second)
    {
        Edge* edge = new Edge(first, second);
        addItem(edge);
        first->update();
        second->update();
        edges.append(edge);
        return *edge;
    }

    Graph::~Graph()
    {
        for(Vertex* vertex : vertexies){
            delete vertex;
        }
    }

    void Graph::mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsScene::mousePressEvent(event);
        QPointF mouse_pos = event->scenePos();
        if(this->itemAt(mouse_pos, QTransform()) == nullptr){
            createVertex(mouse_pos.x(), mouse_pos.y(), nullptr);
        }
    }

}
