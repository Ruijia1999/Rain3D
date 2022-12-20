#ifndef RAIN_REFLECT_H
#define RAIN_REFLECT_H

#include <map>
#include <string>
#include "ECS/Entity.h"
namespace Rain {
	namespace Reflect {

#define ENTITY(classType) \
static classType self; \
static Rain::ECS::Entity* my_class() { \
	classType* entity = new classType(); \
	return (Rain::ECS::Entity*)entity; \
} \
classType(const std::string& className) { \
	Rain::Reflect::RegistClass(className, classType::my_class); \
}

#define REGIST(classType) \
classType classType::self(#classType);
		
		typedef ECS::Entity* (*ClassType)();
		void Initialize();
		void ClearUp();
		void RegistClass(const std::string& class_name, const ClassType class_type);
		ECS::Entity* GetClass(const std::string& class_name);

	}
}
#endif // !RAIN_REFLECT
