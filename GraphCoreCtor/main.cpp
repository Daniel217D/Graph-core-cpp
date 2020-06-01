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
    graph.createVertex(10, 10, nullptr);

    view.show();

    //MainWindow w;
    //w.show();
    return a.exec();
}
