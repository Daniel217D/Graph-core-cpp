#include <QCursor>
#include "graph.h"

namespace GraphCore{

    Graph::Graph(QWidget *parent)
    {
        Q_UNUSED(parent);

    }

    Graph::~Graph()
    {
        for(Vertex* vertex : vertexies){
            delete vertex;
        }

        for(Edge* edge : edges){
            delete edge;
        }
    }

    Vertex& Graph::createVertex(int x, int y, VertexStyle *style)
    {
        Vertex* vertex = new Vertex(x, y, style);
        addItem(vertex);

        connect(vertex, &Vertex::startPositionChangedByMouse, this, [&](Vertex* sender){
            sender->setCursor(QCursor(Qt::ClosedHandCursor));
        });

        connect(vertex, &Vertex::positionChangedByMouse, this, [&](Vertex* sender){
            if(hasAnotherVertex(sender))
                sender->setCursor(QCursor(Qt::ForbiddenCursor));
            else sender->setCursor(QCursor(Qt::ClosedHandCursor));
        });

        connect(vertex, &Vertex::endPositionChangedByMouse, this, [&](Vertex* sender){
            if(hasAnotherVertex(sender))
                sender->returnPositionIfExist();
            sender->unsetCursor();
        });

        vertexies.append(vertex);
        return *vertex;
    }

    Edge& Graph::createEdge(Vertex *first, Vertex *second, EdgeStyle* style)
    {
        Edge* edge = new Edge(first, second, style);
        addItem(edge);
        edges.append(edge);
        return *edge;
    }

    void Graph::mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsScene::mousePressEvent(event);
        QPointF mouse_pos = event->scenePos();
        if(this->itemAt(mouse_pos, QTransform()) == nullptr){
            createVertex(mouse_pos.x(), mouse_pos.y(), nullptr);
        }
    }

    bool Graph::hasAnotherVertex(const Vertex* vertex)
    {
        for(Vertex* element : vertexies){
            if (element != vertex && element != nullptr && element->getStyle() != nullptr){
                qreal radius = element->getStyle()->getRadius();
                if (abs(vertex->x() - element->x()) <= radius && abs(vertex->y() - element->y()) <= radius)
                    return true;
            }
        }
        return false;
    }
}
