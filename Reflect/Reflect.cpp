#include "Reflect.h"

namespace {
	std::map<std::string, Rain::Reflect::ClassType>* entities;
	bool ifInitialize = false;
}

void  Rain::Reflect::Initialize() {
	entities = new std::map<std::string, Rain::Reflect::ClassType>();
}
void ClearUp() {
}
void Rain::Reflect::RegistClass(const std::string& class_name, const ClassType class_type) {
	if (!ifInitialize) {
		entities = new std::map<std::string, Rain::Reflect::ClassType>();
		ifInitialize = true;
	}
	entities->insert(std::pair<std::string, ClassType>(class_name, class_type));
}
Rain::ECS::Entity* Rain::Reflect::GetClass(const std::string& class_name) {
	std::map<std::string, ClassType>::template iterator it = entities->find(class_name);
	return (it != entities->end()) ? it->second() : nullptr;
}