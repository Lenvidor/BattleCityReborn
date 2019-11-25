#ifndef CALLBACKCONTAINER_H
#define CALLBACKCONTAINER_H

template <class T>
using Callback = void (T::*)(int);

template <class T>
class CallbackContainer{
public:
    CallbackContainer(T *object, Callback<T> callback)
        : object(object), callback(callback) {}
    void invoke(int value) { ((*object).*callback)(value); }
private:
    T *object;
    Callback<T> callback;
};

#endif // CALLBACKCONTAINER_H
