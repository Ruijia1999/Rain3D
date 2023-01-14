#ifndef CIRCLE
#define CIRCLE
#include "ECS/Entity.h"
#include "Reflect/Reflect.h"
#include <vector>
#include "Math\Math.h"
namespace Rain {
	class Circle : public ECS::Entity
	{
	public:
		ENTITY(Circle)
		Circle();
		Circle(int i_id, std::string i_tag, std::string i_name);
		void Initialize();
		void Update(double i_timeSinceLastFrame);
		void Destory();
		void StartPathFinding();
		std::vector<int> CheckCollision();

		void ModifyVelocity(Math::Vector2 i_curPos, Math::Vector2 i_aimPos, float i_radius, const std::vector<int>& i_obstacles);
	};
	REGIST(Circle)
}

#endif
