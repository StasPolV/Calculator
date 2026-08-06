#include "CalculatorWidget.h"
#include "ScalableIconButton.h"

#include <QGridLayout>
#include <QPushButton>
#include <QRegularExpressionValidator>
#include <QFile>
#include <QStyle>
#include <QSize>

#include <algorithm>

namespace
{
    QPushButton* createButton(QString text, QWidget* parent)
    {
        auto* button = new QPushButton(text, parent);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        return button;
    }

    QString loadStyleSheet(QString resource_path)
    {
        QFile file(resource_path);
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            return QString();
        }

        return QLatin1String(file.readAll());
    }
}

void CalculatorWidget::UpdateStyle()
{
    m_label->style()->unpolish(m_label);
    m_label->style()->polish(m_label);
}

void CalculatorWidget::ShowResult(double result)
{
    m_line_edit->setText(QString::number(result));
}

void CalculatorWidget::ShowError(QString error)
{
    m_label->setText(error);
    m_label->setProperty("hasError", true);

    UpdateStyle();
}

void CalculatorWidget::ResetErrorStyle()
{
    if (!m_label->property("hasError").toBool())
    {
        return;
    }

    m_label->setText("");
    m_label->setProperty("hasError", false);
    UpdateStyle();
}

CalculatorWidget::CalculatorWidget(QWidget* parent) : QWidget(parent)
{
    m_button_settings = new ScalableIconButton(this);
    m_button_settings->SetIconSource(":/images/settings_white.png");
    m_button_settings->SetIconRatio(0.75);
    m_button_settings->setAutoRaise(true);

    m_line_edit = new QLineEdit(this);
    m_line_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(m_line_edit, &QLineEdit::returnPressed, this, [this]()
        {
            emit EvaluateClicked(m_line_edit->text().toStdString());
        });
    connect(m_line_edit, &QLineEdit::textChanged, this, &CalculatorWidget::ResetErrorStyle);

    auto* validator = new QRegularExpressionValidator(QRegularExpression(R"(^[0-9+\-*/(). ^sqrt]*$)"), this);
    m_line_edit->setValidator(validator);

    auto* main_layout = new QGridLayout(this);

    main_layout->addWidget(m_button_settings, 0, 0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    main_layout->addWidget(m_line_edit, 1, 0, 1, 4);
    main_layout->setRowMinimumHeight(2, 10);

    m_label = new QLabel(this);
    QString style = loadStyleSheet(":/styles/label.qss");
    m_label->setStyleSheet(style);

    main_layout->addWidget(m_label, 3, 0, 1, 4);

    struct ButtonInfo { QString text; int row; int col; };

    static const std::vector<ButtonInfo> buttons = {
        {"7", 5, 0}, {"8", 5, 1}, {"9", 5, 2},
        {"4", 6, 0}, {"5", 6, 1}, {"6", 6, 2},
        {"1", 7, 0}, {"2", 7, 1}, {"3", 7, 2},
        {"0", 8, 0}, {".", 8, 1}, {"=", 8, 2},
        {"/", 5, 3}, {"*", 6, 3}, {"-", 7, 3}, {"+", 8, 3},
    };

    for (const auto& info : buttons)
    {
        auto* button = createButton(info.text, this);
        bool is_number;

        info.text.toInt(&is_number);
        if (is_number)
        {
            connect(button, &QPushButton::clicked, this, [this, info]() { ClickDigit(info.text); });
        }

        if (info.text == "=")
        {
            connect(button, &QPushButton::clicked, this, [this]() { emit EvaluateClicked(m_line_edit->text().toStdString()); });
        }
        else if (info.text == ".")
        {
            connect(button, &QPushButton::clicked, this, [this]() { m_line_edit->insert("."); });
        }
        else if (!is_number)
        {
            connect(button, &QPushButton::clicked, this, [this, info]() { ClickOp(info.text); });
        }

        main_layout->addWidget(button, info.row, info.col);
    }

    QPushButton* button_one_over_x = createButton("1/x", this);
    QPushButton* button_power = createButton("x²", this);
    QPushButton* button_sqrt = createButton("²√x", this);
    QPushButton* button_clear = createButton("C", this);

    auto wrap_text = [this](const char* wrap)
        {
            QString text = m_line_edit->text();
            QString wrapped = QString(wrap).arg(text);
            m_line_edit->setText(wrapped);
            emit EvaluateClicked(wrapped.toStdString());
        };

    connect(button_one_over_x, &QPushButton::clicked, this, [wrap_text]()
        {
            wrap_text("1/(%1)");
        });

    connect(button_power, &QPushButton::clicked, this, [wrap_text]()
        {
            wrap_text("(%1)^2");
        });

    connect(button_sqrt, &QPushButton::clicked, this, [wrap_text]()
        {
            wrap_text("sqrt(%1)");
        });

    connect(button_clear, &QPushButton::clicked, this, [this]()
        {
            m_line_edit->setText("");
        });

    main_layout->addWidget(button_one_over_x, 4, 0);
    main_layout->addWidget(button_power, 4, 1);
    main_layout->addWidget(button_sqrt, 4, 2);
    main_layout->addWidget(button_clear, 4, 3);

    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    main_layout->setRowStretch(0, 1);
    main_layout->setRowStretch(1, 1);
    main_layout->setRowStretch(2, 0.5);
    main_layout->setRowStretch(3, 1);
    for (int row = 4; row <= 8; ++row)
    {
        main_layout->setRowStretch(row, 2);
    }

    for (int col = 0; col < 4; ++col)
    {
        main_layout->setColumnStretch(col, 1);
    }
}

void CalculatorWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    const int base = std::min(width(), height());
    const int side = std::clamp(static_cast<int>(base * 0.10), 24, 72);

    if (m_button_settings->size() != QSize(side, side))
    {
        m_button_settings->setFixedSize(side, side);
    }

    QFont font = m_line_edit->font();
    font.setPixelSize(std::max(10, m_line_edit->height() / 2));
    m_line_edit->setFont(font);
}

void CalculatorWidget::ClickDigit(QString digit)
{
    m_line_edit->insert(digit);
}

void CalculatorWidget::ClickOp(QString op)
{
    m_line_edit->insert(op);
}
