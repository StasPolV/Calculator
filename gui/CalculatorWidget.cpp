#include "CalculatorWidget.h"
#include "TopBarWidget.h"
#include "DisplayWidget.h"
#include "KeypadWidget.h"
#include "SettingsWidget.h"
#include "HistoryWidget.h"
#include "ScalableIconButton.h"

#include <QVBoxLayout>
#include <QResizeEvent>

#include <algorithm>

CalculatorWidget::CalculatorWidget(SettingsWidget* settings_widget, QWidget* parent) : QWidget(parent)
{
    setMinimumSize(320, 500);

    m_top_bar = new TopBarWidget(this);
    m_display = new DisplayWidget(this);
    m_keypad = new KeypadWidget(this);
    m_settings_widget = settings_widget;
    m_settings_widget->setParent(this);
    m_history_widget = new HistoryWidget(this);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addWidget(m_top_bar, 1);
    layout->addSpacing(10);
    layout->addWidget(m_display, 3);
    layout->addWidget(m_keypad, 10);

    WireSignals();
}

void CalculatorWidget::ChangeSettingsButtonTheme(QString theme) 
{
    if (theme == "Dark") 
    {
        m_top_bar->GetButtonSettings()->SetIconSource(":/images/settings_white.png");
        m_top_bar->GetButtonHistory()->SetIconSource(":/images/clock_with_arrow_white.png");
    }
    else if (theme == "White") 
    {
        m_top_bar->GetButtonSettings()->SetIconSource(":/images/settings_black.png");
        m_top_bar->GetButtonHistory()->SetIconSource(":/images/clock_with_arrow_black.png");
    }
}

void CalculatorWidget::WireSignals()
{
    connect(m_top_bar, &TopBarWidget::SettingsToggleRequested, this, [this]()
        {
            m_settings_widget->IsOpen() ? m_settings_widget->Close() : m_settings_widget->Open();
            m_top_bar->raise();
        });
    connect(m_top_bar, &TopBarWidget::HistoryToggleRequested, this, [this]()
        {
            m_history_widget->IsOpen() ? m_history_widget->Close() : m_history_widget->Open();
        });

    connect(this, &CalculatorWidget::EvaluateClicked, this, [this](const std::string& expression) 
        {
            m_cur_expr = QString::fromStdString(expression);
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

void CalculatorWidget::AddHistory(double result) 
{
    m_history_widget->AddHistory(QString("%1 = %2").arg(m_cur_expr).arg(result));
}

void CalculatorWidget::ShowResult(double result)
{
    m_display->ShowResult(result);
}

void CalculatorWidget::SetPrecision(int precision) 
{
    m_display->SetPrecision(precision);
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

    m_top_bar->SetButtonsSide(side);

    if (m_settings_widget->height() != height() || event->size().width() != event->oldSize().width())
    {
        m_settings_widget->SyncHeight();
    }
    if (m_history_widget->width() != width() || event->size().height() != event->oldSize().height())
    {
        m_history_widget->SyncWidth();
    }
}
