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
    this->setEnabled(false);

    ui->linsList->clear();
    ui->lexList->clear();
    ui->lcsList->clear();

    GraphCore::CoreFinderThread* thread = new GraphCore::CoreFinderThread(*this->graph);

    connect(thread, &GraphCore::CoreFinderThread::progressChanged, this, [&](GraphCore::CoreFinderProgress& progress){

    });

    connect(thread, &GraphCore::CoreFinderThread::internalFounded, this, [&](QStringList* result){
        if(result != nullptr)
            this->ui->linsList->addItems(*result);
        delete result;
    });

    connect(thread, &GraphCore::CoreFinderThread::externalFounded, this, [&](QStringList* result){
        if(result != nullptr)
            this->ui->lexList->addItems(*result);
        delete result;
    });

    connect(thread, &GraphCore::CoreFinderThread::coreFounded, this, [&](QStringList* result){
        if(result != nullptr)
            this->ui->lcsList->addItems(*result);
        this->setEnabled(true);
    });

    connect(thread, &GraphCore::CoreFinderThread::finished, thread, &GraphCore::CoreFinderThread::deleteLater);

    thread->start();
}
