#ifndef FREEMOVECONTROLLER_H
#define FREEMOVECONTROLLER_H

#include "imovecontroller.h"

#include <QVector3D>
#include <QDebug>

class FreeMoveController : public IMoveController
{
public:
    FreeMoveController();

    // IMoveController interface
public:
    void handleMouseEvent(QMouseEvent *event);
    void handleKeyboardEvent(QKeyEvent *event);
    void transformLoadMatrix(QMatrix4x4 &matrix);
    void stopMoving();

private:
    QVector3D m_beforeEye;
    QVector3D m_afterEye;
};

#endif // FREEMOVECONTROLLER_H
