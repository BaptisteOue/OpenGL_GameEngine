#pragma once

#include "coreEngine/IGameLogic.h"

class App : public IGameLogic
{
public:
    App();
    ~App() override;

    void Init() override;
    void Input() override;
    void Update(float Interval) override;
    void Render() override;
	void CleanUp() override;
};
