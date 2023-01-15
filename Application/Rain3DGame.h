#ifndef RAIN3DGAME
#define RAIN3DGAME

#include <Windows.h>
#include "ECS/Entity.h"
#include "Math/Math.h"
#include <vector>
namespace Rain {
    class Rain3DGame
    {

    public:
        void Initialize(HWND hWnd, int width, int height);
        static void StartGame();
        static void Update();
        static void AddEntity(Rain::ECS::Entity* i_entity);
        static ECS::Entity* GetEntity(int i_id);
        static void InitializeSettings(Math::Vector3 ligthDirection = Math::Vector3(0,0,1), Math::Quaternion i_cameraRot = Math::Quaternion(0, 0, 0,1), Math::Vector3 i_cameraPos = Math::Vector3(0,0,-60));
        void ExitGame();
        static void ClearUp();
    };

}

#endif // !1

