#pragma once

unsigned long million = 1000000;
unsigned long billion = million * million;

class Building
{
public:
	std::string name;
	unsigned long long amount;
	unsigned long long cost;
	long double cookiesPerSecond;
	//constructor OwO:
	Building(std::string nam, unsigned long long amnt, unsigned long long cst, long double cps)
	{
		name = nam;
		amount = amnt;
		cost = cst;
		cookiesPerSecond = cps;
	}
	void setName(std::string nameToSet)
	{
		name = nameToSet;
	}
	void setAmount(unsigned long long amountToSet)
	{
		amount = amountToSet;
	}
	void addOne()
	{
		amount += 1;
	}
	void setCost(unsigned long long costToSet)
	{
		cost = costToSet;
	}
	void setCPS(long double cpsToSet)
	{
		cookiesPerSecond = cpsToSet;
	}
};

namespace buildings
{
	Building cursor("Cursor", 0, 15, 0.1);
	Building grandma("Grandma", 0, 100, 1);
	Building farm("Farm", 0, 1100, 8);
	Building mine("Mine", 0, 12000, 47);
	Building factory("Factory", 0, 130000, 260);
	Building bank("Bank", 0, million * 1.4, 1400);
	Building temple("Temple", 0, million * 20, 7800);
	Building wizard("Wizard Tower", 0, million * 330, 44000);
	Building shipment("Shipment", 0, billion * 5.1, 260000);
	Building arr[] = {
		buildings::cursor, buildings::grandma, buildings::farm,
		buildings::mine, buildings::factory, buildings::bank,
		buildings::temple, buildings::wizard, buildings::shipment
	};
}