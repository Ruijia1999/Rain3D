#ifndef RAIN_REFLECT_H
#define RAIN_REFLECT_H

#include <map>
#include <string>
#include "ECS/Entity.h"
namespace Rain {
	namespace Reflect {

#define ENTITY(classType) \
static classType self; \
static Rain::ECS::Entity* my_class(int i_id, std::string i_tag, std::string i_name) { \
	classType* entity = new classType(i_id, i_tag, i_name); \
	return (Rain::ECS::Entity*)entity; \
} \
classType(const std::string& className) { \
	Rain::Reflect::RegistClass(className, classType::my_class); \
}

#define REGIST(classType) \
classType classType::self(#classType);
		
		typedef ECS::Entity* (*ClassType)(int i_id, std::string i_tag, std::string i_name);
		void Initialize();
		void ClearUp();
		void RegistClass(const std::string& class_name, const ClassType class_type);
		ECS::Entity* GetClass(const std::string& class_name, int i_id, std::string i_tag, std::string i_name);

	}
}
#endif // !RAIN_REFLECT
