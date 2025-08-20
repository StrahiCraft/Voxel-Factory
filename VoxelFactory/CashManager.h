#pragma once
#include "TextRenderer.h"
#include <string>

static class CashManager
{
private:
	static int _cash;
	static TextRenderer* _moneyCounter;
public:
	static void setupMoneyCounter(TextRenderer* moneyCounter);
	static void updateMoney(int amount);
	static int getCurrentCash();
};

