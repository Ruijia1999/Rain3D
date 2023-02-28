#ifndef RAIN_ANIMATIONCLIP_H
#define RAIN_ANIMATIONCLIP_H
#include <vector>
#include <string>
#include "SklChannel.h"
#include "Animation\KeyFrame.h"
#include "Transform\TransformComponent.h"
namespace Rain {
	namespace Animation {
		class AnimationClip {

			std::string name;
			double time;
			std::vector<KeyFramePipeline> pipelines;
			//std::vector<SklChannel> channels;

		public:
			AnimationClip(const std::string& i_name, const double i_time, const std::vector<KeyFramePipeline>& i_pipelines) {
				name = i_name;
				time = i_time;
				pipelines = i_pipelines;
			}
			void Initialize();
			bool Update(bool loop, int& i_frame, double& i_time, double i_timeSinceLastFrame, Math::Vector3& velTranslate, Math::Vector3& velScale, Transform::TransformComponent* transform);
			float GetValue(bool loop, int i_frame, double i_time, AnimPipelineType i_type);
			float GetSlope(bool loop, int i_frame, AnimPipelineType i_type);

			//Helper----
			int GetPipeline(AnimPipelineType i_type);
			void UpdateTransform(bool loop, int i_frame, double i_time, Math::Vector3& velTranslate, Math::Vector3& velScale, Transform::TransformComponent* transform);
		};
	}
}
#endif // !RAIN_ANIMATION_H
