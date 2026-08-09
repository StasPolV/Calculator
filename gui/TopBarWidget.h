#pragma once

#include <QWidget>

class ScalableIconButton;

class TopBarWidget : public QWidget
{
	Q_OBJECT

signals:
	void SettingsToggleRequested();
	void HistoryToggleRequested();

public:
	explicit TopBarWidget(QWidget* parent = nullptr);

	void SetButtonsSide(int side);
	ScalableIconButton* GetButtonSettings() const { return m_button_settings; }
	ScalableIconButton* GetButtonHistory() const { return m_button_history; }

private:
	ScalableIconButton* m_button_settings;
	ScalableIconButton* m_button_history;
};
