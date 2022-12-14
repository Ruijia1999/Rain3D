#include "SceneLoader.h"
#include <map>
#include <string>
#include "EngineLog/EngineLog.h"
#include "Math/Math.h"
namespace {
	std::map<std::string, std::function<void(int, lua_State*)>> m_componentCreators;
}
void Rain::Asset::SceneLoader::LoadScene(const char* i_filePath) {
	lua_State* L = luaL_newstate();
	auto i = luaL_dofile(L, "test.lua");

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
void Rain::Asset::SceneLoader::LoadEntity(lua_State* i_luaState) {
	int id;

	lua_pushstring(i_luaState, "id");
	lua_gettable(i_luaState, -2);
	id = lua_tointeger(i_luaState, -1);
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

}

void Rain::Asset::SceneLoader::LoadComponent(int i_id, lua_State* i_luaState) {
	
	
	lua_pushstring(i_luaState, "component");
	lua_gettable(i_luaState, -2);
	std::string component = lua_tostring(i_luaState, -1);
	lua_pop(i_luaState, 1);
	m_componentCreators.find(component)->second(i_id, i_luaState);
}
void Rain::Asset::SceneLoader::RegisterComponentCreators() {

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
#pragma region GameObjectComponent
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

		Transform::TransformSystem::GetInstance()->AddComponent(new Transform::TransformComponent(i_id,position,position,position));
		}
	);
#pragma endregion

}

void Rain::Asset::SceneLoader::RegisterComponentCreator(const std::string& i_ComponentName, std::function<void(int, lua_State*)> i_ComponentCreator) {
	m_componentCreators.insert(std::pair<std::string, std::function<void(int, lua_State*)>>(i_ComponentName, i_ComponentCreator));
}