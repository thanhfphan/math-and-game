#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

const int WIDTH = 1200;
const int HEIGHT = 900;
const int FIXVALUE = 200;
//347x550
sf::IntRect area = sf::IntRect(159, 28, 384, 550);
const sf::Time TIMER_PER_FRAME = sf::seconds(1.f / 60.f);
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
sf::Texture texture;
sf::Sprite player;
sf::Image santaImage;
sf::Vector2f gravity(0, 150);
sf::Vector2f moveDirection(1, 1);
sf::Vector2f velocity(0, 0);
bool faceRight = true;
bool isMoving = false;
float duration = 0;

sf::Texture runningRight[11];
sf::Texture runningLeft[11];
sf::Texture idleRight[16];
sf::Texture idleLeft[16];
int runningFrameCount = 0;
int idleFrameCount = 0;

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
				faceRight = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				velocity.x = +40;
				faceRight = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				velocity.y = -800;
			}
			break;
		}
		case sf::Event::KeyReleased:
		{
			if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
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
	sf::Vector2f currentPosition = player.getPosition();
	currentPosition.x += velocity.x * (float)15 * TIMER_PER_FRAME.asSeconds();
	if (currentPosition.y < HEIGHT - FIXVALUE)
	{
		currentPosition.y += gravity.y * (float)15 * TIMER_PER_FRAME.asSeconds();
	}
	if (currentPosition.y < 0)
	{
		currentPosition.y = 0;
		velocity.x = 0;
	}
	if (currentPosition.y > HEIGHT - FIXVALUE)
	{
		currentPosition.y = HEIGHT - FIXVALUE;
		velocity.y = 0;
	}
	if (currentPosition.x < 0)
	{
		currentPosition.x = 0;
	}
	if (currentPosition.x > WIDTH - FIXVALUE)
	{
		currentPosition.x = WIDTH - FIXVALUE;
	}

	isMoving = velocity.x != 0;

	player.setPosition(currentPosition.x, currentPosition.y);
}

void playerAnimation()
{
	if (runningFrameCount > (int)(sizeof(runningRight)/sizeof(*runningRight)-2))
	{
		runningFrameCount = 0;
	}
	else
	{
		runningFrameCount += 1;
	}
	if (idleFrameCount > (int)(sizeof(idleRight)/sizeof(*idleRight)-2))
	{
		idleFrameCount = 0;
	}
	else
	{
		idleFrameCount += 1;
	}

	if (isMoving)
	{
		if (faceRight)
		{
			player.setTexture(runningRight[runningFrameCount]);
		}
		else
		{
			player.setTexture(runningLeft[runningFrameCount]);
		}
	}else{
		if (faceRight)
		{
			player.setTexture(idleRight[idleFrameCount]);
		}
		else
		{
			player.setTexture(idleLeft[idleFrameCount]);
		}
	}
}

void render()
{
	window.clear();
	window.draw(player);
	window.display();
}

int main()
{

	// moving animation
	for (int i = 0; i < 11; ++i)
	{
		std::string tmpName = "images/Run (" + std::to_string(i + 1) + ").png";
		sf::Image tmpImg;
		if (!tmpImg.loadFromFile(tmpName))
		{
			std::cout << "load from image failed " << std::endl;
			return EXIT_FAILURE;
		}

		if (!runningRight[i].loadFromImage(tmpImg, area))
		{
			std::cout << "load from image failed " << std::endl;
			return EXIT_FAILURE;
		}
		sf::Image flipImage = runningRight[i].copyToImage();
		flipImage.flipHorizontally();
		if (!runningLeft[i].loadFromImage(flipImage))
		{
			std::cout << "load from image failed " << std::endl;
			return EXIT_FAILURE;
		}
	}
	// idle animation
	for (int i = 0; i < 16; ++i)
	{
		std::string tmpName = "images/Idle (" + std::to_string(i + 1) + ").png";
		sf::Image tmpImg;
		if (!tmpImg.loadFromFile(tmpName))
		{
			std::cout << "load from image failed " << std::endl;
			return EXIT_FAILURE;
		}

		if (!idleRight[i].loadFromImage(tmpImg, area))
		{
			std::cout << "load from image failed " << std::endl;
			return EXIT_FAILURE;
		}
		sf::Image flipImage = idleRight[i].copyToImage();
		flipImage.flipHorizontally();
		if (!idleLeft[i].loadFromImage(flipImage))
		{
			std::cout << "load from image failed " << std::endl;
			return EXIT_FAILURE;
		}
	}

	player.setTexture(idleRight[0]);
	player.setScale(sf::Vector2f(0.3, 0.3));
	player.setPosition(sf::Vector2f(0, HEIGHT - FIXVALUE - 800));
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		duration += elapsedTime.asSeconds();
		if (duration > 0.1f)
		{
			duration = 0;
			//update player animation
			playerAnimation();
		}

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