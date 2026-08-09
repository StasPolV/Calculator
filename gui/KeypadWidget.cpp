#include "KeypadWidget.h"

#include "ScalableButton.h"

#include <QGridLayout>

#include <vector>

namespace
{
    ScalableButton* createButton(QString text, QWidget* parent)
    {
        auto* button = new ScalableButton(text, parent);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        button->SetFontRatio(0.25);
        return button;
    }
}

KeypadWidget::KeypadWidget(QWidget* parent) : QWidget(parent)
{
    auto* layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

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
        bool is_number = false;
        info.text.toInt(&is_number);

        if (info.text == "=")
        {
            connect(button, &QPushButton::clicked, this, &KeypadWidget::EqualsPressed);
            button->setObjectName("EqualsButton");
        }
        else if (info.text == ".")
        {
            connect(button, &QPushButton::clicked, this, [this]() { emit OperatorPressed("."); });
        }
        else if (is_number)
        {
            connect(button, &QPushButton::clicked, this, [this, info]() { emit DigitPressed(info.text); });
        }
        else
        {
            connect(button, &QPushButton::clicked, this, [this, info]() { emit OperatorPressed(info.text); });
        }

        layout->addWidget(button, info.row, info.col);
    }

    ScalableButton* button_one_over_x = createButton("1/x", this);
    ScalableButton* button_power = createButton("x²", this);
    ScalableButton* button_sqrt = createButton("²√x", this);
    ScalableButton* button_clear = createButton("C", this);

    connect(button_one_over_x, &QPushButton::clicked, this, [this]() { emit FunctionRequested("1/(%1)"); });
    connect(button_power, &QPushButton::clicked, this, [this]() { emit FunctionRequested("(%1)^2"); });
    connect(button_sqrt, &QPushButton::clicked, this, [this]() { emit FunctionRequested("sqrt(%1)"); });
    connect(button_clear, &QPushButton::clicked, this, &KeypadWidget::ClearRequested);

    layout->addWidget(button_one_over_x, 0, 0);
    layout->addWidget(button_power, 0, 1);
    layout->addWidget(button_sqrt, 0, 2);
    layout->addWidget(button_clear, 0, 3);

    for (int row = 0; row <= 4; ++row)
    {
        layout->setRowStretch(row, 1);
    }
}
