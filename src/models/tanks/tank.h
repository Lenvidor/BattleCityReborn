#ifndef TANK_H
#define TANK_H

#include "../movingobject.h"
#include <QEnableSharedFromThis>

class Tank : public MovingObject, public QEnableSharedFromThis<Tank>
{
    Q_OBJECT
public:
    Q_PROPERTY(int hitPoints READ hitPoints NOTIFY hitPointsChanged)
    Q_PROPERTY(bool aboutToAppear READ aboutToAppear NOTIFY aboutToAppearChanged)

    void hit();
    void fireshot();

    bool shellLoaded() const;
    int hitPoints() const;

    void setHitPoints(int hitPoints);

    virtual bool intersects(const QRect &rect) const;
    virtual bool moving() const;

    bool aboutToAppear() const;
    void setAboutToAppear(bool aboutToAppear);

public slots:
    void loadShell();
    void appear();

signals:
    void hitPointsChanged();
    void shellLaunched();
    void aboutToAppearChanged();

private:
    int mHitPoints;
    bool mShellLoaded;
    bool mAboutToAppear;
};

Q_DECLARE_METATYPE(Tank *)
typedef QSharedPointer<Tank> STank;

#endif // TANK_H
