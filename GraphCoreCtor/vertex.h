#ifndef VERTEX_H
#define VERTEX_H

#include <QObject>
#include <QPainter>
#include <QGraphicsItem>

namespace GraphCore
{
    /*!
     * \brief Стиль вершины.
     */
    class VertexStyle
    {

    public:
        /*!
         * \brief Инициализирует стиль вершины.
         * \param radius Радиус.
         * \param backgroundColor Цвет фона.
         * \param circuitPercent Процент контура.
         * \param circuitColor Цвет контура.
         * \param textColor Цвет текста.
         */
        explicit VertexStyle(qreal radius = 0.,
                             Qt::GlobalColor backgroundColor = Qt::white,
                             qreal circuitPercent = 0,
                             Qt::GlobalColor circuitColor = Qt::black,
                             Qt::GlobalColor textColor = Qt::black);
        /*!
         * Уничтожает вершину.
         */
        ~VertexStyle();
        /*!
         * \brief Возвращает радиус.
         * \return Радиус.
         */
        inline qreal getRadius() const;
        /*!
         * \brief Возвращает цвет фона.
         * \return Цвет фона.
         */
        inline Qt::GlobalColor getBackgroundColor() const;
        /*!
         * \brief Возвращает процент контура.
         * \return Процент контура.
         */
        inline qreal getCircuitPercent() const;
        /*!
         * \brief Возвращает цвет контура.
         * \return Цвет контура.
         */
        inline Qt::GlobalColor getCircuitColor() const;
        /*!
         * \brief Возвращает цвет текста.
         * \return Цвет текста.
         */
        inline Qt::GlobalColor getTextColor() const;

    private:
        /*!
         * \brief Радиус.
         */
        qreal radius;
        /*!
         * \brief Цвет фона.
         */
        Qt::GlobalColor backgroundColor;
        /*!
         * \brief Процент контура.
         */
        qreal circuitPercent;
        /*!
         * \brief Цвет контура.
         */
        Qt::GlobalColor circuitColor;
        /*!
         * \brief Цвет текста.
         */
        Qt::GlobalColor textColor;
    };

    /*!
     * \brief Вершина.
     */
    class Vertex : public QObject, public QGraphicsItem
    {
        Q_OBJECT

    public:
        /*!
         * \brief Инициализирует вершину.
         * \param centerX Координата центра вершины x.
         * \param centerY Координата центра вершины y.
         * \param style Стиль вершины.
         * \param parent
         */
        explicit Vertex(int centerX = 0,
                        int centerY = 0,
                        VertexStyle* style = nullptr,
                        QString name = "",
                        QObject *parent = nullptr);
        /*!
         * Уничтожает вершину.
         */
        ~Vertex();
        /*!
         * \brief Возвращает стиль вершины.
         * \return Стиль вершины.
         */
        VertexStyle* getStyle() const;
        /*!
         * \brief Устанавливает стиль вершины и вызывает ее перерисовку.
         * \param value Стиль вершины.
         */
        void setStyle(VertexStyle* value);
        /*!
         * \brief Получает имя вершины.
         * \return Имя вершины.
         */
        QString getName() const;
        /*!
         * \brief Устанавливает имя вершины и вызывает ее перерисовку.
         * \param Имя вершины.
         */
        void setName(const QString& value);
        /*!
         * \brief Меняет местоположение вершины и вызывает positionChangedByMouse.
         * \param x Координата центра вершины x.
         * \param y Координата центра вершины y.
         */
        void changePositionWithSignal(const int x, const int y);
        /*!
         * \brief Возвращает true и устанавливает вершину в позицию oldPosition, если эта позиция не равна nullptr.
         */
        bool returnPositionIfExist();

    signals:
        /*!
         * \brief Оповещает подписчиков, что вершина начала процесс перемещения (под действием мыши).
         * \param sender Создатель оповещения.
         */
        void startPositionChangedByMouse(Vertex* sender);
        /*!
         * \brief Оповещает подписчиков, что вершина переместилась (под действием мыши).
         * \param sender Создатель оповещения.
         * \param x Координата x.
         * \param y Координата y.
         */
        void positionChangedByMouse(Vertex* sender, int x, int y);
        /*!
         * \brief Оповещает подписчиков, что вершина закончила процесс перемещения (под действием мыши).
         * \param sender Создатель оповещения.
         */
        void endPositionChangedByMouse(Vertex* sender);

    private:
        /*!
         * \brief Стиль вершины.
         */
        VertexStyle* style;
        /*!
         * \brief Позиция до перемещения (устанавливается в mousePressEvent, очищается mouseReleaseEvent).
         */
        QPointF* oldPosition;
        /*!
         * \brief Имя вершины.
         */
        QString name;

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
        /*!
         * \brief Действие при перемещении мыши (с нажатой кнопкой).
         * \param event Информация о событии.
         */
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        /*!
         * \brief Действие при нажатии кнопки мыши.
         * \param event Информация о событии.
         */
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        /*!
         * \brief Действие при отпускании кнопки мыши.
         * \param event Информация о событии.
         */
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    };

}

#endif // VERTEX_H
