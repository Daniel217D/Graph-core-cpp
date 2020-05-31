#ifndef VERTEX_H
#define VERTEX_H

#include <QPainter>
#include <QBrush>

#include "graphcore.h"

namespace GraphCore{

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

    class Graph;

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

}

#endif // VERTEX_H
