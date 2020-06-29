#ifndef THEME_H
#define THEME_H

#include "line.h"

namespace GraphCore
{
    /*!
     * \brief Тема приложения.
     */
    class Theme
    {

    public:
        /*!
         * \brief Инициализирует тему приложения.
         */
        Theme();
        /*!
         * \brief Уничтожает тему приложения.
         */
        virtual ~Theme();
        /*!
         * \brief Возвращает цвет фона графа.
         * \return
         */
        virtual QColor getGraphBackground() const = 0;
        /*!
         * \brief Возвращает стандартный стиль вершины.
         * \return
         */
        virtual VertexStyle* getDefaultVertexStyle() const = 0;
        /*!
         * \brief Возвращает стандартный стиль ребра.
         * \return
         */
        virtual EdgeStyle* getDefaultEdgeStyle() const = 0;
        /*!
         * \brief Возвращает стиль подсвеченной вершины.
         * \return
         */
        virtual VertexStyle* getHighlightedVertexStyle() const = 0;
        /*!
         * \brief Возвращает стиль подсвеченного ребра.
         * \return
         */
        virtual EdgeStyle* getHighlightedEdgeStyle() const = 0;
    };

    /*!
     * \brief Белая тема приложения.
     */
    class WhiteTheme : public Theme
    {
    public:
        /*!
         * \brief Инициализирует белую тему приложения.
         */
        WhiteTheme();
        /*!
         * \brief Уничтожает белую тему приложения.
         */
        ~WhiteTheme();
        /*!
         * \brief Возвращает цвет фона графа.
         * \return
         */
        virtual QColor getGraphBackground() const;
        /*!
         * \brief Возвращает стандартный стиль вершины.
         * \return
         */
        virtual VertexStyle* getDefaultVertexStyle() const;
        /*!
         * \brief Возвращает стандартный стиль ребра.
         * \return
         */
        virtual EdgeStyle* getDefaultEdgeStyle() const;
        /*!
         * \brief Возвращает стиль подсвеченной вершины.
         * \return
         */
        virtual VertexStyle* getHighlightedVertexStyle() const;
        /*!
         * \brief Возвращает стиль подсвеченного ребра.
         * \return
         */
        virtual EdgeStyle* getHighlightedEdgeStyle() const;

    private:
        /*!
         * \brief Цвет фона.
         */
        QColor graphBackground;
        /*!
         * \brief Стандартный стиль вершины.
         */
        VertexStyle* defaultVertexStyle;
        /*!
         * \brief Стандартный стиль ребра.
         */
        EdgeStyle* defaultEdgeStyle;
        /*!
         * \brief Подсвеченный стиль вершины.
         */
        VertexStyle* highlightedVertexStyle;
    };

    /*!
     * \brief Черная тема приложения.
     */
    class BlackTheme : public Theme
    {
    public:
        /*!
         * \brief Инициализирует черныю тему приложения.
         */
        BlackTheme();
        /*!
         * \brief Уничтожает черную тему приложения.
         */
        ~BlackTheme();
        /*!
         * \brief Возвращает цвет фона графа.
         * \return
         */
        virtual QColor getGraphBackground() const;
        /*!
         * \brief Возвращает стандартный стиль вершины.
         * \return
         */
        virtual VertexStyle* getDefaultVertexStyle() const;
        /*!
         * \brief Возвращает стандартный стиль ребра.
         * \return
         */
        virtual EdgeStyle* getDefaultEdgeStyle() const;
        /*!
         * \brief Возвращает стиль подсвеченной вершины.
         * \return
         */
        virtual VertexStyle* getHighlightedVertexStyle() const;
        /*!
         * \brief Возвращает стиль подсвеченного ребра.
         * \return
         */
        virtual EdgeStyle* getHighlightedEdgeStyle() const;

    private:
        /*!
         * \brief Цвет фона.
         */
        QColor graphBackground;
        /*!
         * \brief Стандартный стиль вершины.
         */
        VertexStyle* defaultVertexStyle;
        /*!
         * \brief Стандартный стиль ребра.
         */
        EdgeStyle* defaultEdgeStyle;
        /*!
         * \brief Подсвеченный стиль вершины.
         */
        VertexStyle* highlightedVertexStyle;
    };
}

#endif // THEME_H
