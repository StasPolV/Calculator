#include "TopBarWidget.h"
#include "ScalableIconButton.h"

#include <QHBoxLayout>
#include <QSize>

TopBarWidget::TopBarWidget(QWidget* parent) : QWidget(parent)
{
    m_button_settings = new ScalableIconButton(this);
    SetIcon(":/images/settings_white.png");
    m_button_settings->SetIconRatio(0.75);
    m_button_settings->setAutoRaise(true);

    connect(m_button_settings, &ScalableIconButton::clicked, this, &TopBarWidget::SettingsToggleRequested);

    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_button_settings, 0, Qt::AlignLeft | Qt::AlignVCenter);
    layout->addStretch(1);
}

void TopBarWidget::SetIcon(QString icon) 
{
    m_button_settings->SetIconSource(icon);
}

void TopBarWidget::SetButtonSide(int side)
{
    if (m_button_settings->size() != QSize(side, side))
    {
        m_button_settings->setFixedSize(side, side);
    }
}
