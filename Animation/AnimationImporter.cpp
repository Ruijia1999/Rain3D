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
	pipelines.resize(9);
	for (int i = 1; i <= n; ++i) {
		lua_rawgeti(L, -1, i);
		LoadPipeline(L,  pipelines);
		lua_pop(L, 1);
	}
	
}
void Rain::Animation::AnimationImporter::LoadSklAnimation(const char* i_filePath, double& time, std::vector<JointAnimCurve>& jointsAnimCurve) {
	lua_State* L = luaL_newstate();
	std::string filePath = "animations/";
	filePath.append(i_filePath);
	filePath.append(".hrjSklAnim");
	auto ret = luaL_dofile(L, filePath.c_str());

	double startTime;
	double endTime;
	LoadAnimHeader(L, startTime, endTime);

	lua_getglobal(L, "animationData");
	int n = luaL_len(L, -1);
	for (int i = 1; i <= n; ++i) {
		lua_rawgeti(L, -1, i);
		LoadJointAnimCurve(L, jointsAnimCurve);
		lua_pop(L, 1);
	}
}
void Rain::Animation::AnimationImporter::LoadAnimHeader(lua_State* i_luaState, double& start_time, double& end_time) {
	lua_getglobal(i_luaState, "startTime");
	start_time = lua_tonumber(i_luaState, -1);
	lua_pop(i_luaState, 1);
	lua_getglobal(i_luaState, "endTime");
	end_time = lua_tonumber(i_luaState, -1);
	lua_pop(i_luaState, 1);

}
void Rain::Animation::AnimationImporter::LoadJointAnimCurve(lua_State* i_luaState, std::vector<JointAnimCurve>& jointsAnimCurve) {
	JointAnimCurve animCurve;

	lua_pushstring(i_luaState, "joint");
	lua_gettable(i_luaState, -2);
	animCurve.jointName = lua_tostring(i_luaState, -1);
	lua_pop(i_luaState, 1);

	

	lua_pushstring(i_luaState, "pipeline");
	lua_gettable(i_luaState, -2);
	int n = luaL_len(i_luaState, -1);
	animCurve.pipelines.resize(9);
	for (int i = 1; i <= n; ++i) {
		lua_rawgeti(i_luaState, -1, i);
		LoadPipeline(i_luaState, animCurve.pipelines);
		lua_pop(i_luaState, 1);
	}
	lua_pop(i_luaState, 1);
	jointsAnimCurve.push_back(animCurve);

}
void Rain::Animation::AnimationImporter::LoadPipeline(lua_State* i_luaState, std::vector<KeyFramePipeline>& pipelines) {
	lua_pushstring(i_luaState, "name");
	lua_gettable(i_luaState, -2);
	std::string type = lua_tostring(i_luaState, -1);
	lua_pop(i_luaState, 1);
	AnimPipelineType pipelineType = AnimPipelineType::None;
	int index = -1;
	if (type.compare("translateX") == 0) {
		pipelineType = AnimPipelineType::TranslationX;
		index = 0;
	} else if (type.compare("translateY") == 0) {
		pipelineType = AnimPipelineType::TranslationY;
		index = 1;
	} else if (type.compare("translateZ") == 0) {
		pipelineType = AnimPipelineType::TranslationZ;
		index = 2;
	} else if (type.compare("rotateX") == 0) {
		pipelineType = AnimPipelineType::RotationX;
		index = 3;
	} else if (type.compare("rotateY") == 0) {
		pipelineType = AnimPipelineType::RotationY;
		index = 4;
	} else if (type.compare("rotateZ")==0){
		pipelineType = AnimPipelineType::RotationZ;
		index = 5;
	} else if (type.compare("scaleX") == 0) {
		pipelineType = AnimPipelineType::ScaleX;
		index = 6;
	} else if (type.compare("scaleY") == 0) {
		pipelineType = AnimPipelineType::ScaleY;
		index = 7;
	} else if (type.compare("scaleZ") == 0) {
		pipelineType = AnimPipelineType::ScaleZ;
		index = 8;
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
		LoadFrames(i_luaState, i-1, keyframes);
		lua_pop(i_luaState, 1);
	}
	lua_pop(i_luaState, 1);

	KeyFramePipeline pipleLine = KeyFramePipeline(pipelineType, frameCount, keyframes);
	pipelines[index]= pipleLine;
}
void Rain::Animation::AnimationImporter::LoadFrames(lua_State* i_luaState, int index, KeyFrame* keyframes) {
	lua_rawgeti(i_luaState, -1, 1);
	double time = lua_tointeger(i_luaState, -1);
	lua_pop(i_luaState, 1);

	lua_rawgeti(i_luaState, -1, 2);
	float value= lua_tonumber(i_luaState, -1);
	lua_pop(i_luaState, 1);

	KeyFrame keyframe = KeyFrame(value, time);
	keyframes[index] = keyframe;
}