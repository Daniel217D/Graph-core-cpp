#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>

#include "graph.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    using namespace GraphCore;

    ui->setupUi(this);
    graph = new Graph(this);
    QGraphicsView* view = new QGraphicsView(graph);
    graph->setSceneRect(-100, -100, 1100, 1100);
    ui->graphView->addWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

