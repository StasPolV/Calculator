#pragma once

#include <QPixmap>
#include <QSize>
#include <QString>
#include <QToolButton>

class QResizeEvent;

class ScalableIconButton : public QToolButton
{
	Q_OBJECT

public:
	explicit ScalableIconButton(QWidget* parent = nullptr);
	void SetIconSource(QString path);
	void SetIconRatio(double ratio);

	QSize sizeHint() const override;
	QSize minimumSizeHint() const override;

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	void UpdateIcon();

	bool m_icon_dirty = false;
	QPixmap m_source;
	double m_icon_ratio = 0.75;
};
