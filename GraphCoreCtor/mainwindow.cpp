#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>

#include "graph.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    using namespace GraphCore;

    ui->setupUi(this);

    whiteTheme = new WhiteTheme();
    blackTheme = new BlackTheme();
    Theme* theme = ui->changeTheme->isChecked() ? (Theme*)blackTheme : (Theme*)whiteTheme;
    graph = new Graph(*theme, this->ui->orientation, this);

    /*Vertex& v1 = graph->createVertex(-32, -23, nullptr);
    Vertex&  v2 = graph->createVertex(102, -27, nullptr);
    Vertex&  v3 = graph->createVertex(95, 231, nullptr);
    Vertex&  v4 = graph->createVertex(-69, 343, nullptr);
    Vertex&  v5 = graph->createVertex(169, 317, nullptr);
    Vertex&  v6 = graph->createVertex(221, -26, nullptr);
    Vertex&  v7 = graph->createVertex(226, 90, nullptr);
    Vertex&  v8 = graph->createVertex(443, 159, nullptr);
    Vertex&  v9 = graph->createVertex(255, 232, nullptr);
    Vertex&  v10 = graph->createVertex(34, 58, nullptr);

    //1
    graph->createEdge(&v1, &v2, EdgeDirection::ToSecond, nullptr);
    graph->createEdge(&v1, &v4, EdgeDirection::ToSecond, nullptr);
    graph->createEdge(&v1, &v10, EdgeDirection::ToSecond, nullptr);

    //2
    graph->createEdge(&v2, &v3, EdgeDirection::All, nullptr);
    graph->createEdge(&v2, &v4, EdgeDirection::ToSecond, nullptr);

    //3
    graph->createEdge(&v3, &v4, EdgeDirection::ToSecond, nullptr);
    graph->createEdge(&v3, &v5, EdgeDirection::ToSecond, nullptr);

    //5
    graph->createEdge(&v5, &v2, EdgeDirection::ToSecond, nullptr);
    graph->createEdge(&v5, &v4, EdgeDirection::ToSecond, nullptr);

    //6
    graph->createEdge(&v6, &v2, EdgeDirection::ToSecond, nullptr);
    graph->createEdge(&v6, &v7, EdgeDirection::ToSecond, nullptr);

    //7
    graph->createEdge(&v7, &v8, EdgeDirection::ToSecond, nullptr);

    //8
    graph->createEdge(&v8, &v5, EdgeDirection::ToSecond, nullptr);
    graph->createEdge(&v8, &v9, EdgeDirection::ToSecond, nullptr);

    //9
    graph->createEdge(&v9, &v5, EdgeDirection::ToSecond, nullptr);

    //10
    graph->createEdge(&v10, &v4, EdgeDirection::ToSecond, nullptr);*/

    Vertex& center = graph->createVertex(0, 0);
    Vertex& v1 = graph->createVertex(100, 100);
    Vertex& v2 = graph->createVertex(-100, -100);
    Vertex& v3 = graph->createVertex(-100, 100);
    Vertex& v4 = graph->createVertex(100, -100);
    graph->createEdge(&center, &v1, EdgeDirection::All);
    graph->createEdge(&center, &v2, EdgeDirection::All);
    graph->createEdge(&center, &v3, EdgeDirection::All);
    graph->createEdge(&center, &v4, EdgeDirection::All);

    QGraphicsView* view = new QGraphicsView(graph);
    graph->setSceneRect(-100, -100, 1100, 1100);
    ui->graphView->addWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete graph;
    delete whiteTheme;
}

void MainWindow::on_changeTheme_changed()
{
    if (ui->changeTheme->isChecked()){
        QFile file(":/darkTheme.qss");
        file.open(QIODevice::Text | QIODevice::ReadOnly);
        QTextStream stream(&file);
        setStyleSheet(stream.readAll());

        graph->setTheme(blackTheme);

        file.close();
    } else {
        this->setStyleSheet("");

        graph->setTheme(whiteTheme);
    }
}

void MainWindow::on_orientation_changed()
{
    graph->setOriented(ui->orientation->isChecked());
}
