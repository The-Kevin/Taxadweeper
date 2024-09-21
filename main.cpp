#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main(int argc, char* argv[]){
	
	sf::RenderWindow window(sf::VideoMode(640, 480), "Mine sweeper - @The-Kevin");

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
	return 0;
}
