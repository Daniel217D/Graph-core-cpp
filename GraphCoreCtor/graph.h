#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include "graphcore.h"
#include "vertex.h"

namespace GraphCore{

    class Graph
    {

    public:
        Graph();
        int getVertexID(const Vertex* vertex);
        const VertexStyle& getVertexStyle(const Vertex* vertex);
        Vertex& createVertex(int x = 0, int y = 0, int radius = 0, VertexStyle circuit = VertexStyle(0, Qt::black), Qt::GlobalColor textColor = Qt::black);
        bool deleteVertex(const Vertex& vertex);

    private:
        const VertexStyle DEFAULT_STYLE = VertexStyle(20., Qt::white, 10., Qt::blue, Qt::black);
        std::list<Vertex> vertices;
        std::list<Edge> edges;
    };
}

#endif // GRAPH_H
