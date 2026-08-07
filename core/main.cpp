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
	QApplication app(argc, argv);

	SettingsModel settings_model;
	SettingsWidget* settings_view = new SettingsWidget;
	SettingsController(settings_model, *settings_view);

	CalculatorModel model;
	CalculatorWidget view(settings_view);
	CalculatorController(model, view);

	QObject::connect(&settings_model, &SettingsModel::PrecisionChanged, &view, &CalculatorWidget::SetPrecision);
	view.SetPrecision(settings_model.GetPrecision());

	view.show();

	return app.exec();
}
