/*************************************************
 * This file just starts up the whole program by *
 * rendering the form                            *
 * Done by Visual Studios 2012                   *
 ************************************************/

#include "ui_display.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace UIDisplay;

[System::STAThreadAttribute]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

	UIDisplay::UiDisplay form;
    Application::Run(%form);
}