#include "stdafx.h"
#include "Transform.h"

void _Transform_Destroy(Transform* self)
{
    if (self)
        free(self);
}

Transform* CreateTransform()
{
    Transform* transform = (Transform*)malloc(sizeof(Transform));
    
    transform->Destroy = _Transform_Destroy;

    transform->_position.x = 0;
    transform->_position.y = 0;
    transform->_size.x = 0;
    transform->_size.y = 0;
    transform->_velocity.x = 0;
    transform->_velocity.y = 0;

    return transform;
}
