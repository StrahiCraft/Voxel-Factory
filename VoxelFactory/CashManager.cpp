#include "CashManager.h"

int CashManager::_cash = 100;
TextRenderer* CashManager::_moneyCounter;

void CashManager::setupMoneyCounter(TextRenderer* moneyCounter) {
	_moneyCounter = moneyCounter;
	_moneyCounter->setTextColor(glm::vec3(0, 1, 0));
}

void CashManager::updateMoney(int amount) {
	_cash += amount;
	_moneyCounter->setText(std::to_string(_cash) + "$");
}

int CashManager::getCurrentCash() {
	return _cash;
}

