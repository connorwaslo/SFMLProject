#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Source.h"

CSource::CSource(void)
{
	CSource::LoadVariables();

	window.create(sf::VideoMode(screenDim.x, screenDim.y), "SFML works!");
	window.setPosition(sf::Vector2i(400, 100));
	window.setTitle("Tic-Tac-Toe");

	view.reset(sf::FloatRect(0, 0, screenDim.x, screenDim.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	CSource::LoadTextures();

	CSource::GameLoop();
}

CSource::~CSource(void)
{
}

void CSource::GameLoop(void)
{
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			default:
				break;
			}
		}

		CSource::Keyboard();

		frameCounter += frameSpeed * clock.restart().asSeconds();
		if (frameCounter >= switchFrame)
		{
			frameCounter = 0;
			source.x++;
			if(source.x * 32 >= pTexture.getSize().x)
				source.x = 0;
		}

		time = clock.getElapsedTime();

		position.x = pImage.getPosition().x + 10 - (screenDim.x / 2);
		position.y = pImage.getPosition().y + 10 - (screenDim.y / 2);

		if (position.x < 0)
			position.x = 0;
		if(position.y < 0)
			position.y = 0;

		window.clear();

		view.reset(sf::FloatRect(position.x, position.y, screenDim.x, screenDim.y));
		window.setView(view);

		pImage.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));
		window.draw(bImage);
		window.draw(pImage);
		
		window.display();
	}
}

void CSource::Keyboard(void)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		source.y = UP;
		pImage.move(0, -moveSpeed * clock.getElapsedTime().asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		source.y = DOWN;
		pImage.move(0, moveSpeed * clock.getElapsedTime().asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		source.y = LEFT;
		pImage.move(-moveSpeed * clock.getElapsedTime().asSeconds(), 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		source.y = RIGHT;
		pImage.move(moveSpeed * clock.getElapsedTime().asSeconds(), 0);
	}
}

void CSource::LoadVariables(void)
{
	screenDim.x = 800;
	screenDim.y = 600;

	position.x = 0;
	position.y = 0;

	moveSpeed = 180.0f;

	sourceX = 32;
	sourceY = DOWN;

	source.x = 1;
	source.y = DOWN;

	frameCounter = 0;
	switchFrame = 100;
	frameSpeed = 500;
}

void CSource::LoadTextures(void)
{
	if(!pTexture.loadFromFile("player.png"))
		std::cout << "Could not load player image" << std::endl;

	pImage.setTexture(pTexture);
	pImage.setPosition((screenDim.x / 2) - (source.x / 2), (screenDim.y / 2) - (source.y / 2));

	if (!bTexture.loadFromFile("background.png"))
		std::cout << "Could not load background image" << std::endl;

	bImage.setTexture(bTexture);
	bImage.setPosition(0, 0);
}

int main()
{
	CSource::CSource();

    return 0;
}
