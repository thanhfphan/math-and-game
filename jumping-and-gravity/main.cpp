#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

const int WIDTH = 1200;
const int HEIGHT = 900;
const int FIXVALUE = 200;
const sf::Time TIMER_PER_FRAME = sf::seconds(1.f / 60.f);
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
sf::Texture texture;
sf::Sprite sprite;
sf::Vector2f gravity(0, 600);
sf::Vector2f velocity(0,0);
void processEvent()
{
	sf::Event event;
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
				velocity.x = -40;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				velocity.x = +40;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				velocity.y = -200;
			}
			break;
		}
		case sf::Event::KeyReleased:
		{
			if (event.key.code ==  sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
			{
				velocity.x = 0;
			}
			else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
			{
				velocity.x = 0;
			}

			break;
		}
		default:
			break;
		}
	}
}

void update()
{
	sf::Vector2f currentPosition = sprite.getPosition();
	currentPosition += velocity * (float)15*TIMER_PER_FRAME.asSeconds();
	std::cout << velocity.x << " " << velocity.y << std::endl;
	if (currentPosition.y < HEIGHT - FIXVALUE)
	{
		currentPosition += gravity * (float)20* TIMER_PER_FRAME.asSeconds();
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
}

void render()
{
	window.clear();

	window.draw(sprite);
	window.display();
}

int main()
{
	if (!texture.loadFromFile("images/Idle (1).png"))
		return EXIT_FAILURE;
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.3, 0.3));
	sprite.setPosition(sf::Vector2f(0, HEIGHT - FIXVALUE - 800));
	sf::Vector2f velocity(0, 400);
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIMER_PER_FRAME)
		{
			timeSinceLastUpdate -= TIMER_PER_FRAME;

			processEvent();
			update();
		}

		render();
	}
	return EXIT_SUCCESS;
}