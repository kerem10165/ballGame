#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

//mermminin hýzýný ve kendisini tutar
class MermiSinifi
{
public:
	
	MermiSinifi()
	{
		mermi.setPointCount(36);
		mermi.setRadius(5.0f);
		mermi.setFillColor(sf::Color::Red);
		mermi.setOrigin(5, 5);
		speed.x = 0;
		speed.y = 0;
	}

	~MermiSinifi(){}
	
	void setMermi(sf::Vector2f& hiz)
	{
		speed = hiz;
		speed.x *= 10;
		speed.y *= 10;
	}


	sf::CircleShape mermi;
	sf::Vector2f speed;
	
};


int main()
{

	//sfml pencere ve ayarlar
	sf::ContextSettings ayar;
	ayar.antialiasingLevel = 4;
	sf::RenderWindow pencere(sf::VideoMode(800, 600), "Pencere",sf::Style::Default,ayar);
	pencere.setFramerateLimit(60);

	//oyuncu tanýmlandý
	sf::CircleShape oyuncu(30.0f, 36);
	oyuncu.setFillColor(sf::Color::White);
	oyuncu.setOrigin(30, 30);
	oyuncu.setPosition(500, 500);
	
	//dusman tanýmlandý
	sf::RectangleShape dusman;
	dusman.setSize(sf::Vector2f(40.0f, 40.0f));
	dusman.setFillColor(sf::Color::Blue);
	vector <sf::RectangleShape> dusmanlar;


	//mermi tanýmlandý
	MermiSinifi mermi;
	vector <MermiSinifi> mermiler;
	
	
	
	//gerekli deðiþkenler
	sf::Vector2f oyuncu_merkez;
	sf::Vector2f birim_vektor;
	sf::Vector2i mouse;
	float uzaklik;

	//dusman icin rastgele konum ve saat
	random_device rd;
	uniform_real_distribution <float> dagilim_x(0, 760);
	uniform_real_distribution <float> dagilim_y(0, 475);
	mt19937 motor(rd());
	
	sf::Clock saat;
	saat.restart();

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
		
		//update

		//oyuncu kontrolleri
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			oyuncu.move(-5.0, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			oyuncu.move(5.0, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			oyuncu.move(0, -5.0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			oyuncu.move(0, 5.0);
		}

		//oyuncu merkezi ve mermi yönü hesaplama
		oyuncu_merkez = oyuncu.getPosition();
		mouse = sf::Mouse::getPosition(pencere);
		uzaklik = sqrt(pow((oyuncu_merkez.x - mouse.x), 2) + pow((oyuncu_merkez.y - mouse.y), 2));
		birim_vektor.x = mouse.x - oyuncu_merkez.x;
		birim_vektor.y = mouse.y - oyuncu_merkez.y;
		birim_vektor /= uzaklik;
		
		//mermiler oluþturuldu ve gerekli deðerlerle set edildi

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mermi.setMermi(birim_vektor);
			mermi.mermi.setPosition(oyuncu_merkez);
			mermiler.push_back(mermi);
		}

		//mermi hareket
		for (int i = 0; i < mermiler.size(); i++)
		{
			mermiler.at(i).mermi.move(mermiler.at(i).speed);
		}

		//düþman oluþturma
		if (saat.getElapsedTime().asMilliseconds() > 500)
		{
			dusman.setPosition(dagilim_x(motor), dagilim_y(motor));
			dusmanlar.push_back(dusman);
			saat.restart();
		}

		for (int i = 0; i < dusmanlar.size(); i++)
		{
			dusmanlar.at(i).move(0, 6.5);
		}

		//mermi silme
		for (int i = 0; i < mermiler.size(); i++)
		{
			if (mermiler.at(i).mermi.getPosition().x > 805 || mermiler.at(i).mermi.getPosition().x < -5)
			{
				mermiler.erase(mermiler.begin() + i);
			}
			else if (mermiler.at(i).mermi.getPosition().y > 605 || mermiler.at(i).mermi.getPosition().x < -5)
			{
				mermiler.erase(mermiler.begin() + i);
			}
			else
			{

			}
		}

		//mermi ve dusman silme
		for (int i = 0; i < mermiler.size(); i++)
		{
			for (int j = 0; j < dusmanlar.size(); j++)
			{
				if (mermiler[i].mermi.getGlobalBounds().intersects(dusmanlar[j].getGlobalBounds()))
				{
					dusmanlar.erase(dusmanlar.begin() + j);
					mermiler.erase(mermiler.begin() + i);
					break;
				}
			}
		}


		pencere.clear(sf::Color::Black);
		
		//oyuncu çizildi
		pencere.draw(oyuncu);

		//düþmanlar çizildi
		for (int i = 0; i < dusmanlar.size(); i++)
		{
			pencere.draw(dusmanlar.at(i));
		}

		//mermiler çizildi
		for (size_t i = 0; i < mermiler.size(); i++)
		{
			pencere.draw(mermiler.at(i).mermi);
		}

		
		

		

		pencere.display();


	}

	

}


