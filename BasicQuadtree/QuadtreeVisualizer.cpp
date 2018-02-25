#include <QuadtreeVisualizer.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

//! Some quadtree constants
constexpr float gNodeWidthInPixel = 2.0F;
constexpr float gObjectToAddSize = 10.0F;

QuadtreeVisualizer::QuadtreeVisualizer()
{
    mWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(mWindowWidth, mWindowHeight), "SFML Quadtree Ornegi");

    sf::FloatRect rootBoundary{ 0, 0, static_cast<float>(mWindowWidth), static_cast<float>(mWindowHeight) };

    mQuadtree = std::make_unique<uBasicQuadtree>(0, rootBoundary);

    mColorList.insert(mColorList.end(), { sf::Color::Red, sf::Color::Blue, sf::Color::Magenta, sf::Color::Black, sf::Color::Yellow, sf::Color::Cyan, sf::Color::Magenta, sf::Color::Black });
}

void QuadtreeVisualizer::Run()
{
    // Oyun dongusunu baslat
    while (mWindow->isOpen())
    {
        // Olaylari isle
        sf::Event event;
        while (mWindow->pollEvent(event))
        {
            // Uygulama/pencere kapama
            if (event.type == sf::Event::Closed)
                mWindow->close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                // Yeni nesne ekleylim tiklanan yere
                sf::FloatRect newObject{ event.mouseButton.x - gObjectToAddSize / 2.0F, event.mouseButton.y - gObjectToAddSize / 2.0F, gObjectToAddSize, gObjectToAddSize };
                mQuadtree->Insert(newObject);
            }
        }

        // Background
        this->DrawBackground();

        // Quadtree yi cizdir
        this->DisplayQuadtree(mQuadtree.get());

        // Pencereyi guncelle
        mWindow->display();
    }
}

void QuadtreeVisualizer::DisplayQuadtree(uBasicQuadtree* currentNode)
{
    if (nullptr != currentNode)
    {
        for (int32_t index = 0; index < 4; ++index)
        {
            uBasicQuadtree* childNode = currentNode->GetChildNode(index);

            if (nullptr != childNode)
            {
                this->DisplayQuadtree(childNode);
            }
        }

        // Display current node as rectangle
        sf::FloatRect boundary = currentNode->GetBoundary();
        sf::RectangleShape rectangle{ sf::Vector2f{boundary.width, boundary.height } };

        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineColor(mColorList[currentNode->GetCurrentLevel() % mColorList.size()]);
        rectangle.setOutlineThickness(gNodeWidthInPixel);
        rectangle.move(sf::Vector2f{ boundary.left, boundary.top });
        mWindow->draw(rectangle);

        // Display objects
        for (auto object : currentNode->GetObjects())
        {
            sf::FloatRect boundary = object;
            sf::RectangleShape rectangle{ sf::Vector2f{ boundary.width, boundary.height } };
            rectangle.setFillColor(sf::Color::Transparent);
            rectangle.setOutlineColor(sf::Color::Green);
            rectangle.setOutlineThickness(2);
            rectangle.move(sf::Vector2f{ sf::Vector2f{ boundary.left, boundary.top } });
            mWindow->draw(rectangle);
        }
    }
}

void QuadtreeVisualizer::DrawBackground()
{
    sf::RectangleShape rectangleShape
    {
        sf::Vector2f{ static_cast<float>(mWindowWidth),
        static_cast<float>(mWindowHeight) }
    };

    rectangleShape.setFillColor(sf::Color::White);
    mWindow->draw(rectangleShape);
}
