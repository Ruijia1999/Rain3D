#ifndef  RAIN_ASSET_SCENELOADER
#define  RAIN_ASSET_SCENELOADER
#include <functional>
#include "Lua/Lua.h"
#include <string>
namespace Rain {
	namespace Asset {
		namespace SceneLoader {
			void LoadScene(const char* i_filePath);
			void RegisterComponentCreators();
			//help function
			//----------------
			void LoadEntity(lua_State* i_luaState);
			void LoadComponent(int i_id, lua_State* i_luaState);
			void RegisterComponentCreator(const std::string& i_ComponentName, std::function<void(int, lua_State*)> i_ComponentCreator);
		}
	}
}

#endif // ! RAIN_ASSET_SCENELOADER
