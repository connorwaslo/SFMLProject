#pragma once
#include <SFML/Graphics.hpp>

class CSource
{
public:
	CSource(void);
	~CSource(void);
	void GameLoop(void);
	void Keyboard(void);

	void LoadTextures(void);
	void LoadVariables(void);

	enum {
		UP, DOWN, LEFT, RIGHT
	};

private:
	int sourceX;
	int sourceY;

	float moveSpeed;

	float frameCounter;
	float switchFrame;
	float frameSpeed;

	sf::Vector2i source;
	sf::Vector2i screenDim;

	sf::Vector2f position;

	sf::View view;

	sf::RenderWindow window;

	sf::Clock clock;
	sf::Time time;

	sf::Texture pTexture;
	sf::Sprite pImage;
	sf::Texture bTexture;
	sf::Sprite bImage;

	sf::RectangleShape rectHorzTop;
	sf::RectangleShape rectHorzBot;

	sf::RectangleShape rectVertLeft;
	sf::RectangleShape rectVertRight;
};

