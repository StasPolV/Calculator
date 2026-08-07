#include "SettingsModel.h"

SettingsModel::SettingsModel(QObject* parent) : QObject(parent)
{

}

void SettingsModel::SetPrecision(int precision) 
{
	m_precision = precision;

	emit PrecisionChanged(precision);
}

void SettingsModel::SetTheme(QString theme) 
{
	m_theme = (theme == "Dark Theme") ? Theme::DARK : Theme::WHITE;

	// TODO: emit ThemeChanged
}
