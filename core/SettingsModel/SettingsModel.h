#pragma once

#include <string>

#include <QObject>
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
	int m_precision = 2;
	Theme m_theme = Theme::DARK;
};
