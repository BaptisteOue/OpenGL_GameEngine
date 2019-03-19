#pragma once

#include "Window.h"

class IGameLogic
{
public:
    IGameLogic() {}
	virtual ~IGameLogic() {}

    virtual void Init() = 0;
    virtual void Input(Window& window) = 0;
    virtual void Update(float interval) = 0;
    virtual void Render() = 0;
    virtual void CleanUp() = 0;
};
