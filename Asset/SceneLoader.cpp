#include "SceneLoader.h"
#include <map>
#include <string>
#include "EngineLog/EngineLog.h"
#include "MeshRender/MeshRender.h"
#include "Math/Math.h"
#include "ECS/Entity.h"
#include "Reflect/Reflect.h"
#include "GameObject/GameObjectSystem.h"
#include "Transform/TransformSystem.h"
#include "Collision/ColliderSystem.h"
#include "Collision/ColliderBase.h"
#include "Application/Rain3DGame.h"

namespace {
	std::map<std::string, std::function<void(int, lua_State*)>> m_componentCreators;
}

void Rain::Asset::SceneLoader::LoadScene(const char* i_filePath) {
	lua_State* L = luaL_newstate();
	auto i = luaL_dofile(L, "test.lua");
#pragma region Settings
	lua_getglobal(L, "settings");
	LoadSettings(L);
	
#pragma endregion
#pragma region Entities
	lua_getglobal(L, "entities");
	int n = luaL_len(L, -1);
	for (int i = 1; i <= n; ++i) {
		lua_rawgeti(L, -1, i);
		LoadEntity(L);
		lua_pop(L, 1);
	}
#pragma endregion

}
void Rain::Asset::SceneLoader::LoadSettings(lua_State* i_luaState) {
	Math::Vector3 cameraPos;
	Math::Quaternion cameraRot;
	

	lua_pushstring(i_luaState, "camera");
	lua_gettable(i_luaState, -2);
	lua_pushstring(i_luaState, "rotation");
	lua_gettable(i_luaState, -2);
	for (int i = 1; i <= 4; ++i) {
		lua_rawgeti(i_luaState, -1, i);
		cameraRot[i - 1] = lua_tonumber(i_luaState, -1);
		lua_pop(i_luaState, 1);
	}
	lua_pop(i_luaState, 1);

	lua_pushstring(i_luaState, "position");
	lua_gettable(i_luaState, -2);
	for (int i = 1; i <= 3; ++i) {
		lua_rawgeti(i_luaState, -1, i);
		cameraPos[i - 1] = lua_tonumber(i_luaState, -1);
		lua_pop(i_luaState, 1);
	}
	lua_pop(i_luaState, 1);

	Rain::Rain3DGame::InitializeSettings(cameraPos, cameraRot, cameraPos);
}

void Rain::Asset::SceneLoader::LoadEntity(lua_State* i_luaState) {
	int id;
	std::string script;
	std::string tag;
	std::string name;

	lua_pushstring(i_luaState, "id");
	lua_gettable(i_luaState, -2);
	id = lua_tointeger(i_luaState, -1);
	lua_pop(i_luaState, 1);


	lua_pushstring(i_luaState, "script");
	lua_gettable(i_luaState, -2);
	script = lua_tostring(i_luaState, -1);
	lua_pop(i_luaState, 1);

	lua_pushstring(i_luaState, "tag");
	lua_gettable(i_luaState, -2);
	tag = lua_tostring(i_luaState, -1);
	lua_pop(i_luaState, 1);

	lua_pushstring(i_luaState, "name");
	lua_gettable(i_luaState, -2);
	name = lua_tostring(i_luaState, -1);
	lua_pop(i_luaState, 1);

	lua_pushstring(i_luaState, "components");
	lua_gettable(i_luaState, -2);
	int n = luaL_len(i_luaState, -1);
	
	for (int i = 1; i <= n; ++i) {
		lua_rawgeti(i_luaState, -1, i);
		LoadComponent(id, i_luaState);
		lua_pop(i_luaState, 1);
	}
	lua_pop(i_luaState, 1);

	ECS::Entity* entity = Rain::Reflect::GetClass(script);
	Rain::Rain3DGame::AddEntity(entity);
	if(entity!=nullptr)
	entity->Initialize(id,tag,name);
}

void Rain::Asset::SceneLoader::LoadComponent(int i_id, lua_State* i_luaState) {
	
	
	lua_pushstring(i_luaState, "component");
	lua_gettable(i_luaState, -2);
	std::string component = lua_tostring(i_luaState, -1);
	lua_pop(i_luaState, 1);
	m_componentCreators.find(component)->second(i_id, i_luaState);
}
void Rain::Asset::SceneLoader::RegisterComponentCreators() {
	int j = 0;
#pragma region GameObjectComponent
	RegisterComponentCreator("GameObject", [](int i_id, lua_State* i_luaState) {

		lua_pushstring(i_luaState, "isActive");
		lua_gettable(i_luaState, -2);
		bool isActive = lua_toboolean(i_luaState, -1);
		lua_pop(i_luaState, 1);

		lua_pushstring(i_luaState, "isVisible");
		lua_gettable(i_luaState, -2);
		bool isVisible = lua_toboolean(i_luaState, -1);
		lua_pop(i_luaState, 1);

		GameObject::GameObjectSystem::GetInstance()->AddComponent(new GameObject::GameObjectComponent(i_id,isActive,isVisible,"name","tag"));

		}
	);
#pragma endregion

#pragma region TransformComponent
	RegisterComponentCreator("Transform", [](int i_id, lua_State* i_luaState) {
		Math::Vector3 position;
		lua_pushstring(i_luaState, "position");
		lua_gettable(i_luaState, -2);
		for (int i = 1; i <= 3; ++i) {
			lua_rawgeti(i_luaState, -1, i);
			position[i-1] = lua_tonumber(i_luaState,-1); 
			lua_pop(i_luaState, 1);
		}
		lua_pop(i_luaState, 1);

		Math::Quaternion rotation;
		lua_pushstring(i_luaState, "rotation");
		lua_gettable(i_luaState, -2);
		for (int i = 1; i <= 4; ++i) {
			lua_rawgeti(i_luaState, -1, i);
			rotation[i - 1] = lua_tonumber(i_luaState, -1);
			lua_pop(i_luaState, 1);
		}
		lua_pop(i_luaState, 1);

		Transform::TransformSystem::GetInstance()->AddComponent(new Transform::TransformComponent(i_id,position,position,rotation));
		}
	);
#pragma endregion

#pragma region MeshRender
	RegisterComponentCreator("MeshRender", [](int i_id, lua_State* i_luaState) {
		Render::Mesh* mesh;
		lua_pushstring(i_luaState, "mesh");
		lua_gettable(i_luaState, -2);
		std::string mesh_name = lua_tostring(i_luaState,-1);
		lua_pop(i_luaState, 1);
		MeshRender::MeshRenderSystem* n = MeshRender::MeshRenderSystem::GetInstance();
		mesh = MeshRender::MeshRenderSystem::GetInstance()->meshes.find(mesh_name)->second;

		Render::Effect* effect;
		lua_pushstring(i_luaState, "effect");
		lua_gettable(i_luaState, -2);
		std::string effect_name = lua_tostring(i_luaState,-1);
		lua_pop(i_luaState, 1);
		effect = MeshRender::MeshRenderSystem::GetInstance()->effects.find(effect_name)->second;

		Math::Vector4 color;
		lua_pushstring(i_luaState, "color");
		lua_gettable(i_luaState, -2);
		for (int i = 1; i <= 4; ++i) {
			lua_rawgeti(i_luaState, -1, i);
			color[i - 1] = lua_tonumber(i_luaState, -1)/255.0f;
			lua_pop(i_luaState, 1);
		}
		lua_pop(i_luaState, 1);

		MeshRender::MeshRenderSystem::GetInstance()->AddComponent(new MeshRender::MeshRenderComponent(i_id, mesh, effect,color));
		}
	);
#pragma endregion

#pragma region Collider
	RegisterComponentCreator("Collider", [](int i_id, lua_State* i_luaState) {
		
		lua_pushstring(i_luaState, "type");
		lua_gettable(i_luaState, -2);
		std::string type = lua_tostring(i_luaState, -1);
		lua_pop(i_luaState, 1);

		ColliderSystem::GetInstance()->AddComponent(new ColliderComponent(i_id, type.c_str()));
		}
	);
#pragma endregion
}

void Rain::Asset::SceneLoader::RegisterComponentCreator(const std::string& i_ComponentName, std::function<void(int, lua_State*)> i_ComponentCreator) {
	m_componentCreators.insert(std::pair<std::string, std::function<void(int, lua_State*)>>(i_ComponentName, i_ComponentCreator));
}