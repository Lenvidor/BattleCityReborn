#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QMetaMethod>
#include <QTimer>
#include <QHash>
#include <QList>
#include <QMap>

class ResumableTimer : public QObject
{
    Q_OBJECT
public:
    void connect(int msec, const QObject *receiver, const char *member);
    void disconnect(const QObject *receiver, const char *member);
    void singleShot(int msec, const QObject *receiver, const char *member);

    void stop();
    void resume();
    void clear();

private slots:
    void onCompleted();
    void onIntervalResumed();

private:
    QList<QSharedPointer<QTimer>> mOnceTimers;
    QHash<QObject*,int> mRemainingMsec;

    QList<QSharedPointer<QTimer>> mIntervalTimers;
    QHash<QObject*,int> mIntervals;
    QHash<const QObject*,QMap<QString,QSharedPointer<QTimer>>> mIntervalTimerLink;
    bool mStopped { false };
};

typedef QSharedPointer<ResumableTimer> SResumableTimer;
