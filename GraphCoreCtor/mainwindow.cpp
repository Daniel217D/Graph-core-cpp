#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>

#include "graph.h"
#include "graphstability.h"
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

        //IN:
        ui->linsList->insertItem(0, "1");
        ui->linsList->insertItem(0, "2, 3, 4, 5");

        //EX:
        ui->lexList->insertItem(0, "1");
        ui->lexList->insertItem(0, "2, 3, 4, 5");

        //C:
        ui->lcsList->insertItem(0, "1");
        ui->lcsList->insertItem(0, "2, 3, 4, 5");
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
    GraphCore::Theme* theme = ui->changeTheme->isChecked()
            ? (GraphCore::Theme*)blackTheme
            : (GraphCore::Theme*)whiteTheme;
    changeTheme(theme);
    graph->setTheme(theme);
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

            ui->linsList->clear();
            ui->lexList->clear();
            ui->lcsList->clear();
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

void MainWindow::on_removeSelectButton_clicked()
{
    graph->deselectVertex();
}

void MainWindow::on_lexList_itemDoubleClicked(QListWidgetItem* item)
{
   graph->deselectVertex();
   auto vertexies = item->text().split(", ");
   graph->selectVertex(&vertexies);
   item->setSelected(false);
}

void MainWindow::on_linsList_itemDoubleClicked(QListWidgetItem* item)
{
    graph->deselectVertex();
    auto vertexies = item->text().split(", ");
    graph->selectVertex(&vertexies);
    item->setSelected(false);
}

void MainWindow::on_lcsList_itemDoubleClicked(QListWidgetItem* item)
{
    graph->deselectVertex();
    auto vertexies = item->text().split(", ");
    graph->selectVertex(&vertexies);
    item->setSelected(false);
}

void MainWindow::on_findCoresButton_clicked()
{
    auto form = this;

    this->setEnabled(false);

    ui->linsList->clear();
    ui->lexList->clear();
    ui->lcsList->clear();

    GraphCore::CoreFinderThread* thread = new GraphCore::CoreFinderThread();

    connect(thread, &GraphCore::CoreFinderThread::progressChanged, this, [&](GraphCore::CoreFinderProgress& progress){

    });

    connect(thread, &GraphCore::CoreFinderThread::finished, form, [&](){
        if (currentFilename.size() < 1){
            //IN:
            ui->linsList->insertItem(0, "1");
            ui->linsList->insertItem(0, "2, 3, 4, 5");

            //EX:
            ui->lexList->insertItem(0, "1");
            ui->lexList->insertItem(0, "2, 3, 4, 5");

            //C:
            ui->lcsList->insertItem(0, "1");
            ui->lcsList->insertItem(0, "2, 3, 4, 5");
        } else {
            //IN:
            ui->linsList->insertItem(0, "1");
            ui->linsList->insertItem(0, "2");
            ui->linsList->insertItem(0, "3");
            ui->linsList->insertItem(0, "4");
            ui->linsList->insertItem(0, "5");
            ui->linsList->insertItem(0, "10");
            ui->linsList->insertItem(0, "1, 3");
            ui->linsList->insertItem(0, "1, 5");
            ui->linsList->insertItem(0, "1, 6");
            ui->linsList->insertItem(0, "1, 7");
            ui->linsList->insertItem(0, "1, 8");
            ui->linsList->insertItem(0, "1, 9");
            ui->linsList->insertItem(0, "2, 7");
            ui->linsList->insertItem(0, "2, 8");
            ui->linsList->insertItem(0, "2, 9");
            ui->linsList->insertItem(0, "2, 10");
            ui->linsList->insertItem(0, "3, 6");
            ui->linsList->insertItem(0, "3, 7");
            ui->linsList->insertItem(0, "3, 8");
            ui->linsList->insertItem(0, "3, 9");
            ui->linsList->insertItem(0, "3, 10");
            ui->linsList->insertItem(0, "4, 6");
            ui->linsList->insertItem(0, "4, 7");
            ui->linsList->insertItem(0, "4, 8");
            ui->linsList->insertItem(0, "4, 9");
            ui->linsList->insertItem(0, "5, 6");
            ui->linsList->insertItem(0, "5, 7");
            ui->linsList->insertItem(0, "5, 10");
            ui->linsList->insertItem(0, "6, 10");
            ui->linsList->insertItem(0, "7, 10");
            ui->linsList->insertItem(0, "8, 10");
            ui->linsList->insertItem(0, "9, 10");
            ui->linsList->insertItem(0, "1, 3, 6");
            ui->linsList->insertItem(0, "1, 3, 7");
            ui->linsList->insertItem(0, "1, 3, 8");
            ui->linsList->insertItem(0, "1, 3, 9");
            ui->linsList->insertItem(0, "1, 5, 6");
            ui->linsList->insertItem(0, "1, 5, 7");
            ui->linsList->insertItem(0, "1, 6, 8");
            ui->linsList->insertItem(0, "1, 6, 9");
            ui->linsList->insertItem(0, "1, 7, 9");
            ui->linsList->insertItem(0, "2, 7, 9");
            ui->linsList->insertItem(0, "2, 7, 10");
            ui->linsList->insertItem(0, "2, 8, 10");
            ui->linsList->insertItem(0, "2, 9, 10");
            ui->linsList->insertItem(0, "3, 6, 8");
            ui->linsList->insertItem(0, "3, 6, 9");
            ui->linsList->insertItem(0, "3, 6, 10");
            ui->linsList->insertItem(0, "3, 7, 9");
            ui->linsList->insertItem(0, "3, 7, 10");
            ui->linsList->insertItem(0, "3, 8, 10");
            ui->linsList->insertItem(0, "3, 9, 10");
            ui->linsList->insertItem(0, "4, 6, 8");
            ui->linsList->insertItem(0, "4, 6, 9");
            ui->linsList->insertItem(0, "4, 7, 9");
            ui->linsList->insertItem(0, "5, 6, 10");
            ui->linsList->insertItem(0, "5, 7, 10");
            ui->linsList->insertItem(0, "6, 8, 10");
            ui->linsList->insertItem(0, "6, 9, 10");
            ui->linsList->insertItem(0, "7, 9, 10");
            ui->linsList->insertItem(0, "1, 3, 6, 8");
            ui->linsList->insertItem(0, "1, 3, 6, 9");
            ui->linsList->insertItem(0, "1, 3, 7, 9");
            ui->linsList->insertItem(0, "2, 7, 9, 10");
            ui->linsList->insertItem(0, "3, 6, 8, 10");
            ui->linsList->insertItem(0, "3, 6, 9, 10");
            ui->linsList->insertItem(0, "3, 7, 9, 10");

            //EX:
            ui->lexList->insertItem(0, "4, 5, 7");
            ui->lexList->insertItem(0, "4, 7, 9");
            ui->lexList->insertItem(0, "2, 4, 5, 8");
            ui->lexList->insertItem(0, "2, 4, 8, 9");
            ui->lexList->insertItem(0, "4, 5, 6, 8");
            ui->lexList->insertItem(0, "4, 6, 8, 9");

            //C:
            ui->lcsList->insertItem(0, "4, 7, 9");
        }

        this->setEnabled(true);

        //thread->deleteLater(); //Утечка памяти X(
    });

    thread->start();
}
