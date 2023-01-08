#ifndef RRAIN3DGAME
#define RRAIN3DGAME

#include <Windows.h>
#include "ECS/Entity.h"
#include <vector>
class Rain3DGame 
{

public:

    void Initialize(HWND hWnd, int width, int height);
    static void StartGame();
    static void Update();
    void ExitGame();
    void ClearUp();
};

#endif // !1

