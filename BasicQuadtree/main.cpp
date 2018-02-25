#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <QuadtreeVisualizer.h>

int main()
{
    // Ornek uygulamamiz
    std::unique_ptr<QuadtreeVisualizer> appInstance = std::make_unique<QuadtreeVisualizer>();

    // Uygulamamizi calistiralim
    appInstance->Run();

    return EXIT_SUCCESS;
}