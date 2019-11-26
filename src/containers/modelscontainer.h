#pragma once

#include <QObject>
#include <QLinkedList>
#include <QSharedPointer>
#include <QEnableSharedFromThis>
#include "../models/object.h"

template <typename T> class ContainerIterator;

class ModelsContainer : public QObject, public QEnableSharedFromThis<ModelsContainer>
{
    Q_OBJECT
public:
    void insert(SObject obj);

    void remove(SObject obj);
    void remove(Object *obj);

    template <typename T> friend class ContainerIterator;
    template <typename T = Object> ContainerIterator<T> getIterator();


signals:
    void objectInserted(int index, Object *obj);
    void objectRemoved(int index, Object *obj);
private:
    QList<SObject> mObjects;

    void removeAt(int index);
};

Q_DECLARE_METATYPE(ModelsContainer *)
typedef QSharedPointer<ModelsContainer> SModelsContainer;

#include "containeriterator.h"

