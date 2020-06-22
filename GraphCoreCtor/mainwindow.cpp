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
    changeTheme(theme);
    //graph = Graph::deserialize(*restoreGraphData("D:\\Niapoll\\Desktop\\Test.grd"), *theme, this->ui->orientation, this); //new Graph(*theme, this->ui->orientation, this);
    graph = new Graph(*theme, this->ui->orientation, this);

    /*Vertex& v1 = graph->createVertex(-32, -23);
    Vertex&  v2 = graph->createVertex(102, -27);
    Vertex&  v3 = graph->createVertex(95, 231);
    Vertex&  v4 = graph->createVertex(-69, 343);
    Vertex&  v5 = graph->createVertex(169, 317);
    Vertex&  v6 = graph->createVertex(221, -26);
    Vertex&  v7 = graph->createVertex(226, 90);
    Vertex&  v8 = graph->createVertex(443, 159);
    Vertex&  v9 = graph->createVertex(255, 232);
    Vertex&  v10 = graph->createVertex(34, 58);

    //1
    graph->createEdge(&v1, &v2, EdgeDirection::ToSecond);
    graph->createEdge(&v1, &v4, EdgeDirection::ToSecond);
    graph->createEdge(&v1, &v10, EdgeDirection::ToSecond);

    //2
    graph->createEdge(&v2, &v3, EdgeDirection::All);
    graph->createEdge(&v2, &v4, EdgeDirection::ToSecond);

    //3
    graph->createEdge(&v3, &v4, EdgeDirection::ToSecond);
    graph->createEdge(&v3, &v5, EdgeDirection::ToSecond);

    //5
    graph->createEdge(&v5, &v2, EdgeDirection::ToSecond);
    graph->createEdge(&v5, &v4, EdgeDirection::ToSecond);

    //6
    graph->createEdge(&v6, &v2, EdgeDirection::ToSecond);
    graph->createEdge(&v6, &v7, EdgeDirection::ToSecond);

    //7
    graph->createEdge(&v7, &v8, EdgeDirection::ToSecond);

    //8
    graph->createEdge(&v8, &v5, EdgeDirection::ToSecond);
    graph->createEdge(&v8, &v9, EdgeDirection::ToSecond);

    //9
    graph->createEdge(&v9, &v5, EdgeDirection::ToSecond);

    //10
    graph->createEdge(&v10, &v4, EdgeDirection::ToSecond);*/

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
        changeTheme(blackTheme);
        graph->setTheme(blackTheme);
    } else {
        changeTheme(whiteTheme);
        graph->setTheme(whiteTheme);
    }
}

void MainWindow::on_orientation_changed()
{
    graph->setOriented(ui->orientation->isChecked());
}

void MainWindow::changeTheme(GraphCore::Theme *theme)
{
    if (theme == whiteTheme){
        setStyleSheet("");
    } else if (theme == blackTheme) {
        QString filename = ":/darkTheme.qss";
        QFile file(filename);
        file.open(QIODevice::Text | QIODevice::ReadOnly);
        QTextStream stream(&file);
        setStyleSheet(stream.readAll());
        file.close();
    }
}
