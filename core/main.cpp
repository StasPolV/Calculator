#include "CalculatorController.h"
#include "CalculatorModel.h"
#include "CalculatorWidget.h"

#include <QApplication>

int main(int argc, char* argv[]) 
{
	QApplication app(argc, argv);

	CalculatorModel model;
	CalculatorWidget view;
	CalculatorController(model, view);

	view.show();

	return app.exec();
}
