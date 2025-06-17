#include "KeyboardConfig.h"
#include <locale>
#include <string>

std::string getKeyboardLayout() {
	setlocale(LC_ALL, "");		// Systeme local
	std::string name = setlocale(LC_ALL, NULL);

	if (name.find("Fr") != std::string::npos) {
		return "AZERTY";
	}
	else {
		return "QWERTY";
	}
}