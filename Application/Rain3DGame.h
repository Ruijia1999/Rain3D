#ifndef RAIN3DGAME
#define RAIN3DGAME

#include <Windows.h>
#include "ECS/Entity.h"
#include <vector>
namespace Rain {
    class Rain3DGame
    {

    public:
        void Initialize(HWND hWnd, int width, int height);
        static void StartGame();
        static void Update();
        static void AddEntity(Rain::ECS::Entity* i_entity);
        void ExitGame();
        void ClearUp();
    };

}

#endif // !1

