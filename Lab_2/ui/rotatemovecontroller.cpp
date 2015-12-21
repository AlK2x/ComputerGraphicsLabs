#define _USE_MATH_DEFINES
#include "rotatemovecontroller.h"
#include <QQuaternion>

RotateMoveController::RotateMoveController()
    : m_angleX(0.0)
    , m_angleY(0.0)
{

}

void RotateMoveController::handleKeyboardEvent(QKeyEvent *event)
{
    (void)event;
}

void RotateMoveController::transformLoadMatrix(QMatrix4x4 &matrix)
{
    QVector3D angles(m_angleX, m_angleY, 0);
    QQuaternion quat = QQuaternion::fromEulerAngles(angles);
    matrix.rotate(quat);

//    QMatrix4x4 rotator;
//    rotator.rotate(m_angleX, QVector3D(0, 0, 1));
//    matrix *= rotator;
//    float angleRadX = m_angleX * M_PI / 180;
//    matrix.rotate(m_angleY, QVector3D(sinf(angleRadX), cosf(angleRadX), 0));
    float s = m_wheelFactor;
    matrix *= QMatrix4x4(s, 0, 0, 0,
                         0, s, 0, 0,
                         0, 0, s, 0,
                         0, 0, 0, 1);
 //   m_wheelFactor = 0;
}

void RotateMoveController::stopMoving()
{
    m_pos.setX(0);
    m_pos.setY(0);
}

void RotateMoveController::handleMouseEvent(QMouseEvent *event)
{
    if (event->type() == QEvent::MouseMove)
    {
        int dx = event->x() - m_pos.x();
        int dy = event->y() - m_pos.y();
        m_angleX += dx;
        m_angleY += dy;
    }
    m_pos.setX(event->x());
    m_pos.setY(event->y());
}
