#include "CalculatorWidget.h"

#include <QGridLayout>
#include <QPushButton>
#include <QRegularExpressionValidator>

namespace
{
    QPushButton* createButton(const QString& text, QWidget* parent)
    {
        auto* button = new QPushButton(text, parent);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        return button;
    }
}

void CalculatorWidget::ShowResult(double result) 
{
    m_line_edit->setText(QString::number(result));
}

CalculatorWidget::CalculatorWidget(QWidget* parent) : QWidget(parent)
{
    m_line_edit = new QLineEdit(this);
    m_line_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(m_line_edit, &QLineEdit::returnPressed, this, [this]()
        {
            emit EvaluateClicked(m_line_edit->text().toStdString());
        });

    auto* validator = new QRegularExpressionValidator(QRegularExpression(R"(^[0-9+\-*/(). ^sqrt]*$)"), this);
    m_line_edit->setValidator(validator);

    auto* main_layout = new QGridLayout(this);
    main_layout->addWidget(m_line_edit, 0, 0, 1, 4);

    struct ButtonInfo { QString text; int row; int col; };

    static const std::vector<ButtonInfo> buttons = {
        {"7", 2, 0}, {"8", 2, 1}, {"9", 2, 2},
        {"4", 3, 0}, {"5", 3, 1}, {"6", 3, 2},
        {"1", 4, 0}, {"2", 4, 1}, {"3", 4, 2},
        {"0", 5, 0}, {".", 5, 1}, {"=", 5, 2},
        {"/", 2, 3}, {"*", 3, 3}, {"-", 4, 3}, {"+", 5, 3},
    };

    for (const auto& info : buttons) 
    {
        auto* button = createButton(info.text, this);
        bool is_number;

        int value = info.text.toInt(&is_number);
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

    main_layout->addWidget(button_one_over_x, 1, 0);
    main_layout->addWidget(button_power, 1, 1);
    main_layout->addWidget(button_sqrt, 1, 2);
    main_layout->addWidget(button_clear, 1, 3);

    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setRowStretch(0, 1);
    for (int row = 1; row <= 5; ++row) 
    {
        main_layout->setRowStretch(row, 2);
    }
}

void CalculatorWidget::resizeEvent(QResizeEvent* event) 
{
    QWidget::resizeEvent(event);

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
