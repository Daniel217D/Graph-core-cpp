#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtMath>
#include "graphcore.h"
#include "graph.h"
#include "vertex.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    using namespace GraphCore;

    ui->setupUi(this);

    graph_scene = new QGraphicsScene();

    graph_scene->setSceneRect(0, 0, 100, 100);
    auto graph = new Graph();
    auto test_vertex = new Vertex(*graph, 0, 0);
    //auto test_vertex3 = new Vertex(*graph, 120, 120, 30, VertexCircuit(30., Qt::green), Qt::green);

    ui->graphicsView->setScene(graph_scene);
    graph_scene->addItem(test_vertex);
    //graph_scene->addItem(test_vertex3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

