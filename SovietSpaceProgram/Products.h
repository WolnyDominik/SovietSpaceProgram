#pragma once

#include <string>
#include <vector>



struct resource
{
	std::string name;
	int amount;
};

struct product
{
	std::string name;
	int produced_count;
	std::vector<resource> craft_recipe;
};

