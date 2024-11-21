#include "core/Application.hpp"

int main()
{
    Application *app = Application::Get();
    app->Initialise();
    app->Run();
    app->Exit();

    return 0;
}
