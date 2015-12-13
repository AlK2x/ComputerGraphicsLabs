#include "rotatemovecontroller.h"

RotateMoveController::RotateMoveController()
    :m_angleX(0.0)
    , m_angleY(0.0)
    , m_rotateVector(QVector3D(0, 0, 1))
    , m_x(0)
    , m_y(0)
{

}

void RotateMoveController::handleKeyboardEvent(QKeyEvent *event)
{
}

void RotateMoveController::transformLoadMatrix(QMatrix4x4 &matrix)
{
    matrix.rotate(m_angleX, m_rotateVector);
    matrix.rotate(m_angleY, QVector3D(0, 1, 0));
    matrix *= QMatrix4x4(m_wheelFactor, 0, 0, 0,
                         0, m_wheelFactor, 0, 0,
                         0, 0, m_wheelFactor, 0,
                         0, 0, 0, 1);
 //   m_wheelFactor = 0;
}

void RotateMoveController::stopMoving()
{
    m_x = 0;
    m_y = 0;
}

void RotateMoveController::handleMouseEvent(QMouseEvent *event)
{
    int dx = event->x() - m_x;
    int dy = event->y() - m_y;
    m_angleX += dx;
    m_angleY += dy;
qDebug() << m_angleX << ' ' << m_angleY << '\n';
    m_x = event->x();
    m_y = event->y();
}
