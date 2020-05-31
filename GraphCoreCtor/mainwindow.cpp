#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vertex.h>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    using namespace GraphCore;

    ui->setupUi(this);

    graph_scene = new QGraphicsScene();

    graph_scene->setSceneRect(0, 0, 100, 100);
    auto test_vertex = new Vertex(0, 0, 30, VertexCircuit(10., Qt::black));
    auto test_vertex2 = new Vertex(60, 60, 20, VertexCircuit(10., Qt::blue), Qt::red);
    auto test_vertex3 = new Vertex(120, 120, 30, VertexCircuit(30., Qt::green), Qt::green);

    ui->graphicsView->setScene(graph_scene);
    graph_scene->addItem(test_vertex);
    graph_scene->addItem(test_vertex2);
    graph_scene->addItem(test_vertex3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

