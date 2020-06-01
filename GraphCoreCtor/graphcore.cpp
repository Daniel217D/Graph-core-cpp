#include "graphcore.h"

namespace GraphCore{

    Graph::Graph(QWidget *parent)
    {

    }

    void Graph::createVertex(int x, int y, VertexStyle *style)
    {
        Vertex* vertex = new Vertex(x, y, style);
        addItem(vertex);
        vertexies.append(vertex);
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
