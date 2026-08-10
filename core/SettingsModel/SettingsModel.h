#pragma once

#include <QObject>
#include <QSettings>

#include <string>

class QString;

enum Theme
{
	DARK,
	WHITE,
};

class SettingsModel : public QObject
{
	Q_OBJECT

signals:
	void PrecisionChanged(int precision);
	void ThemeChanged(QString theme);

public slots:
	void SetPrecision(int precision);
	void SetTheme(QString theme);

public:
	explicit SettingsModel(QObject* parent = nullptr);

	int GetPrecision() const { return m_precision; }
	QString GetTheme() const
	{
		switch (m_theme)
		{
		case Theme::DARK: return "Dark"; break;
		case Theme::WHITE: return "White"; break;
		}

		return "None";  // TODO: add handling
	}

private:
	QSettings m_settings;
	int m_precision;
	Theme m_theme = Theme::DARK;
};
