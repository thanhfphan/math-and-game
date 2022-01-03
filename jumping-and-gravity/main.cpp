#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

const int WIDTH = 1200;
const int HEIGHT = 900;
const int FIXVALUE = 200;
int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
	sf::Texture texture;
	if (!texture.loadFromFile("images/Idle (1).png"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);
	sprite.setScale(sf::Vector2f(0.3, 0.3));
	sprite.setPosition(sf::Vector2f(0, HEIGHT - FIXVALUE - 800));
	sf::Vector2f gravity(0, 600);
	sf::Vector2f velocity(0, 400);
	sf::Clock deltaClock;
	sf::Time currentTime;
	// sf::Time deltaTime;
	while (window.isOpen())
	{
		sf::Vector2f currentPosition = sprite.getPosition();
		sf::Event event;
		currentTime = deltaClock.getElapsedTime();
		deltaClock.restart();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			switch (event.type)
			{
			case sf::Event::KeyPressed:
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					currentPosition.x -= 40;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					currentPosition.x += 40;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					currentPosition += -velocity;
				}

				break;
			}
			default:
				break;
			}
		}

		if (currentPosition.y < HEIGHT - FIXVALUE)
		{
			currentPosition += gravity * currentTime.asSeconds();
			// std::cout << deltaTime.asSeconds() << std::endl;
			// std::cout << "velocity: x= " << currentPosition.x << " velocity:y= " << currentPosition.y << std::endl;
			// std::cout << "x= " << gravity.x << " y= " << gravity.y << std::endl;
		}
		if (currentPosition.y < 0)
		{
			currentPosition.y = 0;
		}
		if (currentPosition.y > HEIGHT - FIXVALUE)
		{
			currentPosition.y = HEIGHT - FIXVALUE;
		}
		if (currentPosition.x < 0)
		{
			currentPosition.x = 0;
		}
		if (currentPosition.x > WIDTH - FIXVALUE)
		{
			currentPosition.x = WIDTH - FIXVALUE;
		}

		sprite.setPosition(currentPosition.x, currentPosition.y);
		window.clear();

		window.draw(sprite);
		window.display();
	}
	return EXIT_SUCCESS;
}