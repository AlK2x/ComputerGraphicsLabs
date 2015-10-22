#include "application.h"
#include <QStyleFactory>
#include <QDebug>
#include <QStyle>
#include <QLibrary>

Application::Application(int argc, char *argv[])
    : QApplication(argc, argv)
{
    initStyle();
    initImageRes();
}

void Application::initStyle()
{

    qDebug() << QStyleFactory::keys();
    auto style = QStyleFactory::create("Fusion");
    QFont font = a.font();
    font.setFamily("Arial");
    font.setPointSize(10);
    a.setFont(font);
    a.setPalette(style->standardPalette());
    a.setStyle(style);
}

void Application::initImageRes()
{
    QLibrary lib("imageres.dll");
    if (!lib.load())
    {
\
    }
}

