#include "theme.h"
namespace GraphCore
{
    GraphCore::WhiteTheme::WhiteTheme()
        :Theme()
    {
        graphBackground = Qt::white;
        defaultVertexStyle = new VertexStyle(20., graphBackground, 10., Qt::blue, Qt::black);
        defaultEdgeStyle = new EdgeStyle(3, Qt::black, 10, 0.45);
        highlightedVertexStyle = new VertexStyle(20., graphBackground, 10., Qt::red, Qt::black);
    }

    GraphCore::WhiteTheme::~WhiteTheme()
    {
        delete defaultVertexStyle;
        delete defaultEdgeStyle;
        delete highlightedVertexStyle;
    }

    QColor WhiteTheme::getGraphBackground() const
    {
        return graphBackground;
    }

    VertexStyle* WhiteTheme::getDefaultVertexStyle() const
    {
        return defaultVertexStyle;
    }

    EdgeStyle* WhiteTheme::getDefaultEdgeStyle() const
    {
        return defaultEdgeStyle;
    }

    VertexStyle* WhiteTheme::getHighlightedVertexStyle() const
    {
        return highlightedVertexStyle;
    }

    EdgeStyle* WhiteTheme::getHighlightedEdgeStyle() const
    {
        return defaultEdgeStyle;
    }

    GraphCore::BlackTheme::BlackTheme()
        :Theme()
    {
        graphBackground = QColor(35, 38, 41);
        defaultVertexStyle = new VertexStyle(20., graphBackground, 15., QColor(61, 174, 233), Qt::white);
        defaultEdgeStyle = new EdgeStyle(3, Qt::white, 10, 0.45);
        highlightedVertexStyle = new VertexStyle(20., graphBackground, 15., Qt::red, Qt::white);
    }

    GraphCore::BlackTheme::~BlackTheme()
    {
        delete defaultVertexStyle;
        delete defaultEdgeStyle;
        delete highlightedVertexStyle;
    }

    QColor BlackTheme::getGraphBackground() const
    {
        return graphBackground;
    }

    VertexStyle* BlackTheme::getDefaultVertexStyle() const
    {
        return defaultVertexStyle;
    }

    EdgeStyle* BlackTheme::getDefaultEdgeStyle() const
    {
        return defaultEdgeStyle;
    }

    VertexStyle* BlackTheme::getHighlightedVertexStyle() const
    {
        return highlightedVertexStyle;
    }

    EdgeStyle* BlackTheme::getHighlightedEdgeStyle() const
    {
        return defaultEdgeStyle;
    }

    Theme::Theme()
    {

    }

    Theme::~Theme()
    {

    }

}
