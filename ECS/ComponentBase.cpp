#include "ComponentBase.h"

Rain::ECS::ComponentBase::ComponentBase() {
	id = 0;
}

Rain::ECS::ComponentBase::ComponentBase(int i_id,std::shared_ptr <Entity> i_entity) {
	id = i_id;
	entity = i_entity;
}

