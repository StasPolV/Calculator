#include "CalculatorController.h"
#include "CalculatorModel.h"
#include "CalculatorWidget.h"
#include "SettingsController.h"
#include "SettingsModel.h"
#include "SettingsWidget.h"


#include <QApplication>
#include <QObject>

int main(int argc, char* argv[]) 
{
	QApplication::setOrganizationName("J3n1xCorporation");
	QApplication::setApplicationName("Qt-Calculator");

	QApplication app(argc, argv);

	SettingsWidget* settings_view = new SettingsWidget;
	SettingsModel settings_model;
	SettingsController settings_controller(settings_model, *settings_view);

	CalculatorModel model;
	CalculatorWidget view(settings_view);
	CalculatorController calculator_controller(model, view);

	QObject::connect(&settings_model, &SettingsModel::PrecisionChanged, &view, &CalculatorWidget::SetPrecision);
	view.SetPrecision(settings_model.GetPrecision());

	view.show();

	return app.exec();
}
