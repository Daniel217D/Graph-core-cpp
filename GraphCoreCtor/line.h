#ifndef LINE_H
#define LINE_H

#include "data.h"

namespace GraphCore
{
    class Line : public QObject, public QGraphicsLineItem
    {

    public:
        explicit Line(EdgeStyle* style = nullptr, EdgeDirection direction = EdgeDirection::All, QObject *parent = nullptr);

        EdgeStyle* getStyle() const;
        void setStyle(EdgeStyle* value);
        EdgeDirection getDirection() const;
        void setDirection(const EdgeDirection &value);
        void setPoint(Vertex *value);

    private:
        EdgeStyle* style;
        EdgeDirection direction;
        Vertex* point;

        /*!
         * \brief Отрисовывает объект.
         * \param painter Рисовальщик.
         * \param option Опции.
         * \param widget Виджет.
         */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    };
}

#endif // LINE_H
