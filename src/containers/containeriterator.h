#ifndef CONTAINERITERATOR_H
#define CONTAINERITERATOR_H

#include "modelscontainer.h"
#include "callbackcontainer.h"
#include <QHash>
#include <QMap>

#define TO_STRING(a) #a

template <class T>
using NestedMap = QHash<QObject *, QMap<int, Callback<T>>>;

class BaseHandler
{
public:
    virtual ~BaseHandler() {}
    virtual void receive(QObject *, int, int) = 0;
};

class Listener : public QObject
{
    Q_OBJECT
public:
    Listener(BaseHandler *handler) : handler(handler) { }
public slots:
    void processSignal(int value) { handler->receive(QObject::sender(), QObject::senderSignalIndex(), value); }
private:
    BaseHandler *handler;
};

template <typename T> class ContainerIterator : public BaseHandler
{
public:
    ContainerIterator(SModelsContainer modelsContainer);

    bool hasNext();
    QSharedPointer<T> peekNext();
    QSharedPointer<T> next();
    void remove();
    void toFront();

private:
    SModelsContainer mModelsContainer;
    /*
     * forwardNextIndex - the index that corresponds to object pointer of T type
     * that's going to be picked up by member functions ::next() and ::peekNext().
     * If there is no next object of T type, then forwardNextIndex is equal to
     * list size.
     *
     * backwardNextIndex - the index that corresposnds to object pointer of non-T
     * type that's located right after previous object of T type. If there is no
     * previous object of T type, then backwardNextIndex is equal to zero.
     * backwardNextIndex is additional index that's needed for maintaining cases
     * of removing and inserting objects of T type in the list.
     *
     * Example:
     * T - objects of T type
     * F - forwardNextIndex
     * B - backwardNextIndex
     * O - objects of different non-T types
     *
     * Objects list:
     * OOOOTOOOTOOOO
     *      |  |
     *      B  F
     */
    int forwardNextIndex { 0 };
    int backwardNextIndex { 0 };

    NestedMap<ContainerIterator> mCallbacks;
    QSharedPointer<Listener> mListener;

    /*QMutableLinkedListIterator<SObject> mForwardIter;
    QMutableLinkedListIterator<SObject> mBackwardIter;*/

    //void tuneIterator();

    void registerCallbacks();
    void tuneForwardIndex();
    void tuneBackwardIndex();

    void receive(QObject *sender, int signalIndex, int value);
    void onObjectInserted(int index);
    void onObjectRemoved(int index);
};

#include "templatedefinitions.h"

#endif // CONTAINERITERATOR_H
