#pragma once

#include "SettingsModel.h"
#include "SettingsWidget.h"

#include <QObject>

class SettingsController : public QObject
{
	Q_OBJECT
public:
	SettingsController(SettingsModel& model, SettingsWidget& view, QObject* parent = nullptr);

private:
	SettingsModel& m_model;
	SettingsWidget& m_view;
};
