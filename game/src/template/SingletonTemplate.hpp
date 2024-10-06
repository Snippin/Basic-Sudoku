#pragma once

template <typename T>
class Singleton
{
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
            instance = NULL;
        }
    }

protected:
    Singleton()
    {
    }
    ~Singleton()
    {
    }

private:
    static T *instance;
};

template <typename T>
T *Singleton<T>::instance = nullptr;
