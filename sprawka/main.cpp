/*------------------------------------------------------------

Tytul gry: Rozbrykane Asteroidy

Co zrealizowalem w biezacym tygodniu?
-stworzenie klasy gracza
-poprawienie obrotow statku (z uzyciem flagi)
-poruszanie statkiem
-stworzenie klasy asteroidy

Czas pracy w biezacym tygodniu: 3h

Co planuje na kolejny tydzien?
-dodanie funkcji losuj(min,max) zwracajaca losowa liczbe z przedzialu <min,max>
-stworzenie menu
-poprawienie reagowania statku na przemieszczanie im (dodanie bezwladnosci)
-poprawienie trajektorii ruchu asteroidy
-...

------------------------------------------------------------*/





/*------------------------------------------------------------

Program glowny

------------------------------------------------------------*/
#include <SFML/Graphics.hpp>
#include <iostream>
#define M_PI 3.14159265358979323846

class asteroida {
private:
	float deltaAlfa = 1;
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::CircleShape asteroidaKsztalt;

public:
	asteroida(float xIn, float yIn);
	sf::CircleShape getAsteroida() { return asteroidaKsztalt; };
	void move();
};
asteroida::asteroida(float xIn, float yIn) {
	pos.x = xIn;
	pos.y = yIn;
	vel.x = 1;
	vel.y = 1;
	asteroidaKsztalt.setRadius(50);
	asteroidaKsztalt.setPointCount(5);
	asteroidaKsztalt.setPosition(pos.x, pos.y);
	asteroidaKsztalt.setOutlineThickness(3.f);
	asteroidaKsztalt.setOutlineColor(sf::Color::White);
	asteroidaKsztalt.setFillColor(sf::Color::Transparent);
}
void asteroida::move() {
	asteroidaKsztalt.setPosition(asteroidaKsztalt.getPosition() + vel);
	asteroidaKsztalt.rotate(deltaAlfa);

}
class gracz {
private:
	float deltaAlfa = 0;
	float v = 0;
	float deltaV = 0;
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::ConvexShape graczKsztalt;
	bool up;
	bool left;
	bool right;
	
public:
	gracz(float xIn, float yIn);
	sf::ConvexShape getGracz() { return graczKsztalt; };
	void setKey(int key, bool val);
	void move();
	void calculateVal();
};

gracz::gracz(float xIn, float yIn) {
	pos.x = xIn;
	pos.y = yIn;
	graczKsztalt.setPointCount(3);
	graczKsztalt.setPoint(0, sf::Vector2f(0.f, -30.f));
	graczKsztalt.setPoint(1, sf::Vector2f(15.f, 15.f));
	graczKsztalt.setPoint(2, sf::Vector2f(-15.f, 15.f));
	graczKsztalt.setPosition(pos.x,pos.y);
	graczKsztalt.setOutlineThickness(3.f);
	graczKsztalt.setOutlineColor(sf::Color::White);
	graczKsztalt.setFillColor(sf::Color::Transparent);
}

void gracz::setKey(int key, bool val) {
	switch (key)
	{
	case 0: // kliknieto W
		if (val) {
			deltaV = 0.16f;
		}
		else {
			deltaV = -0.16f;
		}
		break;

	case 1: // kliknieto A
		left = val;
		break;
	case 2: // kliknieto D
		right = val;
		break;
	default:
		break;
	}
}
void gracz::move() {
	if(left&&right) {
		deltaAlfa = 0;
	}  else if (left) {
		deltaAlfa = -2.5;
	} else if (right) {
		deltaAlfa = 2.5;
	} else {
		deltaAlfa = 0;
	}

	graczKsztalt.rotate(deltaAlfa);
	
	calculateVal();
	graczKsztalt.setPosition(graczKsztalt.getPosition() + vel);
}
void gracz::calculateVal() {
	int lastRotation = graczKsztalt.getRotation();
	v += deltaV;
	if (v <= 0) {
		v = 0;
		deltaV = 0;
	}
	vel.x = sinf(graczKsztalt.getRotation()* (float)M_PI / 180)*v;
	vel.y = -cosf(graczKsztalt.getRotation()*(float)M_PI / 180)*v;
}
int main()
{
	std::cout << "Rozbrykane Asteroidy, autor: Karol Konopka\n";

	sf::Clock zegar;
	sf::Time czas;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Rozbrykane Asteroidy");
	asteroida a1(100, 100);
	gracz g1((float)window.getSize().x/2,(float)window.getSize().y / 2);

	while (window.isOpen()) { 
		sf::Event event;  
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::F1) {
					std::cout << "kliknieto f1" << std::endl;
				}
				else if (event.key.code == sf::Keyboard::Escape) {
					std::cout << "kliknieto esc" << std::endl;
				}
				else if (event.key.code == sf::Keyboard::W) {
					g1.setKey(0, true);
					std::cout << "kliknieto W" << std::endl;
				}
				else if (event.key.code == sf::Keyboard::A) {
					g1.setKey(1, true);
					std::cout << "kliknieto A" << std::endl;
				}
				else if (event.key.code == sf::Keyboard::D) {
					g1.setKey(2, true);
					std::cout << "kliknieto D" << std::endl;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::F1) {
					std::cout << "puszczono f1" << std::endl;
				}
				else if (event.key.code == sf::Keyboard::Escape) {
					std::cout << "puszczono esc" << std::endl;
				}
				else if (event.key.code == sf::Keyboard::W) {
					g1.setKey(0, false);
					std::cout << "puszczono W" << std::endl;
				}
				else if (event.key.code == sf::Keyboard::A) {
					g1.setKey(1, false);
					std::cout << "puszczono A" << std::endl;
				}
				else if (event.key.code == sf::Keyboard::D) {
					g1.setKey(2, false);
					std::cout << "puszczono D" << std::endl;
				}
			}
			if (event.type == sf::Event::Resized) { 
				std::cout << "nowa szerokosc: " << event.size.width << std::endl;  
				std::cout << "nowa wysokosc: " << event.size.height << std::endl;
			}
		}
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > 16) {
			g1.move();
			a1.move();
			zegar.restart();
		}
		window.clear(); 
		window.draw(g1.getGracz());
		window.draw(a1.getAsteroida());
		window.display(); 
	}
	getchar();
	return 0;
}