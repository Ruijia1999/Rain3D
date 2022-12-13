#ifndef  RAIN_ASSET_SCENELOADER
#define  RAIN_ASSET_SCENELOADER
#include <functional>
#include "LUA/LUA.h"
namespace Rain {
	namespace Asset {
		namespace SceneLoader {
			void LoadScene(const char* i_filePath);
			void RegisterComponentCreators();
			void RegisterComponentCreator(const char* i_ComponentName, std::function<void> i_ComponentCreator);
		}
	}
}

#endif // ! RAIN_ASSET_SCENELOADER
