#include "CalculatorController.h"
#include "CalculatorModel.h"
#include "CalculatorWidget.h"
#include "SettingsWidget.h"


#include <QApplication>

int main(int argc, char* argv[]) 
{
	QApplication app(argc, argv);

	SettingsWidget settings_view;

	CalculatorModel model;
	CalculatorWidget view(&settings_view);
	CalculatorController(model, view);

	view.show();

	return app.exec();
}
