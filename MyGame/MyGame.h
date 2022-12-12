#pragma once
#include "Rain3D/Rain3D.h"

namespace Game{
	class MyGame: Rain3D {
		void Initialize();
		void Update();
		void ClearUp();
	};
}