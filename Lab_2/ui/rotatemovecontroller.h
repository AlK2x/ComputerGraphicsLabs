#ifndef ROTATEMOVECONTROLLER_H
#define ROTATEMOVECONTROLLER_H

#include "imovecontroller.h"

#include <QVector3D>
#include <QDebug>

class RotateMoveController : public IMoveController
{
public:
    RotateMoveController();

    // IMoveController interface
public:
    void handleMouseEvent(QMouseEvent *event);
    void handleKeyboardEvent(QKeyEvent *event);
    void transformLoadMatrix(QMatrix4x4 &matrix);
    void stopMoving();

private:
    QVector3D m_rotateVector;
    float m_angleX;
    float m_angleY;

    int m_x;
    int m_y;
};

#endif // ROTATEMOVECONTROLLER_H
