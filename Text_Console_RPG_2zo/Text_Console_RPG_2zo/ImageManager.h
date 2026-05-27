#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>



void PrintImage(const std::string& fileName)
{
    sf::Texture image;
    if (!image.loadFromFile(fileName))
    {
        std::cout << "이미지 로드 실패\n";
        return;
    }

    std::string name = fileName;
    std::string title = name.erase(0, 6);

    sf::Vector2u size = image.getSize();

    sf::RenderWindow window(
        sf::VideoMode(size.x, size.y),
        title,
        sf::Style::Titlebar | sf::Style::Close
    );

    sf::Sprite imageSprite;
    imageSprite.setTexture(image);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color(0, 0, 0));
        window.draw(imageSprite);
        window.display();
    }
}
