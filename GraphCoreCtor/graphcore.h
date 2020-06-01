#ifndef GRAPHCORE_H
#define GRAPHCORE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsView>

namespace GraphCore{

class Graph;

class VertexStyle{

public:
    explicit VertexStyle(double radius = 0.,
                         Qt::GlobalColor backgroundColor = Qt::white,
                         double circuitPercent = 0,
                         Qt::GlobalColor circuitColor = Qt::black,
                         Qt::GlobalColor textColor = Qt::black);
    ~VertexStyle();
    double getRadius() const;
    Qt::GlobalColor getBackgroundColor() const;
    double getCircuitPercent() const;
    Qt::GlobalColor getCircuitColor() const;
    Qt::GlobalColor getTextColor() const;

private:
    double radius;
    Qt::GlobalColor backgroundColor;
    double circuitPercent;
    Qt::GlobalColor circuitColor;
    Qt::GlobalColor textColor;
};

class Vertex : public QObject, public QGraphicsItem{
    Q_OBJECT

public:
    //circuit нужно передать по ссылке, но терять инициализатор как-то не хочется
    explicit Vertex(Graph& owner, int x = 0, int y = 0, QObject *parent = nullptr);
    ~Vertex();
    int getX() const;
    void setX(int value);
    int getY() const;
    void setY(int value);
    const QString getName();
    const VertexStyle& getStyle() const;

private:
    Graph& graph;
    int x;
    int y;

    static QRectF generateDescribedSquare(double centerX, double centerY, double radius);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

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

class Graph : public QGraphicsView {
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();
    int getVertexID(const Vertex* vertex);
    const VertexStyle& getVertexStyle(const Vertex* vertex);
    Vertex& createVertex(int x = 0, int y = 0, int radius = 0, VertexStyle circuit = VertexStyle(0, Qt::black), Qt::GlobalColor textColor = Qt::black);
    bool deleteVertex(const Vertex& vertex);

private:
    const VertexStyle DEFAULT_STYLE = VertexStyle(20., Qt::white, 10., Qt::blue, Qt::black);
    QGraphicsScene* scene;
    //std::list<Vertex> vertices;
    //std::list<Edge> edges;
};

}
#endif // GRAPHCORE_H
