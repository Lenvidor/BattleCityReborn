#pragma once

#include <QSharedPointer>

class ICoordinator
{
public:
    virtual void initialize() = 0;
    virtual void terminate() = 0;

    virtual ~ICoordinator() {}
};
