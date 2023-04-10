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
		};
		struct IndexFormat {
			INT32 x, y, z;
		};

		struct SkeletalIndexFormat {
			INT32 x, y, z;
			INT32 nx, ny, nz;
			INT32 tx, ty, tz;
			INT32 uvx, uvy, uvz;
		};
	}
}