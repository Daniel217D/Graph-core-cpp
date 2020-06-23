#include "graphstability.h"

namespace GraphCore
{

    GraphStability::GraphStability(Graph& graph)
    {
        graph.createAdjacencyMatrix(adjacencyMatrix, length);
    }

    GraphStability::~GraphStability()
    {
        for(int i = 0; i < length; ++i)
            delete[] adjacencyMatrix[i];
        delete[] adjacencyMatrix;
    }

    bool **GraphStability::getAdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }

    int GraphStability::getLength() const
    {
        return length;
    }

    GraphExternalStability::GraphExternalStability(Graph& graph)
        :GraphStability(graph)
    {

    }

    GraphExternalStability::~GraphExternalStability()
    {

    }

    GraphInternalStability::GraphInternalStability(Graph& graph)
        :GraphStability(graph)
    {

    }

    GraphInternalStability::~GraphInternalStability()
    {

    }

    CoreFinderThread::CoreFinderThread()
        :QThread()
    {
        this->progress = new CoreFinderProgress();
    }

    CoreFinderThread::~CoreFinderThread()
    {
        delete progress;
    }

    void CoreFinderThread::run()
    {
        QThread::sleep(10);
    }

}
