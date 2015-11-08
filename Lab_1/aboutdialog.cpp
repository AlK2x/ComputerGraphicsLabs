#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent), m_painter(this),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(ui->textEdit);
    painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap));
        painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
        painter.drawRect(70, 70, 50, 15);
        painter.drawRect(70, 70, 15, 75);
}


void AboutDialog::drowA(int h)
{

}

void AboutDialog::drowB(int h)
{

}

void AboutDialog::drowK(int h)
{

}
