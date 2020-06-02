#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsView>
#include "graphcore.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GraphCore::Graph graph;
    QGraphicsView view(&graph);

    graph.setSceneRect(-100, -100, 1100, 1100);
    auto center = &graph.createVertex(100, 100, new GraphCore::VertexStyle(20., Qt::white, 10., Qt::red, Qt::black));
    auto v1 = &graph.createVertex(200, 0, nullptr);
    auto v2 = &graph.createVertex(0, 0, nullptr);
    auto v3 = &graph.createVertex(200, 200, nullptr);
    auto v4 = &graph.createVertex(0, 200, nullptr);
    graph.createEdge(center, v1);
    graph.createEdge(center, v2);
    graph.createEdge(center, v3);
    graph.createEdge(center, v4);
    view.show();

    //MainWindow w;
    //w.show();
    return a.exec();
}
