#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphcore.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    using namespace GraphCore;

    ui->setupUi(this);
    //graph = new Graph(this);
    //ui->graphView->addWidget(graph);
}

MainWindow::~MainWindow()
{
    delete ui;
}

