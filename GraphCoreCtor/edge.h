#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

namespace GraphCore
{
    /*!
     * \brief Стиль ребра.
     */
    class EdgeStyle
    {

    public:
        /*!
         * \brief Инициализирует стиль ребра.
         * \param diameter Диаметр линии.
         * \param color Цвет линии.
         */
        explicit EdgeStyle(qreal diameter = 0.,
                             Qt::GlobalColor color = Qt::black);
        /*!
         * \brief Уничтожает стиль ребра.
         */
        ~EdgeStyle();
        /*!
         * \brief Возвращает диаметр линии.
         * \return Диаметр линии.
         */
        inline qreal getDiameter() const;
        /*!
         * \brief Возвращает цвет линии.
         * \return Цвет линии.
         */
        inline Qt::GlobalColor getColor() const;

    private:
        /*!
         * \brief Диаметр линии.
         */
        qreal diameter;
        /*!
         * \brief Цвет линии.
         */
        Qt::GlobalColor color;
    };

    /*!
     * \brief Ребро.
     */
    class Edge : public QObject, public QGraphicsItem
    {
        Q_OBJECT

    public:
        /*!
         * \brief Инициализирует ребро из двух вершин.
         * \param first Первая вершина.
         * \param second Вторая вершина.
         * \param style Стиль ребра.
         * \param parent Объект родителя.
         */
        explicit Edge(Vertex* first,
                      Vertex* second = nullptr,
                      EdgeStyle* style = nullptr,
                      QObject *parent = nullptr);
        /*!
         * \brief Уничтожает ребро.
         */
        ~Edge();
        /*!
         * \brief Возвращает стиль ребра.
         * \return Стиль ребра.
         */
        EdgeStyle* getStyle() const;
        /*!
         * \brief Устанавливает стиль ребра.
         * \param value Стиль ребра.
         */
        void setStyle(EdgeStyle* value);

    private:
        /*!
         * \brief Первая вершина.
         */
        Vertex* first;
        /*!
         * \brief Вторая вершина.
         */
        Vertex* second;
        /*!
         * \brief Стиль ребра.
         */
        EdgeStyle* style;

        /*!
         * \brief Возвращает четверть, в которой лежит вторая вершина, если первая имеет координаты (0, 0). 0, если одна из вершин nullptr.
         * \return Четверть вершины или 0.
         */
        int getQuarter() const;
        /*!
         * \brief Возвращает собственную область рисования.
         * \return Область рисования.
         */
        QRectF boundingRect() const;
        /*!
         * \brief Отрисовывает объект.
         * \param painter Рисовальщик.
         * \param option Опции.
         * \param widget Виджет.
         */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    };

}

#endif // EDGE_H
