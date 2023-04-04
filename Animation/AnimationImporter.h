#ifndef ASSET_ANIMATIONIMPORTER
#define ASSET_ANIMATIONIMPORTER

#include <functional>
#include "Lua/Lua.h"
#include "Animation\GeneralAnimationClip.h"
#include "Animation\SklAnimClip.h"
namespace Rain {
	namespace Animation {
		class AnimationImporter {
		public:
			static void LoadAnimation(const char* i_filePath, double& time, std::vector<KeyFramePipeline>& pipelines);
			static void LoadSklAnimation(const char* i_filePath, double& time, std::vector<JointAnimCurve>& pipelines);

		private:
			//Helper------
			static void LoadAnimHeader(lua_State* i_luaState, double& start_time, double& end_time);
			static void LoadPipeline(lua_State* i_luaState, const double start_time, std::vector<KeyFramePipeline>& pipelines);
			static void LoadFrames(lua_State* i_luaState, const double start_time, int index, KeyFrame* keyframes);
		};
	}

}


#endif // !ASSET_ANIMATIONIMPORTER

