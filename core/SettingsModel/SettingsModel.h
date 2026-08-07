#pragma once

#include <string>

#include <QObject>
#include <QSettings>

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

public slots:
	void SetPrecision(int precision);
	void SetTheme(QString theme);

public:
	explicit SettingsModel(QObject* parent = nullptr);

	int GetPrecision() const { return m_precision;  }

private:
	QSettings m_settings;
	int m_precision;
	Theme m_theme = Theme::DARK;
};
