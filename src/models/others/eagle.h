#ifndef EAGLE_H
#define EAGLE_H

#include "../interactiveobject.h"

class Eagle : public InteractiveObject
{
    Q_OBJECT
public:
    Q_PROPERTY(bool defeated READ defeated NOTIFY defeatedChanged)

    void defeat();
    bool defeated();

signals:
    void defeatedChanged();

private:
    bool mDefeated { false };
};

Q_DECLARE_METATYPE(Eagle *)
typedef QSharedPointer<Eagle> SEagle;

#endif // EAGLE_H
