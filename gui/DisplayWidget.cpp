#include "DisplayWidget.h"

#include "ScalableLineEdit.h"
#include "utils.h"

#include <QFile>
#include <QLabel>
#include <QRegularExpressionValidator>
#include <QStyle>
#include <QVBoxLayout>

DisplayWidget::DisplayWidget(QWidget* parent) : QWidget(parent)
{
	m_line_edit = new ScalableLineEdit(this);
	m_line_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(m_line_edit, &QLineEdit::returnPressed, this,
	        [this]() { emit EvaluateRequested(m_line_edit->text().toStdString()); });
	connect(m_line_edit, &QLineEdit::textChanged, this, &DisplayWidget::ResetErrorStyle);

	auto* validator =
	        new QRegularExpressionValidator(QRegularExpression(R"(^[0-9+\-*/(). ^sqrt]*$)"), this);
	m_line_edit->setValidator(validator);

	m_label = new QLabel(this);
	m_label->setStyleSheet(utils::loadStyleSheet(":/styles/label.qss"));

	auto* layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(m_line_edit, 1);
	layout->addSpacing(10);
	layout->addWidget(m_label, 1);
}

void DisplayWidget::InsertText(const QString& text)
{
	m_line_edit->insert(text);
}

void DisplayWidget::SetPrecision(int precision)
{
	m_precision = precision;
}

void DisplayWidget::SetText(const QString& text)
{
	m_line_edit->setText(text);
}

QString DisplayWidget::Text() const
{
	return m_line_edit->text();
}

void DisplayWidget::Clear()
{
	m_line_edit->setText("");
}

void DisplayWidget::ShowResult(double result)
{
	m_line_edit->setText(QString::number(result, 'f', m_precision));
}

void DisplayWidget::ShowError(QString error)
{
	m_label->setText(error);
	m_label->setProperty("hasError", true);

	UpdateStyle();
}

void DisplayWidget::ResetErrorStyle()
{
	if (!m_label->property("hasError").toBool())
	{
		return;
	}

	m_label->setText("");
	m_label->setProperty("hasError", false);
	UpdateStyle();
}

void DisplayWidget::UpdateStyle()
{
	m_label->style()->unpolish(m_label);
	m_label->style()->polish(m_label);
}
