#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsView>
#include "graph.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    using namespace GraphCore;

    Graph graph;
    QGraphicsView view(&graph);

    graph.setSceneRect(-100, -100, 1100, 1100);
    auto center = &graph.createVertex(100, 100, new VertexStyle(20., Qt::white, 10., Qt::red, Qt::black));
    auto v1 = &graph.createVertex(200, 0, nullptr);
    auto v2 = &graph.createVertex(0, 0, nullptr);
    auto v3 = &graph.createVertex(200, 200, nullptr);
    auto v4 = &graph.createVertex(0, 200, nullptr);
    graph.createEdge(center, v1, nullptr);
    graph.createEdge(center, v2, nullptr);
    graph.createEdge(center, v3, nullptr);
    graph.createEdge(center, v4, nullptr);
    view.show();

    //MainWindow w;
    //w.show();
    return a.exec();
}
