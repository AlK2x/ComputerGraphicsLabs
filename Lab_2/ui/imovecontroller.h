#ifndef IMOVECONTROLLER_H
#define IMOVECONTROLLER_H

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QVector3D>



class IMoveController : public QObject
{
    Q_OBJECT
public:
    explicit IMoveController(QObject *parent = 0);

    virtual void handleMouseEvent(QMouseEvent *event) = 0;
    virtual void handleKeyboardEvent(QKeyEvent *event) = 0;
    virtual void transformLoadMatrix(QMatrix4x4 &matrix) = 0;

    void saveCameraPosition(QVector3D const &eye, QVector3D const &at, QVector3D const &up);
    QVector3D getEye() const;
    QVector3D getFront() const;
    QVector3D getUp() const;

signals:

public slots:

protected:
    QVector3D m_eye;   /**< Eye position */
    QVector3D m_front; /**< Front direction */
    QVector3D m_up;    /**< Up direction */
};

#endif // IMOVECONTROLLER_H
