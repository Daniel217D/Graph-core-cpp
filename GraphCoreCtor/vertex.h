#ifndef VERTEX_H
#define VERTEX_H

#include <QObject>
#include <QPainter>
#include <QGraphicsItem>

namespace GraphCore
{

    class VertexStyle
    {

    public:
        explicit VertexStyle(qreal radius = 0.,
                             Qt::GlobalColor backgroundColor = Qt::white,
                             qreal circuitPercent = 0,
                             Qt::GlobalColor circuitColor = Qt::black,
                             Qt::GlobalColor textColor = Qt::black);
        ~VertexStyle();
        inline qreal getRadius() const;
        inline Qt::GlobalColor getBackgroundColor() const;
        inline qreal getCircuitPercent() const;
        inline Qt::GlobalColor getCircuitColor() const;
        inline Qt::GlobalColor getTextColor() const;

    private:
        qreal radius;
        Qt::GlobalColor backgroundColor;
        qreal circuitPercent;
        Qt::GlobalColor circuitColor;
        Qt::GlobalColor textColor;
    };

    class Vertex : public QObject, public QGraphicsItem
    {
        Q_OBJECT

    public:
        explicit Vertex(int centerX = 0, int centerY = 0, VertexStyle* style = nullptr, QObject *parent = nullptr);
        ~Vertex();
        VertexStyle* getStyle() const;
        void setStyle(VertexStyle* value);
        QString getName() const;

    private:
        VertexStyle* style;
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    };

}

#endif // VERTEX_H
