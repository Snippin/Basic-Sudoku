#pragma once

template <typename T>
class Singleton
{
    friend T;

public:
    static T *Get()
    {
        if (instance == nullptr)
        {
            instance = new T();
        }

        return instance;
    }

    static void Destroy()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

private:
    Singleton() = default;
    ~Singleton() = default;

    static T *instance;
};

template <typename T>
T *Singleton<T>::instance = nullptr;
