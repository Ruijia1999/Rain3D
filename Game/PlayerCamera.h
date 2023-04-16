#ifndef PLAERCAMERA
#define PLAERCAMERA
#include "ECS/Entity.h"
#include "Reflect/Reflect.h"
#include "Transform\TransformComponent.h"
namespace Rain {
	class PlayerCamera : public ECS::Entity
	{
	public:
		ENTITY(PlayerCamera)
			PlayerCamera();
		PlayerCamera(int i_id, std::string i_tag, std::string i_name);
		void Initialize();
		void Update(double i_timeSinceLastFrame);

	private:
		float mouseSensitivity;
	
		Math::Vector2 orgMouseCoord;
		Math::Vector3 orgCameraPos;
		Math::Vector3 orgDiversity;
		Rain::Transform::TransformComponent* camera;
		Rain::Transform::TransformComponent* player;
	};
	REGIST(PlayerCamera)
}

#endif
