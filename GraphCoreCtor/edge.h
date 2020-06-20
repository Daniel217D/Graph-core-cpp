#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"
#include <QLineF>

namespace GraphCore
{
    /*!
     * \brief Направление ребра.
     */
    enum class EdgeDirection
    {
        ToFirst, //Стрелка направлена в первую вершину
        ToSecond, //Стрелка направлена во вторую вершину
        All //Стрелка направлена в обе вершины
    };

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
                             Qt::GlobalColor color = Qt::black,
                             qreal arrowLength = 0.,
                             qreal arrowAngle = 0.);
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
        /*!
         * \brief Возвращает длину лепестков стрелки.
         * \return Длина лепестков стрелки.
         */
        inline qreal getArrowLength() const;
        /*!
         * \brief Возвращает угол между лепестками стрелки.
         * \return Угол между лепестками стрелки.
         */
        inline qreal getArrowAngle() const;

    private:
        /*!
         * \brief Диаметр линии.
         */
        qreal diameter;
        /*!
         * \brief Цвет линии.
         */
        Qt::GlobalColor color;
        /*!
         * \brief Длина лепестков стрелки.
         */
        qreal arrowLength;
        /*!
         * \brief Угол между лепестками стрелки.
         */
        qreal arrowAngle;
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
                      EdgeDirection direction = EdgeDirection::All,
                      EdgeStyle* style = nullptr,
                      QObject *parent = nullptr);
        /*!
         * \brief Уничтожает ребро.
         */
        ~Edge();
        /*!
         * \brief Возвращает направление стрелок ребра.
         * \return Направление стрелок.
         */
        EdgeDirection getDirection() const;
        /*!
         * \brief Устанавливает направление стрелок ребра и вызывает его перерисовку.
         * \param value Направление стрелок.
         */
        void setDirection(const EdgeDirection &value);
        /*!
         * \brief Возвращает стиль ребра.
         * \return Стиль ребра.
         */
        EdgeStyle* getStyle() const;
        /*!
         * \brief Устанавливает стиль ребра и вызывает его перерисовку.
         * \param value Стиль ребра.
         */
        void setStyle(EdgeStyle* value);
        /*!
         * \brief Возвращает первую вершину ребра.
         * \return Первая вершина ребра.
         */
        Vertex* getFirst() const;
        /*!
         * \brief Возвращает вторую вершину ребра.
         * \return Вторая вершина ребра.
         */
        Vertex* getSecond() const;

    signals:
        void needDirectionChanged(Edge* sender);
        void needDestruction(Edge* sender);

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
         * \brief Направление стрелок ребра.
         */
        EdgeDirection direction;
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
        bool contains(const QPointF &point) const;
        /*!
         * \brief Отрисовывает объект.
         * \param painter Рисовальщик.
         * \param option Опции.
         * \param widget Виджет.
         */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        /*!
         * \brief Действие при нажатии кнопки мыши.
         * \param event Информация о событии.
         */
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        QLineF line() const;
        /*!
         * \brief Возвращает коеффициент угла наклона.
         * \return Коеффициент угла наклона
         */
        inline qreal getTiltAngle() const;
        /*!
         * \brief Возвращает точку касания относительно центра круга радиусом radix.
         * \param radix Радиус круга.
         * \return Точка касания
         */
        QPointF getTouchPoint(qreal radix) const;
    };

}

#endif // EDGE_H
