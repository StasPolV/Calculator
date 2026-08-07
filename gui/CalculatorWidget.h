#pragma once

#include <QWidget>
#include <QString>

#include <string>

class TopBarWidget;
class DisplayWidget;
class KeypadWidget;
class SettingsWidget;

// Composition root of the calculator GUI. Owns TopBarWidget, DisplayWidget,
// KeypadWidget and SettingsWidget, wires their signals to each other, and
// exposes the same minimal public interface CalculatorController expects:
// EvaluateClicked signal, ShowResult/ShowError slots. Nothing outside this
// class needs to know that the calculator is made of four sub-widgets.
class CalculatorWidget : public QWidget
{
	Q_OBJECT

signals:
	void EvaluateClicked(const std::string& expression);

public slots:
	void ShowResult(double result);
	void ShowError(QString error);

public:
	explicit CalculatorWidget(QWidget* parent = nullptr);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	void WireSignals();

	TopBarWidget* m_top_bar;
	DisplayWidget* m_display;
	KeypadWidget* m_keypad;
	SettingsWidget* m_settings_widget;
};
