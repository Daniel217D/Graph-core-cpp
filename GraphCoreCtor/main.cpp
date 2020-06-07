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

    /*auto center = &graph.createVertex(100, 100, new VertexStyle(20., Qt::white, 10., Qt::red, Qt::black));
    auto v1 = &graph.createVertex(200, 0, nullptr);
    auto v2 = &graph.createVertex(0, 0, nullptr);
    auto v3 = &graph.createVertex(200, 200, nullptr);
    auto v4 = &graph.createVertex(0, 200, nullptr);
    graph.createEdge(center, v1, EdgeDirection::All, nullptr);
    graph.createEdge(center, v2, EdgeDirection::All, nullptr);
    graph.createEdge(center, v3, EdgeDirection::All, nullptr);
    graph.createEdge(center, v4, EdgeDirection::All, nullptr);*/

    auto v1 = &graph.createVertex(-32, -23, nullptr);
    auto v2 = &graph.createVertex(102, -27, nullptr);
    auto v3 = &graph.createVertex(95, 231, nullptr);
    auto v4 = &graph.createVertex(-69, 343, nullptr);
    auto v5 = &graph.createVertex(169, 317, nullptr);
    auto v6 = &graph.createVertex(221, -26, nullptr);
    auto v7 = &graph.createVertex(226, 90, nullptr);
    auto v8 = &graph.createVertex(443, 159, nullptr);
    auto v9 = &graph.createVertex(255, 232, nullptr);
    auto v10 = &graph.createVertex(34, 58, nullptr);

    //1
    graph.createEdge(v1, v2, EdgeDirection::ToSecond, nullptr);
    graph.createEdge(v1, v4, EdgeDirection::ToSecond, nullptr);
    graph.createEdge(v1, v10, EdgeDirection::ToSecond, nullptr);

    //2
    graph.createEdge(v2, v3, EdgeDirection::All, nullptr);
    graph.createEdge(v2, v4, EdgeDirection::ToSecond, nullptr);

    //3
    graph.createEdge(v3, v4, EdgeDirection::ToSecond, nullptr);
    graph.createEdge(v3, v5, EdgeDirection::ToSecond, nullptr);

    //5
    graph.createEdge(v5, v2, EdgeDirection::ToSecond, nullptr);
    graph.createEdge(v5, v4, EdgeDirection::ToSecond, nullptr);

    //6
    graph.createEdge(v6, v2, EdgeDirection::ToSecond, nullptr);
    graph.createEdge(v6, v7, EdgeDirection::ToSecond, nullptr);

    //7
    graph.createEdge(v7, v8, EdgeDirection::ToSecond, nullptr);

    //8
    graph.createEdge(v8, v5, EdgeDirection::ToSecond, nullptr);
    graph.createEdge(v8, v9, EdgeDirection::ToSecond, nullptr);

    //9
    graph.createEdge(v9, v5, EdgeDirection::ToSecond, nullptr);

    //10
    graph.createEdge(v10, v4, EdgeDirection::ToSecond, nullptr);

    view.show();
    graph.update();

    //MainWindow w;
    //w.show();
    return a.exec();
}
