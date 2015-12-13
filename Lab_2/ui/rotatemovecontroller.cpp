#include "rotatemovecontroller.h"

RotateMoveController::RotateMoveController()
    :m_angle(0.0)
    , m_rotateVector(QVector3D(0, 0, 1))
{

}

void RotateMoveController::handleKeyboardEvent(QKeyEvent *event)
{
    qDebug() << "Rotate keyboard" << '\n';
}

void RotateMoveController::transformLoadMatrix(QMatrix4x4 &matrix)
{
    matrix.rotate(m_angle, m_rotateVector);
}

void RotateMoveController::handleMouseEvent(QMouseEvent *event)
{
    m_angle += event->x();
}
