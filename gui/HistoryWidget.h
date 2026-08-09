#pragma once

#include <QWidget>
#include <QString>

class QPropertyAnimation;
class QVBoxLayout;

class HistoryWidget : public QWidget 
{
	Q_OBJECT

signals:
	void HistoryButtonClicked(QString result);

public:
	explicit HistoryWidget(QWidget* parent = nullptr);

	void AddHistory(QString full_expression);

	void Open();
	void Close();
	void SyncWidth();

	bool IsOpen() const;
private:
	QPropertyAnimation* Animate(QRect from, QRect to);

	bool m_is_open = false;
	QWidget* m_buttons_container;
	QVBoxLayout* m_container_layout;
};
