#pragma once

#include <QWidget>
#include <QResizeEvent>
#include <QPropertyAnimation>

class QSpinBox;

class SettingsWidget : public QWidget 
{
	Q_OBJECT

signals:
	void PrecisionChanged(int precision);
	void ThemeChanged(QString theme);

public:
	explicit SettingsWidget(QWidget* parent = nullptr);

	void Open();
	void Close();
	void SyncHeight();

	bool IsOpen() const { return m_is_open; }

private:
	QPropertyAnimation* Animate(QRect from, QRect to);

	bool m_is_open = false;
};
