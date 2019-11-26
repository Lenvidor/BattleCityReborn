#pragma once

#include <QSharedPointer>
#include <QObject>

class PlayerInfo : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int lives READ lives NOTIFY livesChanged)
    Q_PROPERTY(int score READ score NOTIFY scoreChanged)

    int lives() const;
    void setLives(int lives);

    int score() const;
    void setScore(int score);

signals:
    void livesChanged();
    void scoreChanged();

private:
    int mLives;
    int mScore;
};

Q_DECLARE_METATYPE(PlayerInfo *)
typedef QSharedPointer<PlayerInfo> SPlayerInfo;
