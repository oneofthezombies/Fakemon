#include "stdafx.h"
#include "Component.h"

Component* CreateComponent(ComponentType componentType)
{
    switch (componentType)
    case ComponentType_Transform:
        return CreateTransform();

    return NULL;
}
