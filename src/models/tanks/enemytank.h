#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "tank.h"
#include "../../enums/tanktype.h"

class EnemyTank : public Tank
{
    Q_OBJECT
public:
    Q_PROPERTY(bool bonus READ bonus NOTIFY bonusChanged)
    Q_PROPERTY(TankType::Enum type READ type NOTIFY typeChanged)

    TankType::Enum type() const;
    void setType(const TankType::Enum &type);

    bool bonus() const;
    void setBonus(bool bonus);

signals:
    void typeChanged();
    void bonusChanged();

private:
    TankType::Enum mType;
    bool mBonus;
};

Q_DECLARE_METATYPE(EnemyTank *)
typedef QSharedPointer<EnemyTank> SEnemyTank;

#endif // ENEMYTANK_H
