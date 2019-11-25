#include "movementcoordinator.h"

MovementCoordinator::MovementCoordinator() : mGlobal(Global::getInstance())
{

}

/**********************************************
 * ORGINISING METHODS
 **********************************************/

void MovementCoordinator::initialize()
{
    if (mGlobal && mGlobal->resumableTimer)
    {
        mGlobal->resumableTimer->connect(MV_TIMER_MSEC,this,SLOT(onTimerTriggered()));
    }
}

void MovementCoordinator::terminate()
{
    if (mGlobal && mGlobal->resumableTimer)
    {
        mGlobal->resumableTimer->disconnect(this,SLOT(onTimerTriggered()));
    }
}

/**********************************************
 * PROCESSING METHODS
 **********************************************/

int MovementCoordinator::processInteractions(SMovingObject mvObj) const
{
    ObjectList objects = findCrossingObjects(mvObj);

    int distance = mvObj->nextMoveDistance(MV_TIMER_MSEC);
    QPoint position = mvObj->position();
    QPoint direction = Converter::toVector(mvObj->direction());

    for (int i = 0; i < distance; i++)
    {
        QRect tempRect = mvObj->rect();
        tempRect.moveCenter(position+direction*(i+1));
        ObjectListIterator objIter(objects);

        bool barrierIsReached = limitIsReached(tempRect);

        while (objIter.hasNext())
        {
            SInteractiveObject obj = objIter.next();

            if (!obj || obj->terminated() || !obj->intersects(tempRect))
            {
                continue;
            }

            if (mGlobal->interactionController->interact(mvObj,obj,i))
            {
                barrierIsReached = true;
            }
        }

        if (barrierIsReached)
        {
            return i;
        }
    }

    return -1;
}

void MovementCoordinator::validatePosition(SMovingObject mvObj) const
{

    QPoint tempPosition = mvObj->position();

    switch (mvObj->direction())
    {
    case Direction::UP:
    case Direction::DOWN:
    {
        tempPosition.rx() = qRound(float(tempPosition.rx())/float(TURN_RATE))*TURN_RATE;
        break;
    }
    case Direction::LEFT:
    case Direction::RIGHT:
    {
        tempPosition.ry() = qRound(float(tempPosition.ry()/float(TURN_RATE)))*TURN_RATE;
        break;
    }
    }

    mvObj->setPosition(tempPosition);
}

void MovementCoordinator::processCollisions() const
{
    if (!mGlobal || !mGlobal->modelsContainer)
        return;

    auto mvIter = mGlobal->modelsContainer->getIterator<MovingObject>();

    while (mvIter.hasNext())
    {
        SMovingObject mvObj = mvIter.next();

        if (!mvObj->terminated() && mvObj->moving())
        {
            if (mvObj->terminateNextTurn())
            {
                mvObj->terminate();
                continue;
            }

            validatePosition(mvObj);

            int distanceToBarrier = processInteractions(mvObj);
            bool barrierIsReached = distanceToBarrier > -1;

            if (barrierIsReached)
            {
                mvObj->reachBarrier(distanceToBarrier);
                emit objectMoved(mvObj.data(),distanceToBarrier,true);
            }
            else
            {
                int distance = mvObj->nextMoveDistance(MV_TIMER_MSEC);
                mvObj->move(MV_TIMER_MSEC);
                emit objectMoved(mvObj.data(),distance,false);
            }
        }
    }
}

/**********************************************
 * HELPING METHODS
 **********************************************/

bool MovementCoordinator::limitIsReached(const QRect &rect) const
{
    return  rect.top() <= -PX_TILE_SIZE/2 ||
            rect.left() <= -PX_TILE_SIZE/2 ||
            rect.bottom() > PX_TILE_SIZE*STAGE_MAP_SIZE - PX_TILE_SIZE/2 ||
            rect.right() > PX_TILE_SIZE*STAGE_MAP_SIZE - PX_TILE_SIZE/2;
}


ObjectList MovementCoordinator::findCrossingObjects(const SMovingObject &mvObj) const
{
    auto iter = mGlobal->modelsContainer->getIterator<InteractiveObject>();

    ObjectList objectList;
    QRect mvArea = getMovingArea(mvObj);

    while (iter.hasNext())
    {
        SInteractiveObject obj = iter.next();

        if (obj != mvObj && obj->intersects(mvArea))
        {
            objectList.append(obj);
        }
    }

    return objectList;
}

QRect MovementCoordinator::getMovingArea(const SMovingObject &mvObj) const
{
    int dx = mvObj->nextMoveDistance(MV_TIMER_MSEC);

    QPoint s = QPoint(mvObj->width(),mvObj->height()); // size in point form
    QPoint d = Converter::toVector(mvObj->direction()); // direction in point form
    QPoint td = transpose(d); // transposed point form of direction
    QPoint c = mvObj->position(); // object position

    // temporary points
    QPoint p = c + crossProduct(d,s)/2;
    QPoint tl = p + crossProduct(td,s)/2;
    QPoint br = p - crossProduct(td,s)/2 + dx*d;

    return normalize(QRect(tl,br)).adjusted(1,1,0,0);
}

QRect MovementCoordinator::normalize(const QRect &r) const
{
    QRect rect = r;

    if (rect.top() > rect.bottom())
    {
        rect.setBottom(r.top());
        rect.setTop(r.bottom());
    }
    if (rect.left() > rect.right())
    {
        rect.setLeft(r.right());
        rect.setRight(r.left());
    }
    return rect;
}

QPoint MovementCoordinator::transpose(const QPoint &p) const
{
    return QPoint(p.y(),p.x());
}

QPoint MovementCoordinator::crossProduct(const QPoint &p1, const QPoint &p2) const
{
    return QPoint(p1.x()*p2.x(),p1.y()*p2.y());
}


/**********************************************
 * EVENT LISTENERS
 **********************************************/

void MovementCoordinator::onTimerTriggered()
{
    processCollisions();
}

