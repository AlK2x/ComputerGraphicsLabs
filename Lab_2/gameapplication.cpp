#include "gameapplication.h"
#include "gl/scenenode.h"
#include "nodes/coloredcube.h"
#include "ui/rotatemovecontroller.h"

const QSize FIXED_WINDOW_SIZE(800, 600);

GameApplication::GameApplication(int argc, char *argv[])
    : QGuiApplication(argc, argv)
{
}

int GameApplication::enterGameLoop()
{
    m_window.setFixedSize(FIXED_WINDOW_SIZE);
    m_window.show();
    connect(&m_window, SIGNAL(activeChanged()), this, SLOT(loadScene()));

    return exec();
}

void GameApplication::loadFromFile(QString filename)
{
    QString jsonString;
    QFile file;
    file.setFileName(filename);
    if (!file.exists())
    {
        return;
    }
    bool result = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!result)
    {
        return;
    }

    jsonString = file.readAll();
    QJsonDocument json = QJsonDocument::fromJson(jsonString.toUtf8());
    if (json.isNull())
    {
        return;
    }

}

void GameApplication::loadScene()
{
    disconnect(&m_window, SIGNAL(activeChanged()), this, SLOT(loadScene()));

    auto scene = std::make_shared<BaseScene>();
    scene->camera().setViewport(m_window.size());
    scene->camera().lookAt(QVector3D(6, 3, 6), QVector3D(0, 0, 0), QVector3D(0, 0, 1));
    scene->camera().setMoveController(scene->getCurrentMoveController());
    new ColoredCube(scene.get());
    m_window.pushScene(scene);
}
