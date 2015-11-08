#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QPainter>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void drowK(int h);
    void drowA(int h);
    void drowB(int h);

    Ui::AboutDialog *ui;
    QPainter m_painter;
};

#endif // ABOUTDIALOG_H
