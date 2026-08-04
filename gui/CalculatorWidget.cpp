#include "CalculatorWidget.h"
#include <QGridLayout>
#include <QPushButton>

namespace
{
    QPushButton* createButton(const QString& text, QWidget* parent)
    {
        auto* button = new QPushButton(text, parent);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        return button;
    }
}

CalculatorWidget::CalculatorWidget(QWidget* parent) : QWidget(parent)
{
    m_line_edit = new QLineEdit(this);
    m_line_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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
        main_layout->addWidget(createButton(info.text, this), info.row, info.col);
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
