#include "graph.h"
#include "vertex.h"
#include "edge.h"

namespace GraphCore{

    Graph::Graph()
    {

    }

    int Graph::getVertexID(const Vertex* vertex)
    {
        return 1;
    }

    const VertexStyle& Graph::getVertexStyle(const Vertex *vertex)
    {
        return this->DEFAULT_STYLE;
    }

}
