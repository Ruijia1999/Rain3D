#pragma once
namespace Rain {
	namespace Render {
		struct StaticVertexFormat {
			float x, y, z;
			float nx, ny, nz;
			float tx, ty, tz;
			float u, v;
		};
		struct SkeletalVertexFormat {
			float x, y, z;
			float nx, ny, nz;
			float tx, ty, tz;
			float u, v;
			INT8 i0, i1, i2, i3; //The index of joint;
			float w0, w1, w2; //The weight of joint;
		};
		struct IndexFormat {
			INT32 x, y, z;
		};
	}
}