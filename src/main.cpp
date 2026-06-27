#include <QApplication>

#include "CalculatorWidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
	CalculatorWidget calculator;
	calculator.show();
	return app.exec();
}
