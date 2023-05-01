#ifndef  RAIN_ASSET_SCENELOADER
#define  RAIN_ASSET_SCENELOADER
#include <functional>
#include "Lua/Lua.h"
#include <string>
#include "ECS\Entity.h"
#include <memory>
namespace Rain {
	namespace Asset {
		namespace SceneLoader {
			void LoadScene(const char* i_filePath);
			void RegisterComponentCreators();
			//help function
			//----------------
			void LoadSettings(lua_State* i_luaState);
			void LoadEntity(lua_State* i_luaState);
			void LoadComponent(int i_id, lua_State* i_luaState, std::shared_ptr <ECS::Entity> i_entity);
			void RegisterComponentCreator(const std::string& i_ComponentName, std::function<void(int, std::shared_ptr <ECS::Entity> i_entity, lua_State*)> i_ComponentCreator);
		}
	}
}

#endif // ! RAIN_ASSET_SCENELOADER
