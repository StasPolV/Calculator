#pragma once

#include <QPropertyAnimation>
#include <QResizeEvent>
#include <QWidget>

class QSpinBox;
class QSlider;
class QSpinBox;
class QComboBox;

class SettingsWidget : public QWidget
{
	Q_OBJECT

signals:
	void PrecisionChanged(int precision);
	void ThemeChanged(QString theme);

public slots:
	void SetPrecision(int precision);
	void SetTheme(QString theme);

public:
	explicit SettingsWidget(QWidget* parent = nullptr);

	void Open();
	void Close();
	void SyncHeight();

	bool IsOpen() const { return m_is_open; }

private:
	QPropertyAnimation* Animate(QRect from, QRect to);

	bool m_is_open = false;
	QSlider* m_precision_slider;
	QSpinBox* m_precision_spin_box;
	QComboBox* m_combo_box;
};
