#pragma once

#include <QObject>
#include <QSharedPointer>

class StageInfo : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int stageNumber READ stageNumber NOTIFY stageNumberChanged)
    Q_PROPERTY(int tanksAvailable READ tanksAvailable NOTIFY tanksAvailableChanged)

    int stageNumber() const;
    void setStageNumber(int stageNumber);

    int tanksAvailable() const;
    void setTanksAvailable(int tanksAvailable);

signals:
    void stageNumberChanged();
    void tanksAvailableChanged();

private:
    int mStageNumber;
    int mTanksAvailable;
};

Q_DECLARE_METATYPE(StageInfo *)
typedef QSharedPointer<StageInfo> SStageInfo;
