#ifndef THEME_H
#define THEME_H

#include "line.h"

namespace GraphCore
{
    class Theme
    {

    public:
        Theme();
        virtual ~Theme();
        virtual VertexStyle* getDefaultVertexStyle() const = 0;
        virtual EdgeStyle* getDefaultEdgeStyle() const = 0;
        virtual VertexStyle* getHighlightedVertexStyle() const = 0;
        virtual EdgeStyle* getHighlightedEdgeStyle() const = 0;
    };

    class WhiteTheme : public Theme
    {
    public:
        WhiteTheme();
        ~WhiteTheme();
        virtual VertexStyle* getDefaultVertexStyle() const;
        virtual EdgeStyle* getDefaultEdgeStyle() const;
        virtual VertexStyle* getHighlightedVertexStyle() const;
        virtual EdgeStyle* getHighlightedEdgeStyle() const;

    private:
        VertexStyle* defaultVertexStyle;
        EdgeStyle* defaultEdgeStyle;
        VertexStyle* highlightedVertexStyle;
    };
}

#endif // THEME_H
