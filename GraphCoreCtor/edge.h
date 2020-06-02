#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

namespace GraphCore
{

    class Edge : public QObject, public QGraphicsItem
    {
        Q_OBJECT

    public:
        explicit Edge(Vertex* first, Vertex* second = nullptr, QObject *parent = nullptr);
        ~Edge();

    private slots:
        void updateLine();

    private:
        Vertex* first;
        Vertex* second;

        int getQuarter() const;
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    };

}

#endif // EDGE_H
