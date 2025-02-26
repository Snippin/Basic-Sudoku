#pragma once

#include <memory>

template <typename T>
class Singleton
{
    friend T;

public:
    static T *Get()
    {
        if (!instance)
        {
            instance = std::make_unique<T>();
        }

        return instance.get();
    }

    static void Destroy()
    {
        if (instance)
        {
            instance.reset();
        }
    }

private:
    Singleton() = default;
    ~Singleton() = default;

    static std::unique_ptr<T> instance;
};

template <typename T>
std::unique_ptr<T> Singleton<T>::instance = nullptr;
