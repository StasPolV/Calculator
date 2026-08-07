#pragma once

#include <QWidget>

class ScalableIconButton;

class TopBarWidget : public QWidget
{
	Q_OBJECT

signals:
	void SettingsToggleRequested();

public:
	explicit TopBarWidget(QWidget* parent = nullptr);

	void SetButtonSide(int side);

private:
	ScalableIconButton* m_button_settings;
};
