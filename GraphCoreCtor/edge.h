#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

namespace GraphCore
{

    class EdgeStyle
    {

    public:
        explicit EdgeStyle(qreal diameter = 0.,
                             Qt::GlobalColor color = Qt::black);
        ~EdgeStyle();
        inline qreal getDiameter() const;
        inline Qt::GlobalColor getColor() const;

    private:
        qreal diameter;
        Qt::GlobalColor color;
    };

    class Edge : public QObject, public QGraphicsItem
    {
        Q_OBJECT

    public:
        explicit Edge(Vertex* first, Vertex* second = nullptr, EdgeStyle* style = nullptr, QObject *parent = nullptr);
        ~Edge();
        EdgeStyle* getStyle() const;
        void setStyle(EdgeStyle* value);

    private:
        Vertex* first;
        Vertex* second;
        EdgeStyle* style;

        int getQuarter() const;
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    };

}

#endif // EDGE_H
