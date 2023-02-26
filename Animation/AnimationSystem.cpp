#include "AnimationSystem.h"
#include "AnimationImporter.h"
Rain::Animation::AnimationSystem* Rain::Animation::AnimationSystem::instance;
Rain::Animation::AnimationSystem * Rain::Animation::AnimationSystem::GetInstance() {
	if (instance == nullptr) {
		instance = new AnimationSystem();
		return instance;
	}
	else {
		return instance;
	}
}
Rain::Animation::AnimationSystem::AnimationSystem() {

}
void Rain::Animation::AnimationSystem::Initialize() {
	InitializeClip("Bounce");
}
void Rain::Animation::AnimationSystem::InitializeClip(const char* name) {
	double time;
	std::vector<KeyFramePipeline> pipelines;
	AnimationImporter::LoadAnimation(name, time, pipelines);
	AnimationClip* clip = new AnimationClip(name, time, pipelines);
	animationClips.insert(std::pair<std::string, AnimationClip*>(name, clip));
}
std::shared_ptr<Rain::Animation::AnimationClip> Rain::Animation::AnimationSystem::GetClip(const std::string& i_name) {
	if (animationClips.find(i_name) != animationClips.end()) {
		return animationClips.find(i_name)->second;
	}
	return nullptr;
}