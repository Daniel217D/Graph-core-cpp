#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include <QListWidgetItem>
#include <QGraphicsView>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_changeTheme_changed();

    void on_orientation_changed();

    void on_openFile_triggered();

    void on_saveFile_triggered();

    void on_saveAsFile_triggered();

    void on_clearAll_triggered();

    void on_removeSelectButton_clicked();

    void on_lexList_itemDoubleClicked(QListWidgetItem *item);

    void on_linsList_itemDoubleClicked(QListWidgetItem *item);

    void on_lcsList_itemDoubleClicked(QListWidgetItem *item);

    void on_findCoresButton_clicked();

    void on_about_triggered();

    void on_clearLists_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsView* graphView;
    GraphCore::Graph* graph;
    GraphCore::WhiteTheme* whiteTheme;
    GraphCore::BlackTheme* blackTheme;
    QString currentFilename;
    QLabel* progressLabel;

    /*!
     * \brief Меняет тему окна приложения относительно темы графа.
     * \param theme Тема графа.
     */
    void changeTheme(GraphCore::Theme* theme);
};
#endif // MAINWINDOW_H
