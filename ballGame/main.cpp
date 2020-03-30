#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;


int main()
{

	sf::RenderWindow pencere(sf::VideoMode(800, 600), "Pencere");


	while (pencere.isOpen())
	{
		sf::Event olay;

		while (pencere.pollEvent(olay))
		{
			if (olay.type == sf::Event::Closed)
			{
				pencere.close();
			}
		}

	}


	pencere.clear(sf::Color::White);



	pencere.display();

}


