#include<SFML/Graphics.hpp>
#include<stack>
#include<random>
#include<string>
#include"Maze.h"
#include"Player.h"

using namespace std;
using namespace sf;


bool vWall[MSIZE + 1][MSIZE + 1];
bool hWall[MSIZE + 1][MSIZE + 1];


int main() {
	RenderWindow window(VideoMode(1920, 1800), "maze",Style::Fullscreen);
	Maze maze;
	srand(time(NULL));


	maze.prep();
	maze.logic();
	player player;
	player.prep();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		player.collision();
		player.handleMove(&window);
		player.towall();
		if (player.x == (MSIZE - 1) * area + MSIZE * thickness && player.y == (MSIZE - 1) * area + MSIZE * thickness)
		{
			player.prep();
			maze.prep();
			maze.logic();
		}

		window.clear();

		maze.draw(window);
		player.draw(&window);

		window.display();

	}
	return 0;

}