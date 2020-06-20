#include "theme.h"
namespace GraphCore
{


    GraphCore::WhiteTheme::WhiteTheme()
        :Theme()
    {
        defaultVertexStyle = new VertexStyle(20., Qt::white, 10., Qt::blue, Qt::black);
        defaultEdgeStyle = new EdgeStyle(3, Qt::black, 10, 0.45);
        highlightedVertexStyle = new VertexStyle(20., Qt::white, 10., Qt::red, Qt::black);
    }

    GraphCore::WhiteTheme::~WhiteTheme()
    {
        delete defaultVertexStyle;
        delete defaultEdgeStyle;
        delete highlightedVertexStyle;
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

    Theme::Theme()
    {

    }

    Theme::~Theme()
    {

    }

}
