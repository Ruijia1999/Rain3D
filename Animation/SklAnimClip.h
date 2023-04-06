#ifndef RAIN_ANIMATION_SKLANIM
#define RAIN_ANIMATION_SKLANIM
#include "Math\Math.h"
#include "KeyFrame.h"
#include "Transform\TransformSystem.h"
#include "MeshRender\MeshRenderSystem.h"
#include "Math\Quaternion.h"
#include <string>
#include <unordered_map>
namespace Rain {
	namespace Animation {
		struct JointAnimCurve {
			std::string jointName;
			std::vector<KeyFramePipeline> pipelines;
		};

		class SklAnimClip
		{
		public:
			std::string name;
			double time;
			std::vector<JointAnimCurve> jointsAnim;


		public:
			SklAnimClip() {

			}
			SklAnimClip(const std::string& i_name, const double i_time, const std::vector<JointAnimCurve> &i_jointsAnim) {
				name = i_name;
				time = i_time;
				jointsAnim=i_jointsAnim;
			}
			void Initialize();
			bool Update(bool loop, int& i_frame, double& i_time, double i_timeSinceLastFrame, Math::Vector3& i_velTranslate, Math::Quaternion& previousRotate, Math::Quaternion& nextRotate, MeshRender::MeshRenderComponent* i_sklMesh);
			float GetValue(bool loop, int i_frame, double i_time, int i_jointIndex, AnimPipelineType i_type);
			float GetTransValue(bool loop, int i_frame, int i_jointIndex, AnimPipelineType i_type);
			Math::Quaternion GetRotateValue(bool loop, int i_frame, int i_time, int i_jointIndex);
			float GetSlope(bool loop, int i_frame, int i_jointIndex, AnimPipelineType i_type);

			//Helper----
			int GetPipeline(AnimPipelineType i_type);
			void UpdateMesh(bool loop, int i_frame, double i_time, Math::Vector3& velTranslate, Math::Quaternion& velRotate, Math::Vector3& velScale, Transform::TransformComponent* transform);
			void Slerp(const Math::Quaternion& quaternion1, const Math::Quaternion& quaternion2, float i_time, Math::Quaternion& quaternion);
		};
	}
}


#endif