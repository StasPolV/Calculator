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
        {"7", 1, 0}, {"8", 1, 1}, {"9", 1, 2},
        {"4", 2, 0}, {"5", 2, 1}, {"6", 2, 2},
        {"1", 3, 0}, {"2", 3, 1}, {"3", 3, 2},
        {"0", 4, 0}, {".", 4, 1}, {"=", 4, 2},
        {"/", 1, 3}, {"*", 2, 3}, {"-", 3, 3}, {"+", 4, 3},
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

    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setRowStretch(0, 1);
    for (int row = 1; row <= 4; ++row) 
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
