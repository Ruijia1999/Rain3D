#ifndef PLAYER
#define PLAYER
#include "ECS/Entity.h"
#include "Reflect/Reflect.h"
#include <vector>
#include "Math\Math.h"
namespace Rain {
	class Player : public ECS::Entity
	{
	public:
		ENTITY(Player)
		Player();
		Player(int i_id, std::string i_tag, std::string i_name);
		void Initialize();
		void Update(double i_timeSinceLastFrame);
		void Destory();
		void StartPathFinding();
		std::vector<int> CheckCollision();

		void ModifyVelocity(Math::Vector2 i_curPos, Math::Vector2 i_aimPos, float i_radius, const std::vector<int>& i_obstacles);
	};
	REGIST(Player)
}

#endif
