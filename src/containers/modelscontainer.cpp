#include "modelscontainer.h"

void ModelsContainer::insert(SObject obj)
{
    mObjects.append(obj);
    emit objectInserted(mObjects.size() - 1, obj.data());
}

void ModelsContainer::remove(SObject obj)
{
    remove(obj.data());
}

void ModelsContainer::remove(Object *obj)
{
    for (int i = 0; i < mObjects.size(); i++)
    {
        if (mObjects[i].data() == obj)
        {
            removeAt(i);
            break;
        }
    }


}

void ModelsContainer::removeAt(int index)
{
    SObject obj = mObjects[index];
    mObjects.removeAt(index);
    emit objectRemoved(index,obj.data());
}
