#include "edge.h"

namespace GraphCore
{

    Edge::Edge(Vertex *first, Vertex *second, QObject *parent)
        : QObject(parent), QGraphicsItem() //FIXME
    {
        this->first = first;
        this->second = second;
        connect(first, &Vertex::positionChanged, this, &Edge::updateLine);\
        connect(second, &Vertex::positionChanged, this, &Edge::updateLine);
    }

    Edge::~Edge()
    {

    }

    void Edge::updateLine()
    {
        update();
    }

    int Edge::getQuarter() const
    {
        if (first->x() <= second->x() && first->y() <= second->y())
            return 4;
        else if (first->x() > second->x() && first->y() > second->y())
            return 2;
        else if(first->x() <= second->x() && first->y() >= second->y())
            return 1;
        else return 3;
    }

    QRectF Edge::boundingRect() const
    {
        auto width = abs(first->x() - second->x());
        auto height = abs(first->y() - second->y());

        return QRectF(0, 0, width, height);
    }

    void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        auto sizes = boundingRect();

        painter->setPen(QPen(Qt::black, 3));
        switch(getQuarter()){
            case 1:
                this->setPos(first->x(), second->y());
                painter->drawLine(0, sizes.height(), sizes.width(), 0);
                break;
            case 2:
                this->setPos(second->x(), second->y());
                painter->drawLine(0, 0, sizes.width(), sizes.height());
                break;
            case 3:
                this->setPos(second->x(), first->y());
                painter->drawLine(sizes.width(), 0, 0, sizes.height());
                break;
            case 4:
                this->setPos(first->x(), first->y());
                painter->drawLine(0, 0, sizes.width(), sizes.height());
                break;
        }
    }
}
