/**
 * \file    QuadtreeVisualizer.h
 * \date    2018/02/25
 * \author  yazilimperve
 * \brief   
 */
#ifndef QUADTREEVISUALIZER_H__
#define QUADTREEVISUALIZER_H__

#include <BasicQuadtree.h>
#include <SFML/Graphics/RenderWindow.hpp>

class QuadtreeVisualizer
{
public:
    QuadtreeVisualizer();

    //! Ana uygulama dongusu
    void Run();
private:

    //! Quadtree'yi gorsellestirme
    void DisplayQuadtree(BasicQuadtree* currentNode);

    //! Arka plan cizdirme
    void DrawBackground();

    //! Temel quadtree nesnemiz
    std::unique_ptr<BasicQuadtree> mQuadtree;

    //! SFML penceremiz
    const uint32_t mWindowWidth = 800;
    const uint32_t mWindowHeight = 600;
    std::unique_ptr<sf::RenderWindow> mWindow;

    //! Kullanilacak olan renkler
    std::vector<sf::Color> mColorList;
};

#endif // QUADTREEVISUALIZER_H__
