#include "imovecontroller.h"

IMoveController::IMoveController(QObject *parent) : QObject(parent)
{

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

void IMoveController::handleKeyboardEvent(QKeyEvent *event)
{

}

void IMoveController::handleMouseEvent(QMouseEvent *event)
{

}

