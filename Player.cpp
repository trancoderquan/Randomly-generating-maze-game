#pragma once
#include <chrono>
#include <thread>
#include <iostream>
#include "Player.h"
#include "Constants.h"


using namespace sf;
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

player::player()
{

}
void player::towall()
{

	for (int i = 0; i <= offsety; i++)
		if (hWall[offsetx][offsety - i])
		{
			UDtowall = (i) * (area + thickness);
			break;
		}
	for (int i = 0; i <= MSIZE; i++)
		if (vWall[offsetx + i][offsety])
		{
			RDtowall = (i) * (area + thickness);
			break;
		}
	for (int i = 0; i <= MSIZE; i++)
		if (hWall[offsetx][offsety + i])
		{
			DDtowall = (i) * (area + thickness);
			break;
		}
	for (int i = 0; i <= offsetx; i++)
		if (vWall[offsetx - i][offsety])
		{
			LDtowall = (i) * (area + thickness);
			break;
		}


}

void player::prep()
{
	x = thickness; y = thickness;
	offsetx = 0; offsety = 0;
}

void player::draw(RenderWindow* window)
{

	pl1.setFillColor(sf::Color::Magenta);
	pl1.setSize(sf::Vector2f(size, size));
	pl1.setPosition(x, y);
	window->draw(pl1);
	bullet.setFillColor(sf::Color::White);

	while (shooting && side[0])
	{
		bullet.setSize(sf::Vector2f(area / 5, UDtowall));
		bullet.setPosition(x + area / 4, y - UDtowall);
		window->draw(bullet);
		shooting = false;

		//powerup
		if (!powerup)
		{
			int yposition = offsety - UDtowall / (area + thickness);
			hWall[offsetx][yposition] = false;
		}

		sleep_for(nanoseconds(DELAY * 2));
	}
	while (shooting && side[1])
	{
		bullet.setSize(sf::Vector2f(RDtowall - area, area / 5));
		bullet.setPosition(x + area, y + area / 4);
		window->draw(bullet);
		shooting = false;

		//powerup
		if (!powerup)
		{
			int xposition = offsetx + RDtowall / (area + thickness);
			vWall[xposition][offsety] = false;
		}
		sleep_for(nanoseconds(DELAY));
	}
	while (shooting && side[2])
	{
		bullet.setSize(sf::Vector2f(area / 5, DDtowall - area));
		bullet.setPosition(x + area / 4, y + area);
		window->draw(bullet);
		shooting = false;

		//powerup
		if (!powerup)
		{
			int yposition = offsety + DDtowall / (area + thickness);
			hWall[offsetx][yposition] = false;
		}

		sleep_for(nanoseconds(DELAY));
	}
	while (shooting && side[3])
	{
		bullet.setSize(sf::Vector2f(LDtowall, area / 5));
		bullet.setPosition(x - LDtowall, y + area / 4);
		window->draw(bullet);
		shooting = false;

		//powerup
		if (!powerup)
		{
			int xposition = offsetx - LDtowall / (area + thickness);
			vWall[xposition][offsety] = false;
		}
		sleep_for(nanoseconds(DELAY));
	}
}
void player::collision()
{
	if (!hWall[offsetx][offsety])
		movable[0] = true;
	if (!vWall[offsetx + 1][offsety])
		movable[1] = true;
	if (!hWall[offsetx][offsety + 1])
		movable[2] = true;
	if (!vWall[offsetx][offsety])
		movable[3] = true;
}
void player::handleMove(RenderWindow* window)
{
	pl1.setPosition(x, y);
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window->close();

	}
	if (Keyboard::isKeyPressed(Keyboard::W) && movable[0])
	{
		goingup = true;
		for (int i = 0; i < 4; i++)
		{
			side[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			movable[i] = false;
		}
		side[0] = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && movable[2])
	{
		goingdown = true;
		for (int i = 0; i < 4; i++)
		{
			side[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			movable[i] = false;
		}
		side[2] = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && movable[1])
	{
		goingR = true;
		for (int i = 0; i < 4; i++)
		{
			side[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			movable[i] = false;
		}
		side[1] = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) && movable[3])
	{
		goingL = true;
		for (int i = 0; i < 4; i++)
		{
			side[i] = false;
		}
		for (int i = 0; i < 4; i++)
		{
			movable[i] = false;
		}
		side[3] = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::E) && x > 0)
	{
		shooting = true;
	}

	while (goingdown)
	{
		x = pl1.getPosition().x; y = pl1.getPosition().y + OFFSET;
		offsety++;
		goingdown = false;
		sleep_for(nanoseconds(DELAY));

	}
	while (goingup)
	{
		x = pl1.getPosition().x; y = pl1.getPosition().y - OFFSET;
		offsety--;
		goingup = false;
		sleep_for(nanoseconds(DELAY));

	}
	while (goingR)
	{
		x = pl1.getPosition().x + OFFSET; y = pl1.getPosition().y;
		offsetx++;
		goingR = false;
		sleep_for(nanoseconds(DELAY));


	}
	while (goingL)
	{
		x = pl1.getPosition().x - OFFSET; y = pl1.getPosition().y;
		offsetx--;
		goingL = false;
		sleep_for(nanoseconds(DELAY));


	}

}