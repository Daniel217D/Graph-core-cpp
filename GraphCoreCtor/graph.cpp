#include <QCursor>
#include "graph.h"

namespace GraphCore{

    Graph::Graph(Theme& theme, bool isOriented, QWidget *parent)
    {
        Q_UNUSED(parent);

        this->theme = &theme;
        setBackgroundBrush(this->theme->getGraphBackground());
        this->isOriented = isOriented;
        line = new Line(this->theme->getDefaultEdgeStyle());

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

        //vertex.deleteLater(); //Удаление кладет память X(

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

        //edge.deleteLater(); //Удаление кладет память X(
    }

    void Graph::createAdjacencyMatrix(bool**& matrix, int& length)
    {
        QVector<Vertex*> vertexies = this->vertexies.toVector();
        length = vertexies.size();

        matrix = new bool*[length];
        for(int i = 0; i < length; ++i){
            matrix[i] = new bool[length];
            memset(matrix[i], 0, length * sizeof(bool));
        }

        for(int i = 0; i < length; ++i)
            for(Edge* edge : edges)
                if(vertexies[i] == edge->getFirst()
                        && (!isOriented || edge->getDirection() == EdgeDirection::All || edge->getDirection() == EdgeDirection::ToSecond)){
                   int j = vertexies.indexOf(edge->getSecond());
                   matrix[i][j] = true;
                } else if (vertexies[i] == edge->getSecond()
                           && (!isOriented || edge->getDirection() == EdgeDirection::All || edge->getDirection() == EdgeDirection::ToFirst)){
                    int j = vertexies.indexOf(edge->getFirst());
                    matrix[i][j] = true;
                }
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

    void Graph::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsScene::mouseDoubleClickEvent(event);
        QPointF mouse_pos = event->scenePos();
        Vertex* vertex = getVertex(mouse_pos.x(), mouse_pos.y());
        if(!vertex){
            if(event->button() == Qt::LeftButton)
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

        for(Edge* edge : edges){
            edge->setOriented(isOriented);
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
}
