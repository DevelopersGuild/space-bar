#include <SFML/Graphics.hpp>
#include "ResourcePath.h"
#include "Overlap.h"
#include "math.h"
#include <cstdlib>
#include <ctime>
#include "string.h"
#include <iomanip>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function resets the sprite to a new location 
void reset(sf::Sprite& anySprite)
{
	anySprite.setPosition(rand() % 750, (rand() % 480)+70);//+70 allows for a header space
}//reset

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function uses the Overlap header so when objects intersect, eaten (initiated in main) is incremented
void handleCollision(sf::Sprite& charizardSprite, sf::Sprite& cookieSprite, sf::Sprite& cookieSprite4,
                     sf::Sprite& cloudSprite, int& eaten, sf::Text& score)
{
	if (overlap(charizardSprite, cloudSprite))
        {
		eaten++;
        score.setString(std::to_string(eaten));//converting int eaten to string and display onto screen
        reset(cloudSprite);
            
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
void update(float& x, sf::Sprite& charizardSprite, sf::Sprite& cookieSprite, sf::Sprite& cookieSprite4, sf::Sprite& cloudSprite, int& eaten, sf::Text& score)
{
    //charizard motion angle
    x += 0.07;
    float angle = 12 * sin(x);
    
	//keyboard commands - key direction and speed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        charizardSprite.move(0, -5);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		charizardSprite.move(0, 5);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        charizardSprite.setRotation(angle);
		charizardSprite.move(-5, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        charizardSprite.setRotation(angle);
		charizardSprite.move(5, 0);
    }

	//charizard moving on and off screen and re-enters at the extact opposite end of the screen
	if (charizardSprite.getPosition().y < 70)
		charizardSprite.setPosition((charizardSprite.getPosition().x), 600);
	if (charizardSprite.getPosition().y > 600)
		charizardSprite.setPosition((charizardSprite.getPosition().x), 70);
	if (charizardSprite.getPosition().x < 0)
		charizardSprite.setPosition(800, (charizardSprite.getPosition().y)); 
	if (charizardSprite.getPosition().x > 800)
		charizardSprite.setPosition(0, (charizardSprite.getPosition().y));
	
	//flying obstacle - speed and direction
	cookieSprite.move(-5, 0);
	cookieSprite4.move(0, 5);
	if (cookieSprite.getPosition().x < 0)//cookie moving from right to left
		cookieSprite.setPosition(800, (rand() % 530)+70);//was charizardSprite.getPosition().y where cookie was re-entering screen at the last charizard Y axis position but for level 1 it's re-entering at a random point on the Y axis.
    
	if (cookieSprite4.getPosition().y > 600)//cookie moving top to bottom
		cookieSprite4.setPosition(rand() % 800, 70);//was charizardSprite.getPosition().x but now charizardSprite re-enters the screen at the opposite side of the Y axis

    handleCollision(charizardSprite, cookieSprite, cookieSprite4, cloudSprite, eaten, score);
}//update

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function where the screen is cleared and re-drawn - keep in mind that the order the actions are listed is like layers on the screen the top layer being the last on the list
void draw(sf::RenderWindow& window, sf::Sprite& charizardSprite, sf::Sprite& cookieSprite, sf::Sprite& heartSprite1, sf::Sprite& heartSprite2, sf::Sprite& cookieSprite4, sf::Sprite& cloudSprite, int& eaten, sf::Text& score, sf::Text text, sf::Text title, sf::Sprite background)
{ 
	window.clear();
    window.draw(background);
	window.draw(cookieSprite);
	window.draw(heartSprite1);
	window.draw(heartSprite2);
	window.draw(cookieSprite4);
	window.draw(cloudSprite);
	window.draw(charizardSprite);
    window.draw(score);
    window.draw(text);
    window.draw(title);
	window.display();
}//draw

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function main creates window, textures, sprites and calls functions while the window is open.
int main()
{
    //seeding the rand function used in reset and update functions
	srand(time(NULL));
    
    //window controller
    sf::RenderWindow window(sf::VideoMode(800, 600), "Spacebar Games");
    window.setVerticalSyncEnabled(true);
    
    sf::Texture windowBackground;
    windowBackground.loadFromFile(resourcePath() + "assets/background.png");
    sf::Sprite background(windowBackground);

    //hero character
	sf::Texture charizardTexture;
	charizardTexture.loadFromFile(resourcePath() + "assets/spaceship.png");
	sf::Sprite charizardSprite(charizardTexture);
    charizardSprite.setPosition(400,300);
    charizardSprite.setOrigin(32, 32);

    //two obstacles
	sf::Texture cookieTexture;
	cookieTexture.loadFromFile(resourcePath() + "assets/obstacle1.png");
	sf::Sprite cookieSprite(cookieTexture);//first flying cookie obstacle
	sf::Sprite cookieSprite4(cookieTexture);//second flying cookie obstacle
    cookieSprite.setOrigin(32, 32);
    cookieSprite4.setOrigin(32, 32);

    //target
	sf::Texture cloudTexture;
	cloudTexture.loadFromFile(resourcePath() + "assets/starTarget.png");
	sf::Sprite cloudSprite(cloudTexture);
	cloudSprite.setPosition(400, 500);
    cloudSprite.setOrigin(32, 32);

	int eaten = 0;
    
    //window header text
    sf::Font font;
    font.loadFromFile(resourcePath()+ "assets/Fonts/PTC75F.ttf");
    
    //showing the score text and starting position
    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(20);
    score.setColor(sf::Color::Red);
    score.setStyle(sf::Text::Bold);
    score.setPosition(425, 0);
    score.setString("0");
    
    //showing the word, Score
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setColor(sf::Color::Blue);
    text.setStyle(sf::Text::Bold);
    text.setPosition(350, 0);
    text.setString("Score: ");
    
    //showing the name of the game
    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(20);
    title.setColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(10, 0);
    title.setString("Name of Game");
    
	//life counter - locations
    sf::Texture heartTexture;
    heartTexture.loadFromFile(resourcePath() + "assets/heart.png");
	sf::Sprite heartSprite1(heartTexture);
	heartSprite1.setPosition(800 - 40, 50);
	heartSprite1.setOrigin(32, 32);

	sf::Sprite heartSprite2(heartTexture);
	heartSprite2.setPosition(800 - 70, 50);
	heartSprite2.setOrigin(32, 32);

	float x = 0;//declaring x for the update function

	//while the window is open the functions above are called
	while (window.isOpen())
	{
		handleEvent(window);
		update(x, charizardSprite, cookieSprite, cookieSprite4, cloudSprite, eaten, score);
		draw(window, charizardSprite, cookieSprite, heartSprite1, heartSprite2, cookieSprite4, cloudSprite, eaten, score, text, title, background);
	}

    return 0;
}//main