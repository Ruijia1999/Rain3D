#include "Cube.h"
#include "Transform/TransformComponent.h"
#include "Transform/TransformSystem.h"
#include "Input/Input.h"
#include "Collision\ColliderSystem.h"
#include "Collision\ColliderComponent.h"
#include "MeshRender\MeshRender.h"
void Rain::Cube::Initialize(int i_id) {
    id = i_id;
    Rain::Input::Mouse::BindEvent(MOUSE_LEFT_DOWN, [this](Rain::Input::MouseInfo info) {
        Transform::TransformComponent* transform = Transform::TransformSystem::GetInstance()->GetComponent<Transform::TransformComponent>(this->id);
        //transform->position = transform->position + Math::Vector3(0.3f, 0, 0);
        });
    ColliderComponent* collider = ColliderSystem::GetInstance()->GetComponent<ColliderComponent>(id);
    
  
}

Rain::Cube::Cube() {
	int j = 1;
}