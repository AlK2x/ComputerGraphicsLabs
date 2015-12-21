#include "imovecontroller.h"

IMoveController::IMoveController(QObject *parent) : QObject(parent)
{

}

void IMoveController::handleWheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
    {
        m_wheelFactor = (m_wheelFactor < 5) ? m_wheelFactor + 0.3 : m_wheelFactor;
    }
    else
    {
        m_wheelFactor = (m_wheelFactor > 0.1) ? m_wheelFactor - 0.3 : m_wheelFactor;
    }
    qDebug() << "m_wheelFactor = " << m_wheelFactor << '\n';
    event->accept();
}

void IMoveController::saveCameraPosition(const QVector3D &eye, const QVector3D &front, const QVector3D &up)
{
    m_eye = eye;
    m_front = front;
    m_up = up;
}

QVector3D IMoveController::getEye() const
{
    return m_eye;
}

QVector3D IMoveController::getFront() const
{
    return m_front;
}

QVector3D IMoveController::getUp() const
{
    return m_up;
}
