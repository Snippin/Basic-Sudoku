#pragma once

class Scene
{
public:
    Scene() {}
    ~Scene() {}

    virtual void Enter() {}
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Exit() {}
};
