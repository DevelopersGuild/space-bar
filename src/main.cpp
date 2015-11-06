#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "Overlap.h"
#include <cstdlib>
#include <ctime>

using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function resets the sprite to a new location 
void reset(sf::Sprite& resettingAnyVariable)
{
	resettingAnyVariable.setPosition(10, rand() % 550);//resets to a static X axis location 10 and a random Y axis location 

}//reset


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function uses the Overlap header so when objects intersect, eaten (initiated in main) is incremented
void handleCollision(sf::Sprite& charizardSprite, sf::Sprite& cookieSprite, sf::Sprite& cookieSprite4, int& eaten)
{
	if (overlap(charizardSprite, cookieSprite))
	{
		eaten++;
		reset(charizardSprite);
	}
}//handleCollision


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function allows user to close the window
void handleEvent(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}//handleEvent


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function where Sprites' actions are taking place
void update(float& x, sf::Sprite& charizardSprite, sf::Sprite& cookieSprite, sf::Sprite& cookieSprite2, sf::Sprite& cookieSprite3, sf::Sprite& cookieSprite4, int& eaten)
{
	//life counter - motion
	x += 0.07;
	float angle = 15 * sin(x);
	cookieSprite2.setRotation(angle);
	cookieSprite3.setRotation(angle);

	//keyboard commands
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		charizardSprite.move(0, -5);//speed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		charizardSprite.move(0, 5);//speed
	if (charizardSprite.getPosition().y < 0)
		charizardSprite.setPosition(0, 550);
	if (charizardSprite.getPosition().y > 600)
		charizardSprite.setPosition(0, 0);
	
	//flying obstacle
	cookieSprite.move(-5, 0);//speed and direction
	cookieSprite4.move(0, 5);
	if (cookieSprite.getPosition().x < 0)
		cookieSprite.setPosition(800, rand() % 550);
	if (cookieSprite4.getPosition().y > 600)
		cookieSprite4.setPosition(0, rand() % 550);

	handleCollision(charizardSprite, cookieSprite, cookieSprite4, eaten);

}//update


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function where the screen is cleared and re-drawn - keep in mind that the order the actions are listed is like layers on the screen the top layer being the last on the list
void draw(sf::RenderWindow& window, sf::Sprite& charizardSprite, sf::Sprite& cookieSprite, sf::Sprite& cookieSprite2, sf::Sprite& cookieSprite3, sf::Sprite& cookieSprite4, int& eaten)
{
	window.clear();
	window.draw(cookieSprite);
	window.draw(cookieSprite2);
	window.draw(cookieSprite3);
	window.draw(cookieSprite4);
	window.draw(charizardSprite);
	window.display();
}//draw


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function main creates window, textures, sprites and calls functions while the window is open.
int main()
{
	
	srand(time(NULL));//seeding the rand function used in reset and update functions
	sf::RenderWindow window(sf::VideoMode(800, 600), "Spacebar Games");
	window.setVerticalSyncEnabled(true);

	sf::Texture charizardTexture;
	charizardTexture.loadFromFile(resourcePath() + "assets/charizard.png");
	sf::Sprite charizardSprite(charizardTexture);

	sf::Texture cookieTexture;
	cookieTexture.loadFromFile(resourcePath() + "assets/cookie.png");
	sf::Sprite cookieSprite(cookieTexture);
	//cookieSprite.setPosition(400, 300);
	sf::Sprite cookieSprite4(cookieTexture);

	int eaten = 0;

	//life counter - locations
	sf::Sprite cookieSprite2(cookieTexture);
	cookieSprite2.setPosition(800 - 50, 25);
	cookieSprite2.setOrigin(32, 32);

	sf::Sprite cookieSprite3(cookieTexture);
	cookieSprite3.setPosition(800 - 125, 25);
	cookieSprite3.setOrigin(32, 32);


	float x = 0;//declaring x for the update function

	//while the window is open the functions above are called
	while (window.isOpen())
	{
		handleEvent(window);
		update(x, charizardSprite, cookieSprite, cookieSprite2, cookieSprite3, cookieSprite4, eaten);
		draw(window, charizardSprite, cookieSprite, cookieSprite2, cookieSprite3, cookieSprite4, eaten);
	}

	return 0;
}