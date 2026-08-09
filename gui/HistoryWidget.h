#pragma once

#include <QWidget>

class QPropertyAnimation;

class HistoryWidget : public QWidget 
{
	Q_OBJECT
public:
	explicit HistoryWidget(QWidget* parent = nullptr);

	void Open();
	void Close();
	void SyncWidth();

	bool IsOpen() const;
private:
	QPropertyAnimation* Animate(QRect from, QRect to);

	bool m_is_open = false;
};
