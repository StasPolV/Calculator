#include "SettingsController.h"
#include "utils.h"

#include <QApplication>
#include <QString>

namespace 
{
	void setTheme(QString theme) 
	{
		if (theme == "Dark")
		{
			qApp->setStyleSheet(utils::loadStyleSheet(":/styles/theme_dark.qss"));
		}
		else if (theme == "White")
		{
			qApp->setStyleSheet(utils::loadStyleSheet(":/styles/theme_light.qss"));
		}
	}
}

SettingsController::SettingsController(SettingsModel& model, SettingsWidget& view, QObject* parent) : QObject(parent), m_model(model), m_view(view)
{
	connect(&m_view, &SettingsWidget::PrecisionChanged, &m_model, &SettingsModel::SetPrecision);
	connect(&m_view, &SettingsWidget::ThemeChanged, &m_model, &SettingsModel::SetTheme);

	m_view.SetPrecision(m_model.GetPrecision());
	m_view.SetTheme(m_model.GetTheme());

	QString theme = m_model.GetTheme();
	setTheme(theme);


	connect(&m_model, &SettingsModel::ThemeChanged, this, [this](QString theme) 
		{
			setTheme(theme);
		});
}
