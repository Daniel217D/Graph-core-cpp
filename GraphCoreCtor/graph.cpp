#include <QCursor>
#include "graph.h"

namespace GraphCore{

    Graph::Graph(Theme& theme, bool isOriented, QWidget *parent)
    {
        Q_UNUSED(parent);

        this->theme = &theme;
        setBackgroundBrush(this->theme->getGraphBackground());
        this->isOriented = isOriented;
        line = new Line(this->theme->getDefaultEdgeStyle(), EdgeDirection::All, isOriented);

        addItem(line);
    }

    Graph::~Graph()
    {
        line->deleteLater();

        for(Vertex* vertex : vertexies)
            vertex->deleteLater();

        for(Edge* edge : edges)
            edge->deleteLater();
    }

    Vertex& Graph::createVertex(int x, int y)
    {
        Vertex* vertex = new Vertex(x, y, getTheme()->getDefaultVertexStyle(), QString::number(vertexies.size() + 1));
        addItem(vertex);

        connect(vertex, &Vertex::startPositionChangedByMouse, this, [&](Vertex* sender){
            sender->setCursor(QCursor(Qt::ClosedHandCursor));
        });

        connect(vertex, &Vertex::positionChangedByMouse, this, [&](Vertex* sender){
            if(getAnotherVertex(sender))
                sender->setCursor(QCursor(Qt::ForbiddenCursor));
            else sender->setCursor(QCursor(Qt::ClosedHandCursor));
            update(); //FIXME
        });

        connect(vertex, &Vertex::endPositionChangedByMouse, this, [&](Vertex* sender){
            if(getAnotherVertex(sender))
                sender->returnPositionIfExist();
            sender->unsetCursor();
        });

        connect(vertex, &Vertex::startDrawingArrow, this, [&](Vertex* sender){
            line->setPoint(sender);
            line->show();
        });

        connect(vertex, &Vertex::endDrawingArrow, this, [&](Vertex* sender){
            QLineF temp = line->line();
            line->setPoint(nullptr);
            Vertex* vertex = getVertex(temp.x2(), temp.y2());
            if (vertex && sender != vertex && !edgeExist(*sender, *vertex))
                createEdge(sender, vertex, line->getDirection());
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

        vertex.deleteLater();

        line->setPoint(nullptr);
        line->hide();

        updateVertexNames();
    }

    Edge& Graph::createEdge(Vertex *first, Vertex *second, EdgeDirection direction)
    {
        Edge* edge = new Edge(first, second, direction, getTheme()->getDefaultEdgeStyle(), isOriented);
        addItem(edge);

        connect(edge, &Edge::needDirectionChanged, this, [&](Edge* sender){
            if (isOriented){
                sender->setDirection(static_cast<EdgeDirection>((static_cast<int>(sender->getDirection()) + 1) % 3));
            }
        });

        connect(edge, &Edge::needDestruction, this, [&](Edge* sender){
            removeEdge(*sender);
        });

        edges.append(edge);
        return *edge;
    }

    void Graph::removeEdge(Edge &edge)
    {
        edge.hide();
        edges.removeOne(&edge);

        removeItem(&edge);

        edge.deleteLater();
    }

    void Graph::removeAll()
    {
        for(Vertex* vertex : vertexies)
            removeVertex(*vertex);

        for(Edge* edge : edges)
            removeEdge(*edge);
    }

    Theme *Graph::getTheme() const
    {
        return theme;
    }

    void Graph::setTheme(Theme *value)
    {
        theme = value;

        setBackgroundBrush(this->theme->getGraphBackground());

        line->setStyle(value->getDefaultEdgeStyle());

        for(Vertex* vertex : vertexies){
            vertex->setStyle(theme->getDefaultVertexStyle());
        }

        for(Edge* edge : edges){
            edge->setStyle(theme->getDefaultEdgeStyle());
        }
    }

    Vertex* Graph::getVertexByName(QString name)
    {
        for(Vertex* vertex : vertexies)
            if (vertex->getName() == name)
                return vertex;
        return nullptr;
    }

    void Graph::selectVertex(QStringList* names){
        if (names != nullptr){
            for(QString& name : *names){
                Vertex* vertex = getVertexByName(name);
                if (vertex != nullptr)
                    vertex->setStyle(theme->getHighlightedVertexStyle());
            }
        } else {
            for(Vertex* vertex : vertexies)
                vertex->setStyle(theme->getHighlightedVertexStyle());
        }
    }

    void Graph::deselectVertex(QStringList* names){
        if (names != nullptr){
            for(QString& name : *names){
                Vertex* vertex = getVertexByName(name);
                if (vertex != nullptr)
                    vertex->setStyle(theme->getDefaultVertexStyle());
            }
        } else {
            for(Vertex* vertex : vertexies)
                vertex->setStyle(theme->getDefaultVertexStyle());
        }
    }

    void Graph::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsScene::mouseDoubleClickEvent(event);
        QPointF mouse_pos = event->scenePos();
        Vertex* vertex = getVertex(mouse_pos.x(), mouse_pos.y());
        if(!vertex){
            Edge* edge = getEdge(mouse_pos.x(), mouse_pos.y(), 15.);
            if(!edge && event->button() == Qt::LeftButton)
                createVertex(mouse_pos.x(), mouse_pos.y());
        } else {
            if(event->button() == Qt::RightButton)
                removeVertex(*vertex);
        }
    }

    bool Graph::getOriented() const
    {
        return isOriented;
    }

    void Graph::setOriented(bool value)
    {
        isOriented = value;

        line->setOriented(isOriented);

        for(Edge* edge : edges){
            edge->setOriented(isOriented);
        }
    }

    GraphData& Graph::serialize() const
    {
        GraphData* data = new GraphData();

        data->isOriented = isOriented;

        QVector<Vertex*> vertexies = this->vertexies.toVector();
        data->vertexiesCount = vertexies.size();
        data->vertexiesData = new VertexData[data->vertexiesCount];
        for(auto index = 0; index < vertexies.size(); ++index){
            data->vertexiesData[index].id = index;
            data->vertexiesData[index].x = vertexies[index]->x();
            data->vertexiesData[index].y = vertexies[index]->y();
        }

        QVector<Edge*> edges = this->edges.toVector();
        data->edgesCount = edges.size();
        data->edgesData = new EdgeData[data->edgesCount];
        for(auto index = 0; index < edges.size(); ++index){
           data->edgesData[index].firstID = vertexies.indexOf(edges[index]->getFirst());
           data->edgesData[index].secondID = vertexies.indexOf(edges[index]->getSecond());
           data->edgesData[index].direction = edges[index]->getDirection();
        }

        return *data;
    }

    void Graph::deserialize(GraphData &data)
    {
        removeAll();

        isOriented = data.isOriented;

        QVector<Vertex*> vertixies(data.vertexiesCount);
        for(auto index = 0u; index < data.vertexiesCount; ++index){
            auto i = 0u;
            while(data.vertexiesData[i].id != index){
                ++i;
                if (i >= data.vertexiesCount){
                    return;
                }
                continue;
            }
            vertixies[index] = &createVertex(data.vertexiesData[i].x, data.vertexiesData[i].y);
        }

        for(auto index = 0u; index < data.edgesCount; ++index){
            createEdge(vertixies[data.edgesData[index].firstID],
                    vertixies[data.edgesData[index].secondID],
                    data.edgesData[index].direction);
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

    bool Graph::edgeExist(Vertex &first, Vertex &second)
    {
        for(Edge* edge : edges){
            if((&first == edge->getFirst() && &second == edge->getSecond())
                    || (&first == edge->getSecond() && &second == edge->getFirst()))
                return true;
        }
        return false;
    }

    Edge* Graph::getEdge(const int x, const int y, const qreal diameter){
        for(Edge* edge : edges){
            //Прямая проходящая через вершины (в общем виде)
            qreal k = edge->getTiltAngle();
            qreal b = edge->getFirst()->y() - k * edge->getFirst()->x();
            qreal ySupposed = k * x + b;
            if (abs(ySupposed - y) < diameter)
                return edge;
        }
        return nullptr;
    }
}
