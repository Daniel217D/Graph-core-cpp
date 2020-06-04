#include <QCursor>
#include "graph.h"

namespace GraphCore{

    Graph::Graph(QWidget *parent)
    {
        Q_UNUSED(parent);

    }

    Graph::~Graph()
    {
        for(Vertex* vertex : vertexies)
            delete vertex;

        for(Edge* edge : edges)
            delete edge;
    }

    Vertex& Graph::createVertex(int x, int y, VertexStyle *style)
    {
        Vertex* vertex = new Vertex(x, y, style, QString::number(vertexies.size() + 1));
        addItem(vertex);

        connect(vertex, &Vertex::startPositionChangedByMouse, this, [&](Vertex* sender){
            sender->setCursor(QCursor(Qt::ClosedHandCursor));
        });

        connect(vertex, &Vertex::positionChangedByMouse, this, [&](Vertex* sender){
            if(getAnotherVertex(sender))
                sender->setCursor(QCursor(Qt::ForbiddenCursor));
            else sender->setCursor(QCursor(Qt::ClosedHandCursor));
        });

        connect(vertex, &Vertex::endPositionChangedByMouse, this, [&](Vertex* sender){
            if(getAnotherVertex(sender))
                sender->returnPositionIfExist();
            sender->unsetCursor();
        });

        vertexies.append(vertex);
        return *vertex;
    }

    void Graph::removeVertex(Vertex &vertex)
    {
        QList<Edge*> ownedEdges = findOwnedEdges(vertex);
        for(Edge* edge : ownedEdges)
            removeEdge(*edge);
        vertexies.removeOne(&vertex);
        removeItem(&vertex);
        updateVertexNames();
    }

    Edge& Graph::createEdge(Vertex *first, Vertex *second, EdgeStyle* style)
    {
        Edge* edge = new Edge(first, second, style);
        addItem(edge);
        edges.append(edge);
        return *edge;
    }

    void Graph::removeEdge(Edge &edge)
    {
        edge.hide();
        edges.removeOne(&edge);
        removeItem(&edge);
    }

    void Graph::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsScene::mouseDoubleClickEvent(event);
        QPointF mouse_pos = event->scenePos();
        Vertex* vertex = getVertex(mouse_pos.x(), mouse_pos.y());
        if(!vertex){ //TODO: Добавить изменение стиля вершины на выделенный
            if(event->button() == Qt::LeftButton)
                createVertex(mouse_pos.x(), mouse_pos.y(), nullptr);
        } else {
            if(event->button() == Qt::RightButton)
                removeVertex(*vertex);
        }
    }

    Vertex* Graph::getAnotherVertex(const Vertex* vertex)
    {
        for(Vertex* element : vertexies){
            if (element != vertex && element != nullptr && element->getStyle() != nullptr){
                qreal radius = element->getStyle()->getRadius();
                if (abs(vertex->x() - element->x()) <= radius && abs(vertex->y() - element->y()) <= radius)
                    return element;
            }
        }
        return nullptr;
    }

    Vertex* Graph::getVertex(const int x, const int y)
    {
        for(Vertex* element : vertexies){
            if (element != nullptr && element->getStyle() != nullptr){
                qreal radius = element->getStyle()->getRadius();
                if (abs(x - element->x()) <= radius && abs(y - element->y()) <= radius)
                    return element;
            }
        }
        return nullptr;
    }

    QList<Edge*> Graph::findOwnedEdges(Vertex &vertex)
    {
        QList<Edge*> list;
        for(Edge* edge : edges){
            if(&vertex == edge->getFirst() || &vertex == edge->getSecond())
                list.append(edge);
        }
        return list;
    }

    void Graph::updateVertexNames()
    {
        int index = 0;
        for(Vertex* vertex : vertexies){
            vertex->setName(QString::number(++index));
        }
    }
}
