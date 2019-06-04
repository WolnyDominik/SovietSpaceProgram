#include "ScreenGame.h"
#include <iostream>


ScreenGame::ScreenGame(std::string filename, int x, int y)
{
	if (!map.loadFromFile(filename))
		std::cout << "ERROR:\tCan't load map from file\n";
	this->x = x;
	this->y = y;
}

void ScreenGame::update()
{
	if (game_objects.size() > 0)
	{
		for (auto i : game_objects)
			i->produce();
	}
}

void ScreenGame::draw()
{
	ctx::save();

	ctx::translate(x / 2, y / 2);
	ctx::scale(scale, scale);
	ctx::translate(mx, my);

	ctx::drawImage(
		map,
		0, 0, 2400, 1805,
		-((float)2400 / 2),
		-((float)1805 / 2),
		2400, 1805);

	for (auto i : game_objects)
		i->draw();

	ctx::restore();
}

void ScreenGame::onKeyPress()
{
	if (game::getKey(36))
	{
		manager->update(2);
		game_time::pause();
	}
	else if (game::getKey(1))
		building = true;
	else if (building && game::getKey(27))
		build_option = 0;
	else if (building && game::getKey(28))
		build_option = 1;
	else if (building && game::getKey(29))
		build_option = 2;
	else if (game::getKey(72))
		mx -= 50;
	else if (game::getKey(71))
		mx += 50;
	else if (game::getKey(73))
		my += 50;
	else if (game::getKey(74))
		my -= 50;
	else if (game::getKey(15))
		scale += 0.1f;
	else if (game::getKey(11))
		scale -= 0.1f;
	else if (game::getKey(17))
	{
		scale = 0.9f;
		mx = 0;
		my = 0;
	}
	else if (game::getKey(14))
	{
		if (paused)
			game_time::resume();
		else
			game_time::pause();
	}
		
	
}

void ScreenGame::onKeyRelease()
{

}

void ScreenGame::onMousePress()
{
	if (game::isClicked() && game::getMouseKey() == 0 && building && build_option != -1)
		addBuilding(build_option, (game::getX() - (x * 0.5)) / scale - mx, (game::getY() - (y * 0.5)) / scale - my);

	build_option = -1;
}

void ScreenGame::onMouseDrag()
{

}

void ScreenGame::setManager(ScreenManager* manager)
{
	this->manager = manager;
}

void ScreenGame::changeScreen(int choice)
{
	manager->update(choice);
	game::pauseGame();
}

void ScreenGame::addBuilding(int choice, int x, int y)
{
	if (choice == 0)
	{
		Factory* tmp = new Factory(x, y, "");
		game_objects.push_back((Building*)tmp);
	}
	else if (choice == 1)
	{
		CoalPowerPlant* tmp = new CoalPowerPlant(x, y);
		game_objects.push_back((Building*)tmp);
	}
	else if (choice == 2)
	{
		NuclearPowerPlant* tmp = new NuclearPowerPlant(x, y);
		game_objects.push_back((Building*)tmp);
	}
}

void ScreenGame::clearBuildings()
{
	game_objects.clear();
}

