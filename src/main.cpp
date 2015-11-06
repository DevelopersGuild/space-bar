#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "Overlap.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void reset(sf::Sprite& resettingAnyVariable)//not specific, it can apply to any variable named in reset function
{
	resettingAnyVariable.setPosition(10, 400);//rand() % 550

}

void handleCollision(sf::Sprite& charizardSprite, sf::Sprite& cookieSprite, int& eaten)
{
	if (overlap(charizardSprite, cookieSprite))
	{
		eaten++;
		reset(charizardSprite);
	}
}
void handleEvent(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void update(float& x, sf::Sprite& charizardSprite, sf::Sprite& cookieSprite, sf::Sprite& cookieSprite2, sf::Sprite& cookieSprite3, int& eaten)
{
	//life cookies
	x += 0.07;
	float angle = 15 * sin(x);
	cookieSprite2.setRotation(angle);
	cookieSprite3.setRotation(angle);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		charizardSprite.move(0, -5);//speed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		charizardSprite.move(0, 5);//speed
	
	//flying obstacle
	cookieSprite.move(-5, 0);//speed
	if (cookieSprite.getPosition().x < 0)
		cookieSprite.setPosition(800, rand() % 550);//rand() % 550

	handleCollision(charizardSprite, cookieSprite, eaten);

}

void draw(sf::RenderWindow& window, sf::Sprite& charizardSprite, sf::Sprite& cookieSprite, sf::Sprite& cookieSprite2, sf::Sprite& cookieSprite3, int& eaten)
{
	window.clear();
	window.draw(cookieSprite);
	window.draw(cookieSprite2);
	window.draw(cookieSprite3);
	window.draw(charizardSprite);
	window.display();
}

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Works!");
	window.setVerticalSyncEnabled(true);

	sf::Texture charizardTexture;
	charizardTexture.loadFromFile(resourcePath() + "assets/charizard.png");
	sf::Sprite charizardSprite(charizardTexture);

	sf::Texture cookieTexture;
	cookieTexture.loadFromFile(resourcePath() + "assets/cookie.png");

	sf::Sprite cookieSprite(cookieTexture);
	cookieSprite.setPosition(400, 300);

	int eaten = 0;

	sf::Sprite cookieSprite2(cookieTexture);
	cookieSprite2.setPosition(800 - 50, 25);
	cookieSprite2.setOrigin(32, 32);

	sf::Sprite cookieSprite3(cookieTexture);
	cookieSprite3.setPosition(800 - 125, 25);
	cookieSprite3.setOrigin(32, 32);

	float x = 0;

	while (window.isOpen())
	{
		handleEvent(window);
		update(x, charizardSprite, cookieSprite, cookieSprite2, cookieSprite3, eaten);
		draw(window, charizardSprite, cookieSprite, cookieSprite2, cookieSprite3, eaten);
	}

	return 0;
}