#include "SettingsModel.h"

SettingsModel::SettingsModel(QObject* parent) : QObject(parent)
{
	m_precision = m_settings.value("precision", 2).toInt();
	// TODO: add theme in settings
}

void SettingsModel::SetPrecision(int precision) 
{
	m_precision = precision;
	m_settings.setValue("precision", precision);

	emit PrecisionChanged(precision);
}

void SettingsModel::SetTheme(QString theme) 
{
	m_theme = (theme == "Dark") ? Theme::DARK : Theme::WHITE;

	emit ThemeChanged(theme);
}
