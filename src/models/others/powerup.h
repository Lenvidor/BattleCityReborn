#pragma once

#include "../interactiveobject.h"
#include "../../enums/poweruptype.h"

class PowerUp : public InteractiveObject
{
    Q_OBJECT
public:
    Q_PROPERTY(PowerUpType::Enum type READ type NOTIFY typeChanged)

    PowerUpType::Enum type() const;
    void setType(const PowerUpType::Enum &type);

signals:
    void typeChanged();

private:
    PowerUpType::Enum mType;
};

Q_DECLARE_METATYPE(PowerUp *)
typedef QSharedPointer<PowerUp> SPowerUp;
