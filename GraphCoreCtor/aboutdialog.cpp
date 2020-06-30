#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QGraphicsPixmapItem>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QPixmap pixmap(":/resources/aboutLines.png");

    int w = std::min(pixmap.width(),  ui->logo->maximumWidth());
    int h = std::min(pixmap.height(), ui->logo->maximumHeight());
    pixmap = pixmap.scaled(QSize(w, h), Qt::AspectRatioMode::KeepAspectRatioByExpanding, Qt::TransformationMode::SmoothTransformation);
    ui->logo->setPixmap(pixmap);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_ok_clicked()
{
    close();
}
