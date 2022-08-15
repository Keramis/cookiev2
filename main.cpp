#include "includes.h"
#include "utilities.h"
#include "buildingsClass.h"

long float GlobalCookies = 0;

//todo:
/// add clicker thread, detects if space is pressed and adds cookies
/// add buying buildings a thing with _getch();
/// add a GUI that updates every time a building has been bought, and updates fast for cookies produced.

void printCookies()
{
	while (1)
	{
		long float CPS{};
		for (int i = 0; i < 9; i++)
		{
			if (buildings::arr[i].amount > 0)
			{
				GlobalCookies += buildings::arr[i].cookiesPerSecond/20*buildings::arr[i].amount;
				CPS += buildings::arr[i].cookiesPerSecond * buildings::arr[i].amount;
				//divide by 20 to account for updating every ~50ms
				//might be a bit slower due to printing...
			}
		}
		printAtCoords("Cookies: " + std::to_string(GlobalCookies) + " || CPS: " + std::to_string(CPS), 0, 0, true);
		Sleep(50);

	}
}

void clickDetection()
{
	while (1)
	{

		if (wasKeyJustPressed(VK_SPACE))
		{
			GlobalCookies += 1;
		}
		Sleep(50);

	}
}

bool saveGame()
{
	std::ofstream file("cookie_save.txt");
	if (file.is_open())
	{
		file << std::to_string(GlobalCookies) << '\n';

		for (int i = 0; i < 9; ++i)
		{
			file << std::to_string(buildings::arr[i].amount) << '\n';
		}

		return true;
	}

	else
	{
		return false;
	}
}
void saveGameLoop()
{

	while (1)
	{
		bool hasNoFatalErrorOccured = saveGame();

		if (!hasNoFatalErrorOccured)
		{
			setConsoleTitleString("Fatal error occured while trying to save...");
		}

		Sleep(3000);
	}

}

bool loadGame()
{
	std::ifstream file("cookie_save.txt");
	if (file.is_open())
	{
		std::string line{};
		std::getline(file, line);
		GlobalCookies = std::stof(line);
		int count = 0;
		for (int count = 0; count < 9; ++count)
		{
			std::getline(file, line);
			buildings::arr[count].amount = std::stoll(line);
			std::cout << "Building " << buildings::arr[count].name << " loaded || " << buildings::arr[count].amount << " || " << &buildings::arr[count].amount << '\n';
			if (buildings::arr[count].amount > 0)
			{
				//get original price
				auto orgprice = buildings::arr[count].cost;
				//do calculation
				for (int i = buildings::arr[count].amount; i > 0; --i)
				{
					buildings::arr[count].cost += (1.05 * i);
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
void askToLoadGame()
{
	std::cout << "Do you want to load your last saved game? [y/n]: ";
	char a;
	std::cin >> a;
	if (a == 'y')
	{
		std::cout << "\nLoading game.... \n";
		Sleep(500);
		bool hasLoadSucceeded = loadGame();
		if (hasLoadSucceeded)
		{
			std::cout << "Successfully loaded. \n";
			Sleep(2000);
			clearConsole();

		}
		else
		{
			std::cout << "Fatal error occured while reading from save file.\n";
			std::cout << "Do you want to start a new game? [y/n]: ";
			char ans{};
			std::cin >> ans;
			if (!ans == 'y')
			{
				std::cout << "\nQuitting....";
				Sleep(500);
				exit(-100);
			}
			else
			{
				std::cout << "\nStarting a new game...\n";
				Sleep(500);
				clearConsole();
			}
		}
	}
	else
	{
		std::cout << "\nStarting a new game... \n";
		Sleep(100);
		clearConsole();
	}
}

void printBuildings()
{
	for (int i = 0; i < 9; i++)
	{
		Building* ptr = &buildings::arr[i];
		printAtCoords("Buy with [" + std::to_string(i+1) + "] | " + (*ptr).name + "s: " + std::to_string((*ptr).amount) + "  || Cost: " + std::to_string((*ptr).cost)
			, 0, 2 + i, true);
	}
}

void buyBuilding(Building* buildingPtr)
{
	//check if we have enough cookies
	printBuildings();
	if (GlobalCookies - buildingPtr->cost > 0)
	{
		//buy it
		buildingPtr->amount += 1;
		GlobalCookies -= buildingPtr->cost;
		buildingPtr->cost += (1.05*buildingPtr->amount);
		printBuildings();
	}
}
void checkBuyBuilding()
{
	while (1)
	{
		char bb = _getch(); //gets key pressed
		switch (bb)
		{
		case '1':
			buyBuilding(&buildings::arr[0]);
			break;


		case '2':
			buyBuilding(&buildings::arr[1]);
			break;


		case '3':
			buyBuilding(&buildings::arr[2]);
			break;


		case '4':
			buyBuilding(&buildings::arr[3]);
			break;


		case '5':
			buyBuilding(&buildings::arr[4]);
			break;


		case '6':
			buyBuilding(&buildings::arr[5]);
			break;
			

		case '7':
			buyBuilding(&buildings::arr[6]);
			break;


		case '8':
			buyBuilding(&buildings::arr[7]);
			break;


		case '9':
			buyBuilding(&buildings::arr[8]);
			break;


		case '0':
			buyBuilding(&buildings::arr[9]);
			break;


		default:
			break;
		}
	}
}

void startGamePrompt()
{
	std::cout << "Would you like a tutorial? [y/n]: ";
	char a;
	std::cin >> a;
	if (a == 'y')
	{
		std::cout << '\n';
		std::cout << "This is my interpretation of cookie clicker.\nAs you can see, it's not very finished....."
			<< "\nBut I do plan on making continuous updates."
			<< "\nAnyways, use SPACE to 'click' the cookie. You will generate one cookie per space press."
			<< "\nUse the number keys [0-9] to buy buildings. 1 is cursor, 2 is grandma, and so on.\n0 is the highest one, which hasn't been included yet."
			<< "\nI hope you have a fun time playing!"
			<< "\nMade with love from Keramis <3 \n\n\n";
	}
}

void consoleNameUpdater()
{
	while (1)
	{
		setConsoleTitleString("ConsoleCookie Clicker!");
		Sleep(3000);
		setConsoleTitleString("Made with <3 by Keramis!");
		Sleep(3000);
		setConsoleTitleString("Powerups soon!");
		Sleep(3000);
	}
}

int main()
{
	std::thread nameUpdaterThread(consoleNameUpdater);
	nameUpdaterThread.detach();

	startGamePrompt();
	askToLoadGame();

	std::thread cookieUpdaterThread(printCookies);
	cookieUpdaterThread.detach();
	std::thread clickDetectionThread(clickDetection);
	clickDetectionThread.detach();
	std::thread autoSaveThread(saveGameLoop);
	autoSaveThread.detach();
	std::thread buyBuildingThread(checkBuyBuilding);
	buyBuildingThread.detach();
	printBuildings();

	//waitForEscButton();
	saveGame();
	return 0;
}