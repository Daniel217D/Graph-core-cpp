#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>

#include "graph.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

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
    graph = new Graph(*theme, this->ui->orientation, this);

    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp();
    QString testGraph = dir.absoluteFilePath("TestGraph.grd");

    GraphCore::GraphData* data = GraphCore::restoreGraphData(testGraph);
    if(data != nullptr){
        ui->orientation->setChecked(data->isOriented);
        graph->deserialize(*data);
        delete data;
    }

    graphView = new QGraphicsView(graph);
    ui->graphLayout->addWidget(graphView);
    graph->setSceneRect(0, 0, 4096, 4096);
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

void MainWindow::on_openFile_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выберите граф", "", "Графы (*.grd);;Все файлы (*.*)");
    if (filename.size() > 0){
        currentFilename = filename;
        GraphCore::GraphData* data = GraphCore::restoreGraphData(currentFilename);
        if(data != nullptr){
            ui->orientation->setChecked(data->isOriented);
            graph->deserialize(*data);
            delete data;
        }
    }
}

void MainWindow::on_saveFile_triggered()
{
    if (currentFilename.size() > 0){
        GraphCore::GraphData& data = graph->serialize();
        GraphCore::saveGraphData(data, currentFilename);
        delete &data;
    } else on_saveAsFile_triggered();
}

void MainWindow::on_saveAsFile_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить граф", "", "Графы (*.grd);;Все файлы (*.*)");
    if (filename.size() > 0){
        currentFilename = filename;
        on_saveFile_triggered();
    }
}

void MainWindow::on_clearAll_triggered()
{
    graph->removeAll();
}
