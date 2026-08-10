#include "SettingsWidget.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>

#include <algorithm>

namespace
{
	constexpr int kWidth = 320;
}

SettingsWidget::SettingsWidget(QWidget* parent) : QWidget(parent)
{
	setFixedWidth(kWidth);

	setAutoFillBackground(true);
	setAttribute(Qt::WA_StyledBackground, true);

	hide();

	QHBoxLayout* theme_layout = new QHBoxLayout;
	m_combo_box = new QComboBox(this);
	m_combo_box->addItem("Dark");
	m_combo_box->addItem("White");
	QLabel* theme_label = new QLabel("Application Theme: ", this);
	theme_layout->addWidget(theme_label);
	theme_layout->addWidget(m_combo_box);

	QHBoxLayout* precision_layout = new QHBoxLayout;
	m_precision_slider = new QSlider(Qt::Orientation::Horizontal, this);
	m_precision_slider->setRange(0, 10);
	QLabel* precision_label = new QLabel("Calculation Precision: ", this);
	m_precision_spin_box = new QSpinBox(this);
	m_precision_spin_box->setRange(0, 10);
	precision_layout->addWidget(precision_label);
	precision_layout->addWidget(m_precision_spin_box);
	precision_layout->addWidget(m_precision_slider);

	QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(theme_layout);
	main_layout->addLayout(precision_layout);

	connect(m_precision_spin_box, &QSpinBox::valueChanged, m_precision_slider, &QSlider::setValue);
	connect(m_precision_slider, &QSlider::valueChanged, m_precision_spin_box, &QSpinBox::setValue);

	connect(m_precision_spin_box, &QSpinBox::valueChanged, this, &SettingsWidget::PrecisionChanged);

	connect(m_combo_box, &QComboBox::currentTextChanged, this, &SettingsWidget::ThemeChanged);
}

void SettingsWidget::SetPrecision(int precision)
{
	const QSignalBlocker blocker_spin(m_precision_spin_box);
	const QSignalBlocker blocker_slider(m_precision_slider);

	m_precision_spin_box->setValue(precision);
	m_precision_slider->setValue(precision);
}

void SettingsWidget::SetTheme(QString theme)
{
	const QSignalBlocker blocker_theme(m_combo_box);

	m_combo_box->setCurrentText(theme);
}

void SettingsWidget::Open()
{
	if (m_is_open)
	{
		return;
	}

	m_is_open = true;
	raise();
	const QRect closed(-kWidth, 0, kWidth, parentWidget()->height());
	const QRect opened(0, 0, kWidth, parentWidget()->height());

	setGeometry(closed);
	show();

	Animate(closed, opened);
}

void SettingsWidget::Close()
{
	if (!m_is_open)
	{
		return;
	}

	m_is_open = false;
	const QRect closed(-width(), 0, width(), parentWidget()->height());
	auto* anim = Animate(geometry(), closed);
	connect(anim, &QPropertyAnimation::finished, this, &SettingsWidget::hide);
}

void SettingsWidget::SyncHeight()
{
	setGeometry(m_is_open ? 0 : -kWidth, 0, kWidth, parentWidget()->height());
}

QPropertyAnimation* SettingsWidget::Animate(QRect from, QRect to)
{
	auto* anim = new QPropertyAnimation(this, "geometry", this);
	anim->setDuration(200);
	anim->setStartValue(from);
	anim->setEndValue(to);
	anim->setEasingCurve(QEasingCurve::OutCubic);
	anim->start(QAbstractAnimation::DeleteWhenStopped);
	return anim;
}
