#include "ComponentBase.h"

Rain::ECS::ComponentBase::ComponentBase() {
	id = 0;
	active = true;
}

Rain::ECS::ComponentBase::ComponentBase(int i_id) {
	id = i_id;
	active = true;
}

