#ifndef VERTEX_H
#define VERTEX_H

#include<windows.h>
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>

namespace GraphCore{

    class VertexCircuit{

    public:
        explicit VertexCircuit(double percent = 0, Qt::GlobalColor color = Qt::black);
        ~VertexCircuit();
        double getPercent();
        void setPercent(double value);
        Qt::GlobalColor getColor();
        void setColor(Qt::GlobalColor& value);

    private:
        Qt::GlobalColor color;
        double percent;
    };

    class Vertex : public QObject, public QGraphicsItem{
        Q_OBJECT

    public:
        //circuit нужно передать по ссылке, но терять инициализатор как-то не хочется
        explicit Vertex(int x = 0, int y = 0, int radius = 0, VertexCircuit circuit = VertexCircuit(0, Qt::black), Qt::GlobalColor textColor = Qt::black, QObject *parent = nullptr);
        ~Vertex();
        QString getName();

    private:
        GUID id;
        int x;
        int y;
        double radius;
        VertexCircuit circuit;
        Qt::GlobalColor textColor;

        static QRectF generateDescribedSquare(double centerX, double centerY, double radius);
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    };

}

#endif // VERTEX_H
