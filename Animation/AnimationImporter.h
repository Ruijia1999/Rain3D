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
			static void LoadSklAnimation(const char* i_filePath, double& time, std::vector<JointAnimCurve>& jointsAnimCurv);

		private:
			//Helper------
			static void LoadAnimHeader(lua_State* i_luaState, double& start_time, double& end_time);
			static void LoadJointAnimCurve(lua_State* i_luaState, std::vector<JointAnimCurve>& jointsAnimCurve);
			static void LoadPipeline(lua_State* i_luaState, std::vector<KeyFramePipeline>& pipelines);
			static void LoadFrames(lua_State* i_luaState,  int index, KeyFrame* keyframes);
		};
	}

}


#endif // !ASSET_ANIMATIONIMPORTER

