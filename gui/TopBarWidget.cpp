#include "TopBarWidget.h"
#include "ScalableIconButton.h"

#include <QHBoxLayout>
#include <QSize>

TopBarWidget::TopBarWidget(QWidget* parent) : QWidget(parent)
{
    m_button_settings = new ScalableIconButton(this);
    m_button_settings->SetIconSource(":/images/settings_white.png");
    m_button_settings->SetIconRatio(0.75);
    m_button_settings->setAutoRaise(true);

    m_button_history = new ScalableIconButton(this);
    m_button_history->SetIconSource(":/images/clock_with_arrow_white.png");
    m_button_history->SetIconRatio(0.75);
    m_button_history->setAutoRaise(true);

    connect(m_button_settings, &ScalableIconButton::clicked, this, &TopBarWidget::SettingsToggleRequested);

    auto* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_button_settings, 0, Qt::AlignLeft | Qt::AlignVCenter);
    layout->addStretch(1);
    layout->addWidget(m_button_history, 0, Qt::AlignRight | Qt::AlignVCenter);
}

void TopBarWidget::SetButtonsSide(int side)
{
    if (m_button_settings->size() != QSize(side, side))
    {
        m_button_settings->setFixedSize(side, side);
    }
    if (m_button_history->size() != QSize(side, side)) 
    {
        m_button_history->setFixedSize(side, side);
    }
}
