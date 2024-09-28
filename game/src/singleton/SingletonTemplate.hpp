#pragma once

template <typename T>
class Singleton
{
public:
    static T *Get()
    {
        if (s_instance == nullptr)
        {
            s_instance = new T();
        }

        return s_instance;
    }

    static void Destroy()
    {
        if (s_instance)
        {
            delete s_instance;
            s_instance = NULL;
        }
    }

protected:
    Singleton() {}
    ~Singleton() {}

private:
    static T *s_instance;
};

template <typename T>
T *Singleton<T>::s_instance = nullptr;
