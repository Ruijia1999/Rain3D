#include "AnimationImporter.h"


void Rain::Animation::AnimationImporter::LoadAnimation(const char* i_filePath, double& time, std::vector<KeyFramePipeline>& pipelines) {
	lua_State* L = luaL_newstate();
	std::string filePath = "animations/";
	filePath.append(i_filePath);
	filePath.append(".hrjAnim");
	auto ret = luaL_dofile(L, filePath.c_str());
	
	double startTime;
	double endTime;
	LoadAnimHeader(L, startTime, endTime);

	lua_getglobal(L, "pipeline");
	int n = luaL_len(L, -1);
	for (int i = 1; i <= n; ++i) {
		lua_rawgeti(L, -1, i);
		LoadPipeline(L, startTime, pipelines);
		lua_pop(L, 1);
	}
	
}
void Rain::Animation::AnimationImporter::LoadSklAnimation(const char* i_filePath, double& time, std::vector<JointAnimCurve>& pipelines) {

}
void Rain::Animation::AnimationImporter::LoadAnimHeader(lua_State* i_luaState, double& start_time, double& end_time) {
	lua_getglobal(i_luaState, "startTime");
	start_time = lua_tonumber(i_luaState, -1);
	lua_pop(i_luaState, 1);
	lua_getglobal(i_luaState, "endTime");
	end_time = lua_tonumber(i_luaState, -1);
	lua_pop(i_luaState, 1);

}

void Rain::Animation::AnimationImporter::LoadPipeline(lua_State* i_luaState, const double start_time, std::vector<KeyFramePipeline>& pipelines) {
	lua_pushstring(i_luaState, "name");
	lua_gettable(i_luaState, -2);
	std::string type = lua_tostring(i_luaState, -1);
	lua_pop(i_luaState, 1);
	AnimPipelineType pipelineType = AnimPipelineType::None;
	
	if (type.compare("translateX") == 0) {
		pipelineType = AnimPipelineType::TranslationX;
	} else if (type.compare("translateY") == 0) {
		pipelineType = AnimPipelineType::TranslationY;
	} else if (type.compare("translateZ") == 0) {
		pipelineType = AnimPipelineType::TranslationZ;
	} else if (type.compare("rotateX") == 0) {
		pipelineType = AnimPipelineType::RotationX;
	} else if (type.compare("rotateY") == 0) {
		pipelineType = AnimPipelineType::RotationY;
	} else if (type.compare("rotateZ")==0){
		pipelineType = AnimPipelineType::RotationZ;
	} else if (type.compare("scaleX") == 0) {
		pipelineType = AnimPipelineType::ScaleX;
	} else if (type.compare("scaleY") == 0) {
		pipelineType = AnimPipelineType::ScaleY;
	} else if (type.compare("scaleZ") == 0) {
		pipelineType = AnimPipelineType::ScaleZ;
	} else {
		return;
	}

	lua_pushstring(i_luaState, "frameCount");
	lua_gettable(i_luaState, -2);
	int frameCount = lua_tointeger(i_luaState, -1);
	lua_pop(i_luaState, 1);

	KeyFrame* keyframes = new KeyFrame[frameCount];
	lua_pushstring(i_luaState, "frames");
	lua_gettable(i_luaState, -2);
	int n = luaL_len(i_luaState, -1);
	for (int i = 1; i <= n; ++i) {
		lua_rawgeti(i_luaState, -1, i);
		LoadFrames(i_luaState, start_time, i-1, keyframes);
		lua_pop(i_luaState, 1);
	}
	lua_pop(i_luaState, 1);

	KeyFramePipeline pipleLine = KeyFramePipeline(pipelineType, frameCount, keyframes);
	pipelines.push_back(pipleLine);
}
void Rain::Animation::AnimationImporter::LoadFrames(lua_State* i_luaState, const double start_time,int index, KeyFrame* keyframes) {
	lua_rawgeti(i_luaState, -1, 1);
	double time = lua_tointeger(i_luaState, -1);
	lua_pop(i_luaState, 1);

	lua_rawgeti(i_luaState, -1, 2);
	float value= lua_tonumber(i_luaState, -1);
	lua_pop(i_luaState, 1);

	KeyFrame keyframe = KeyFrame(value, time);
	keyframes[index] = keyframe;
}