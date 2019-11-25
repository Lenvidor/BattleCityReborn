#include "resumabletimer.h"

void ResumableTimer::connect(int msec, const QObject *receiver, const char *member)
{
    if (mIntervalTimerLink.contains(receiver) && mIntervalTimerLink[receiver].contains(member))
    {
        return;
    }

    QSharedPointer<QTimer> timer = QSharedPointer<QTimer>(new QTimer());
    timer->setInterval(msec);
    timer->setSingleShot(false);
    QObject::connect(timer.data(),SIGNAL(timeout()),receiver,member);

    mIntervals[timer.data()] = msec;
    mIntervalTimers.append(timer);
    mIntervalTimerLink[receiver][member] = timer;

    if (!mStopped)
    {
        timer->start();
    }
}

void ResumableTimer::disconnect(const QObject *receiver, const char *member)
{
    //if (!mIntervalTimerLink.contains(receiver) || !mIntervalTimerLink[receiver].contains(member))
        //return;

    bool bool1 = !mIntervalTimerLink.contains(receiver);
    bool bool2 = bool1 || !mIntervalTimerLink[receiver].contains(member);

    if (bool2)
        return;

    QSharedPointer<QTimer> timer = mIntervalTimerLink[receiver][member];

    QObject::disconnect(timer.data(),SIGNAL(timeout()),receiver,member);

    mIntervals.remove(timer.data());
    mIntervalTimers.removeOne(timer);
    mIntervalTimerLink[receiver].remove(member);

    if (mIntervalTimerLink[receiver].isEmpty())
    {
        mIntervalTimerLink.remove(receiver);
    }
}

void ResumableTimer::singleShot(int msec, const QObject *receiver, const char *member)
{
    QSharedPointer<QTimer> timer = QSharedPointer<QTimer>(new QTimer());
    timer->setInterval(msec);
    timer->setSingleShot(true);
    QObject::connect(timer.data(),SIGNAL(timeout()),receiver,member);
    QObject::connect(timer.data(),&QTimer::timeout,this,&ResumableTimer::onCompleted);

    mOnceTimers.append(timer);

    if (!mStopped)
    {
        timer->start();
    }
}

void ResumableTimer::stop()
{
    if (mStopped)
        return;

    mStopped = true;

    for (int i = 0; i < mOnceTimers.size(); i++)
    {
        QSharedPointer<QTimer> timer = mOnceTimers[i];

        if (timer->isActive())
        {
            mRemainingMsec[timer.data()] = timer->remainingTime();
            timer->stop();
        }
    }

    for (int i = 0; i < mIntervalTimers.size(); i++)
    {
        QSharedPointer<QTimer> timer = mIntervalTimers[i];

        if (timer->isActive())
        {
            mRemainingMsec[timer.data()] = timer->remainingTime();
            QObject::disconnect(timer.data(),&QTimer::timeout,this,&ResumableTimer::onIntervalResumed);
            timer->stop();
        }
    }
}

void ResumableTimer::resume()
{
    if (!mStopped)
        return;

    mStopped = false;

    for (int i = 0; i < mOnceTimers.size(); i++)
    {
        QSharedPointer<QTimer> timer = mOnceTimers[i];

        if (mRemainingMsec.contains(timer.data()))
        {
            timer->start(mRemainingMsec[timer.data()]);
            mRemainingMsec.remove(timer.data());
        }
        else
        {
            timer->start();
        }
    }

    for (int i = 0; i < mIntervalTimers.size(); i++)
    {
        QSharedPointer<QTimer> timer = mIntervalTimers[i];

        if (mRemainingMsec.contains(timer.data()))
        {
            timer->start(mRemainingMsec[timer.data()]);
            QObject::connect(timer.data(),&QTimer::timeout,this,&ResumableTimer::onIntervalResumed);
            mRemainingMsec.remove(timer.data());
        }
        else
        {
            timer->start();
        }
    }
}

void ResumableTimer::clear()
{
    mRemainingMsec.clear();
    mIntervals.clear();
    mIntervalTimers.clear();
    mIntervalTimerLink.clear();
    mOnceTimers.clear();
}

void ResumableTimer::onCompleted()
{
    for (int i = 0; i < mOnceTimers.size(); i++)
    {
        if (mOnceTimers[i].data() == QObject::sender())
        {
            mOnceTimers.removeAt(i);
            break;
        }
    }
}

void ResumableTimer::onIntervalResumed()
{
    for (int i = 0; i < mIntervalTimers.size(); i++)
    {
        QSharedPointer<QTimer> timer = mIntervalTimers[i];

        if (timer.data() == QObject::sender())
        {
            QObject::disconnect(timer.data(),&QTimer::timeout,this,&ResumableTimer::onIntervalResumed);
            timer->start(mIntervals[timer.data()]);
            break;
        }
    }
}
