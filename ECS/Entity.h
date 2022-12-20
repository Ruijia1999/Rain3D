#ifndef RAIN_ECS_ENTITY
#define RAIN_ECS_ENTITY
namespace Rain {
	namespace ECS {

		class Entity
		{
		public:
			int id;
			virtual void Initialize(int id) = 0;
		};

	}
}
#endif // !RAIN_ECS_ENTITY

