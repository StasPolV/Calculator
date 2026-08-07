#include "SettingsController.h"

SettingsController::SettingsController(SettingsModel& model, SettingsWidget& view, QObject* parent) : QObject(parent), m_model(model), m_view(view)
{
	connect(&m_view, &SettingsWidget::PrecisionChanged, &m_model, &SettingsModel::SetPrecision);
	connect(&m_view, &SettingsWidget::ThemeChanged, &m_model, &SettingsModel::SetTheme);

	m_view.SetPrecision(m_model.GetPrecision());
}
