#ifndef LINE_H
#define LINE_H

#include "data.h"

namespace GraphCore
{
    /*!
     * \brief Линия.
     */
    class Line : public QObject, public QGraphicsLineItem
    {

    public:
        /*!
         * \brief Инициализирует линию.
         * \param style Стиль линии.
         * \param direction Направление линии.
         * \param parent Объект родителя.
         */
        explicit Line(EdgeStyle* style = nullptr,
                      EdgeDirection direction = EdgeDirection::All,
                      bool isOriented = true,
                      QObject *parent = nullptr);
        /*!
         * \brief Уничтожает линию.
         */
        ~Line();
        /*!
         * \brief Возвращает стиль линии.
         * \return Стиль линии.
         */
        EdgeStyle* getStyle() const;
        /*!
         * \brief Устанавливает стиль линии и вызывает ее перерисовку.
         * \param value Стиль линии.
         */
        void setStyle(EdgeStyle* value);
        /*!
         * \brief Возвращает направление линии
         * \return Направление линии.
         */
        EdgeDirection getDirection() const;
        /*!
         * \brief Устанавливает направление линии и вызывает ее перерисовку.
         * \param value Направление линии.
         */
        void setDirection(const EdgeDirection &value);
        /*!
         * \brief setPoint Устанавливает начальную точку. Скрывает линию, если value = nullptr.
         * \param value Вершина.
         */
        void setPoint(Vertex *value);
        /*!
         * \brief Вовзращает true, если стрелки стрелки направлений отображаются.
         * \return Статус отображения стрелок.
         */
        bool getOriented() const;
        /*!
         * \brief Устанавливает значение отображения стрелок.
         * \param value Статус отображения стрелок.
         */
        void setOriented(bool value);

    private:
        /*!
         * \brief style
         */
        EdgeStyle* style;
        /*!
         * \brief direction
         */
        EdgeDirection direction;
        /*!
         * \brief point
         */
        Vertex* point;
        /*!
         * \brief Статус отображения стрелок.
         */
        bool isOriented;

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
