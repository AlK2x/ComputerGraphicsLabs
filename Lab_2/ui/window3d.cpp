#include "window3d.h"
#include <QResizeEvent>
#include <QPainter>
#include <QGuiApplication>
#include <QDebug>

Window3D::Window3D(QWindow *parent)
    : QWindow(parent)
{
    setSurfaceType(QWindow::OpenGLSurface);
    setFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

void Window3D::setFixedSize(QSize size)
{
    setMinimumSize(size);
    setMaximumSize(size);
}

void Window3D::pushScene(std::shared_ptr<BaseScene> scene)
{
    m_sceneStack.push_back(scene);
    scene->onPush();
}

void Window3D::popScene()
{
    if (!m_sceneStack.empty())
    {
        m_sceneStack.back()->onPop();
        m_sceneStack.pop_back();
    }
}

bool Window3D::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::UpdateRequest:
        m_updatePending = false;
        render();
        return true;
    case QEvent::Close:
        if (m_canRender)
        {
            stopRendering();
        }
        return QWindow::event(event);
    default:
        return QWindow::event(event);
    }
}

void Window3D::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        float dx = event->x();
        float dy = event->y();
        m_x = event->x();
        m_y = event->y();

        auto scene = m_sceneStack.back();
        m_sceneStack.pop_back();
        QVector3D eye(scene->camera().eye());

        float radian = dx * PI / 180;
        rotateZ(eye, radian);
        //rotateY(eye, dy * PI / 180);
        qDebug() << eye << "\n";
        scene->camera().lookAt(eye, QVector3D(0, 0, 0), QVector3D(0, 0, 1));
        m_sceneStack.push_back(scene);
        render();
    }
}

void Window3D::rotateZ(QVector3D &eye, float rad)
{
    float r = sqrt(eye.x() * eye.x() + eye.y() * eye.y());
    float newX = r * cos(rad);
    float newY = r * sin(rad);

    eye.setX(newX);
    eye.setY(newY);
    eye.setZ(eye.z());
}

void Window3D::rotateY(QVector3D &eye, float rad)
{
    float r = sqrt(eye.x() * eye.x() + eye.z() * eye.z());
    float newX = r * cos(rad);
    float newZ = r * sin(rad);

    eye.setX(newX);
    eye.setY(eye.y());
    eye.setZ(newZ);
}

void Window3D::mouseReleaseEvent(QMouseEvent *event)
{
    m_x = 0;
    m_y = 0;
}

void Window3D::mousePressEvent(QMouseEvent *event)
{
    m_x = event->x() / 50.0;
    m_y = event->y() / 50.0;
}

void Window3D::exposeEvent(QExposeEvent *event)
{
    QWindow::exposeEvent(event);
    if (isExposed())
        render();
}

void Window3D::resizeEvent(QResizeEvent *event)
{
    QWindow::resizeEvent(event);
    if (!m_canRender)
    {
        initRendering();
    }
}

void Window3D::showEvent(QShowEvent *event)
{
    QWindow::showEvent(event);
}

void Window3D::deferRender()
{
    if (!m_updatePending) {
        m_updatePending = true;
        QGuiApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void Window3D::render()
{
    if (!m_canRender)
    {
        return;
    }

    m_pContext->makeCurrent(this);
    if (!m_sceneStack.empty())
    {
        updateScene(*m_sceneStack.back());
    }
    else
    {
        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    m_pContext->swapBuffers(this);
    deferRender();
}

void Window3D::stopRendering()
{
    while (!m_sceneStack.empty())
    {
        popScene();
    }
    m_canRender = false;
}

void Window3D::initRendering()
{
    if (!m_pContext) {
        m_pContext = new QOpenGLContext(this);
        m_pContext->setFormat(requestedFormat());
        m_pContext->create();
    }
    m_canRender = true;
    m_updateTime.start();
}

void Window3D::updateScene(BaseScene &scene)
{
    scene.setViewport(size());

    int msec = m_updateTime.elapsed();
    m_updateTime.restart();
    scene.visit([&](SceneNode & node) {
        node.advance(msec);
    });
    scene.camera().advance(msec);

    QOpenGLPaintDevice device(size());
    QPainter painter(&device);
    scene.camera().loadMatrix();
    scene.render(painter);
    scene.visit([&](SceneNode & node) {
        node.render(painter);
    });
}