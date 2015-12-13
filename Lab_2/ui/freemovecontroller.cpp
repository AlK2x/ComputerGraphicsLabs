#include "freemovecontroller.h"

FreeMoveController::FreeMoveController()
{

}

void FreeMoveController::handleMouseEvent(QMouseEvent *event)
{
    qDebug() << 'Handle key event' << '\n';
}

void FreeMoveController::handleKeyboardEvent(QKeyEvent *event)
{
    qDebug() << 'Handle key event' << '\n';
}

void FreeMoveController::transformLoadMatrix(QMatrix4x4 &matrix)
{

}

void FreeMoveController::stopMoving()
{

}
