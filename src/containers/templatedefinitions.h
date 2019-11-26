#pragma once

#include "modelscontainer.h"

template <typename T>
ContainerIterator<T> ModelsContainer::getIterator()
{
    return ContainerIterator<T>(sharedFromThis());
}

template <typename T>
ContainerIterator<T>::ContainerIterator(SModelsContainer modelsContainer) :
    mModelsContainer(modelsContainer), mListener(new Listener(this))/*,
    mForwardIter(modelsContainer->mObjects),
    mBackwardIter(modelsContainer->mObjects)*/
{
    //mBackwardIter.toFront();
    //mForwardIter.toFront();
    //tuneIterator();


    registerCallbacks();
    toFront();
}

template <typename T>
void ContainerIterator<T>::toFront()
{
    backwardNextIndex = 0;
    forwardNextIndex = 0;

    tuneForwardIndex();
}

template <typename T>
bool ContainerIterator<T>::hasNext()
{
    return forwardNextIndex != mModelsContainer->mObjects.size();
    //return mForwardIter.hasNext();
}

template <typename T>
QSharedPointer<T> ContainerIterator<T>::peekNext()
{
    return hasNext() ? mModelsContainer->mObjects[forwardNextIndex].template objectCast<T>() : QSharedPointer<T>(nullptr);
    //return mForwardIter.peekNext().objectCast<T>();
}

template <typename T>
void ContainerIterator<T>::remove()
{
    mModelsContainer->removeAt(backwardNextIndex-1);
    //mBackwardIter.remove();
}

template <typename T>
QSharedPointer<T> ContainerIterator<T>::next()
{
    QSharedPointer<T> tObject = peekNext();

    if (hasNext())
    {
        backwardNextIndex = ++forwardNextIndex;
        tuneForwardIndex();
    }

    return tObject;

    /*auto obj = mForwardIter.next();
    mBackwardIter = mForwardIter;
    tuneIterator();
    return obj.objectCast<T>();*/
}

/*template <typename T>
void ContainerIterator<T>::tuneIterator()
{
    while (mForwardIter.hasNext() && !mForwardIter.peekNext().objectCast<T>())
    {
        mForwardIter.next();
    }
}*/

template <typename T>
void ContainerIterator<T>::registerCallbacks()
{
    mCallbacks[mModelsContainer.data()][mModelsContainer->metaObject()->indexOfSignal(TO_STRING(objectInserted(int,Object*)))] = &ContainerIterator<T>::onObjectInserted;
    mCallbacks[mModelsContainer.data()][mModelsContainer->metaObject()->indexOfSignal(TO_STRING(objectRemoved(int,Object*)))] = &ContainerIterator<T>::onObjectRemoved;
    QObject::connect(mModelsContainer.data(),SIGNAL(objectInserted(int,Object*)), mListener.data(),SLOT(processSignal(int)));
    QObject::connect(mModelsContainer.data(),SIGNAL(objectRemoved(int,Object*)), mListener.data(),SLOT(processSignal(int)));
}

template <typename T>
void ContainerIterator<T>::receive(QObject *sender, int signalIndex, int value)
{
    if (mCallbacks.contains(sender) && mCallbacks[sender].contains(signalIndex))
    {
        (this->*mCallbacks[sender][signalIndex])(value);
    }
}

template <typename T>
void ContainerIterator<T>::tuneBackwardIndex()
{
    while (backwardNextIndex-- > 0)
    {
        if (mModelsContainer->mObjects[backwardNextIndex].template objectCast<T>())
        {
            backwardNextIndex++;
            break;
        }
    }
}

template <typename T>
void ContainerIterator<T>::tuneForwardIndex()
{
    while(forwardNextIndex < mModelsContainer->mObjects.size())
    {
        if (mModelsContainer->mObjects[forwardNextIndex].template objectCast<T>())
        {
            break;
        }
        forwardNextIndex++;
    }
}

template <typename T>
void ContainerIterator<T>::onObjectInserted(int insertedIndex)
{
    if (insertedIndex < backwardNextIndex)
    {
        backwardNextIndex++;
        forwardNextIndex++;
    }
    else if (insertedIndex <= forwardNextIndex)
    {
        if (mModelsContainer->mObjects[insertedIndex].objectCast<T>())
        {
            forwardNextIndex = insertedIndex;
        }
        else
        {
            forwardNextIndex++;
        }
    }
}

template <typename T>
void ContainerIterator<T>::onObjectRemoved(int removedIndex)
{
    if (removedIndex < backwardNextIndex)
    {
        backwardNextIndex--;
        forwardNextIndex--;

        tuneBackwardIndex();
    }
    else if (removedIndex < forwardNextIndex)
    {
        forwardNextIndex--;
    }
    else if (removedIndex == forwardNextIndex)
    {
        tuneForwardIndex();
    }
}
