#ifndef RRAIN3DGAME
#define RRAIN3DGAME

#include <Windows.h>
class Rain3DGame 
{

public:
    void Initialize(HWND hWnd, int width, int height);
    static void StartGame();
    static void Update();
    void ClearUp();
};

#endif // !1

