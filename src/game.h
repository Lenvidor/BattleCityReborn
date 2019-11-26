#pragma once

#include <QObject>
#include "global.h"
#include "constants/definedconstants.h"

class Game : public QObject
{
    Q_OBJECT
public:
    Game();

    Q_PROPERTY(StageInfo *stageInfo READ stageInfo NOTIFY stageInfoChanged)
    Q_PROPERTY(PlayerInfo *playerInfo READ playerInfo NOTIFY playerInfoChanged)
    Q_PROPERTY(ModelsContainer *modelsContainer READ modelsContainer NOTIFY modelsContainerChanged)
    Q_PROPERTY(bool paused READ paused NOTIFY pausedChanged)
    Q_PROPERTY(bool started READ started NOTIFY startedChanged)
    Q_PROPERTY(bool ready READ ready NOTIFY readyChanged)
    Q_PROPERTY(bool over READ over NOTIFY overChanged)

    bool paused();
    bool started();
    bool ready();
    bool over();

    StageInfo *stageInfo();
    PlayerInfo *playerInfo();
    ModelsContainer *modelsContainer();

signals:
    void startedChanged();
    void pausedChanged();
    void readyChanged();
    void stageInfoChanged();
    void playerInfoChanged();
    void modelsContainerChanged();
    void overChanged();

public slots:
    void prepare();
    void unprepare();
    void start();
    void finish();
    void pause();
    void unpause();

    void movePlayer(int direction);
    void stopMoving();
    void fireFromPlayer();

    void upgradePlayer();
    void randomPowerUp();
    void destroyPlayerTank();
    void addEnemyPlayer();

private slots:
    void onPausedChanged();
    void onStartedChanged();
    void onReadyChanged();
    void onGameOverReached();

private:
    bool mPaused { true };
    bool mStarted { false };
    bool mReady { false };
    bool mOver { false };

    SGlobal mGlobal;

    void setOver(bool over);
};
