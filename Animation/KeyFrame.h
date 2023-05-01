#ifndef RAIN_ANIMATION_KEYFRAME
#define RAIN_ANIMATION_KEYFRAME
#include "Math\Math.h"
namespace Rain {
	namespace Animation {
		enum AnimPipelineType {
			TranslationX,
			TranslationY,
			TranslationZ,
			RotationX,
			RotationY,
			RotationZ,
			ScaleX,
			ScaleY,
			ScaleZ,
			None,
		};

		class KeyFrame
		{
		public:
			float value;
			double time;

		public:
			KeyFrame() {
		 
				value = 0;
				time = 0;
			}
			KeyFrame(float i_value, double i_time) {
				value = i_value;
				time = i_time;
			}
		};
		class KeyFramePipeline
		{
		public:
			AnimPipelineType type;
			int frameCount;
			KeyFrame* keyFrames;

		public:
			KeyFramePipeline() {

			}
			KeyFramePipeline(AnimPipelineType i_type, int i_frameCount, KeyFrame* i_keyFrames) {
				type = i_type;
				frameCount = i_frameCount;
				keyFrames = i_keyFrames;
			}
			void operator=(const KeyFramePipeline& i_pipeline) {
				type = i_pipeline.type;
				frameCount = i_pipeline.frameCount;
				keyFrames = i_pipeline.keyFrames;
			}
		};


	}
}
#endif // !RAIN_ANIMATION_KEYFRAME

