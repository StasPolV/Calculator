#pragma once

#include <QWidget>
#include <QString>

#include <string>

class TopBarWidget;
class DisplayWidget;
class KeypadWidget;
class SettingsWidget;
class HistoryWidget;

class CalculatorWidget : public QWidget
{
	Q_OBJECT

signals:
	void EvaluateClicked(const std::string& expression);

public slots:
	void ShowResult(double result);
	void AddHistory(double result);
	void ShowError(QString error);
	void SetPrecision(int precision);
	void ChangeSettingsButtonTheme(QString theme);

public:
	explicit CalculatorWidget(SettingsWidget* settings_widget, QWidget* parent = nullptr);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	void WireSignals();

	TopBarWidget* m_top_bar;
	DisplayWidget* m_display;
	KeypadWidget* m_keypad;
	SettingsWidget* m_settings_widget;
	HistoryWidget* m_history_widget;
	QString m_cur_expr;
};
