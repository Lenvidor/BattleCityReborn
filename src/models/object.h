#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QSharedPointer>

class Object : public QObject
{
    Q_OBJECT
public:
    explicit Object(QObject *parent = 0);

    Q_PROPERTY(QPoint position READ position NOTIFY positionChanged)
    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)
    Q_PROPERTY(int x READ x NOTIFY positionChanged)
    Q_PROPERTY(int y READ y NOTIFY positionChanged)
    Q_PROPERTY(int width READ width NOTIFY sizeChanged)
    Q_PROPERTY(int height READ height NOTIFY sizeChanged)


    int x() const;
    int y() const;
    int width() const;
    int height() const;
    int top() const;
    int bottom() const;
    int left() const;
    int right() const;

    QPoint position() const;
    void setPosition(const QPoint &position);

    QSize size() const;
    void setSize(const QSize &size);

    QRect rect() const;

signals:
    void positionChanged();
    void sizeChanged();

private:
    QPoint mPosition;
    QSize mSize;
};

Q_DECLARE_METATYPE(Object *)
typedef QSharedPointer<Object> SObject;

#endif // OBJECT_H
