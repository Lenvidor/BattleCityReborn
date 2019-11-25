#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include "object.h"
#include "../enums/explosiontype.h"
#include "../enums/scoredpoints.h"

class InteractiveObject : public Object
{
    Q_OBJECT
public:
    Q_PROPERTY(ExplosionType::Enum explosionType READ explosionType NOTIFY explosionTypeChanged)
    Q_PROPERTY(ScoredPoints::Enum scoredPoints READ scoredPoints NOTIFY scoredPointsChanged)

    void terminate();
    bool terminated() const;

    virtual bool intersects(const QRect &rect) const;
    virtual bool intersects(const InteractiveObject *obj) const;
    virtual bool intersects(const QSharedPointer<InteractiveObject> &obj) const;

    ExplosionType::Enum explosionType() const;
    void setExplosionType(const ExplosionType::Enum &explosionType);

    ScoredPoints::Enum scoredPoints() const;
    void setScoredPoints(const ScoredPoints::Enum &scoredPoints);

signals:
    void terminatedChanged();
    void explosionTypeChanged();
    void scoredPointsChanged();

private:
    bool mTerminated { false };
    ExplosionType::Enum mExplosionType{ ExplosionType::NONE };
    ScoredPoints::Enum mScoredPoints{ ScoredPoints::NONE };
};

Q_DECLARE_METATYPE(InteractiveObject *)
typedef QSharedPointer<InteractiveObject> SInteractiveObject;

#endif // INTERACTIVEOBJECT_H
