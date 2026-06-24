#include "clsBankClient.h"
#include <iostream>
#include "clsLoginScreen.h"
#include "clsPerson.h"
#include "clsClientListScreen.h"

using namespace std;

int main()
{
	while (true) {
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}

	return 0;
}
