#include "SettingsModel.h"

SettingsModel::SettingsModel(QObject* parent) : QObject(parent)
{
	m_precision = m_settings.value("precision", 2).toInt();
	const QString theme = m_settings.value("theme", "Dark").toString();
	m_theme = (theme == "Dark") ? Theme::DARK : Theme::WHITE;
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
	switch (m_theme)
	{
	case Theme::DARK: m_settings.setValue("theme", "Dark"); break;
	case Theme::WHITE: m_settings.setValue("theme", "White"); break;
	}

	emit ThemeChanged(theme);
}
