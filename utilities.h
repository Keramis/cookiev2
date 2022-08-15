#pragma once

void waitForEscButton();

void setConsoleNonResizable();

bool wasKeyJustPressed(int key);

void printAtCoords(std::string text, SHORT x, SHORT y, bool clearLine);

void clearConsole();

void setConsoleTitleString(std::string input);