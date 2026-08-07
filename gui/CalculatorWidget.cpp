#include "CalculatorWidget.h"
#include "TopBarWidget.h"
#include "DisplayWidget.h"
#include "KeypadWidget.h"
#include "SettingsWidget.h"

#include <QVBoxLayout>
#include <QResizeEvent>

#include <algorithm>

CalculatorWidget::CalculatorWidget(QWidget* parent) : QWidget(parent)
{
    setMinimumSize(320, 500);

    m_top_bar = new TopBarWidget(this);
    m_display = new DisplayWidget(this);
    m_keypad = new KeypadWidget(this);
    m_settings_widget = new SettingsWidget(this);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addWidget(m_top_bar, 1);
    layout->addSpacing(10);
    layout->addWidget(m_display, 3);
    layout->addWidget(m_keypad, 10);

    WireSignals();
}

void CalculatorWidget::WireSignals()
{
    connect(m_top_bar, &TopBarWidget::SettingsToggleRequested, this, [this]()
        {
            m_settings_widget->IsOpen() ? m_settings_widget->Close() : m_settings_widget->Open();
            m_top_bar->raise();
        });

    connect(m_display, &DisplayWidget::EvaluateRequested, this, &CalculatorWidget::EvaluateClicked);

    connect(m_keypad, &KeypadWidget::DigitPressed, m_display, &DisplayWidget::InsertText);
    connect(m_keypad, &KeypadWidget::OperatorPressed, m_display, &DisplayWidget::InsertText);
    connect(m_keypad, &KeypadWidget::ClearRequested, m_display, &DisplayWidget::Clear);

    connect(m_keypad, &KeypadWidget::EqualsPressed, this, [this]()
        {
            emit EvaluateClicked(m_display->Text().toStdString());
        });

    connect(m_keypad, &KeypadWidget::FunctionRequested, this, [this](QString format_template)
        {
            const QString wrapped = format_template.arg(m_display->Text());
            m_display->SetText(wrapped);
            emit EvaluateClicked(wrapped.toStdString());
        });
}

void CalculatorWidget::ShowResult(double result)
{
    m_display->ShowResult(result);
}

void CalculatorWidget::ShowError(QString error)
{
    m_display->ShowError(error);
}

void CalculatorWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    const int base = std::min(width(), height());
    const int side = std::clamp(static_cast<int>(base * 0.10), 24, 72);

    m_top_bar->SetButtonSide(side);

    if (m_settings_widget->height() != height() || event->size().width() != event->oldSize().width())
    {
        m_settings_widget->SyncHeight();
    }
}
