#ifndef ICOORDINATOR_H
#define ICOORDINATOR_H

#include <QSharedPointer>

class ICoordinator
{
public:
    virtual void initialize() = 0;
    virtual void terminate() = 0;

    virtual ~ICoordinator() {}
};

#endif // ICOORDINATOR_H
