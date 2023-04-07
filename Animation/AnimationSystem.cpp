#include "AnimationSystem.h"
#include "GeneralAnimationClip.h"
#include "SklAnimClip.h"
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
	InitializeClip("Bounce", AnimType::General);
	InitializeClip("Scale", AnimType::General);
	InitializeClip("BounceLoop", AnimType::General);
	InitializeClip("Squat", AnimType::Skeletal);
	InitializeClip("Run", AnimType::Skeletal);
	InitializeClip("Idle", AnimType::Skeletal);
}

void Rain::Animation::AnimationSystem::InitializeClip(const char* name, AnimType type) {
	
	if (type == AnimType::General) {
		double time;
		std::vector<KeyFramePipeline> pipelines;
		AnimationImporter::LoadAnimation(name, time, pipelines);
		GeneralAnimationClip* clip = nullptr;
		clip = new GeneralAnimationClip(name, time, pipelines);
		generalAnimationClips.insert(std::pair<std::string, GeneralAnimationClip*>(name, clip));
	}
	else if (type == AnimType::Skeletal) {
		double time;
		std::vector<JointAnimCurve> jointsAnimCurve;
		AnimationImporter::LoadSklAnimation(name, time, jointsAnimCurve);
		SklAnimClip* clip = nullptr;
		clip = new SklAnimClip(name, time, jointsAnimCurve);
		skeletalAnimationClips.insert(std::pair<std::string, SklAnimClip*>(name, clip));
	}

	
}
std::shared_ptr<Rain::Animation::GeneralAnimationClip> Rain::Animation::AnimationSystem::GetGeneralClip(const std::string& i_name) {
	if (generalAnimationClips.find(i_name) != generalAnimationClips.end()) {
		return generalAnimationClips.find(i_name)->second;
	}
	return nullptr;
}

std::shared_ptr<Rain::Animation::SklAnimClip> Rain::Animation::AnimationSystem::GetSkeletalClip(const std::string& i_name) {
	if (skeletalAnimationClips.find(i_name) != skeletalAnimationClips.end()) {
		return skeletalAnimationClips.find(i_name)->second;
	}
	return nullptr;
}