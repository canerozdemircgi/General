#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPen>

enum PaintTool
{
	Pen,
	Eraser
};

class PaintArea : public QWidget
{
	Q_OBJECT

public:
	explicit PaintArea(QWidget *parent = nullptr);

	void setImageSource(const QPixmap &imageSource);
	void setImageZoom(const double imageZoom);

	void setPenSize(const double penSize);
	void setPenColor(const QColor &penColor);
	void setPenAlpha(const int penAlpha);

	void setPaintTool(const PaintTool paintTool);

private:
	QPixmap imageSourceOriginal;
	QImage imageLayerOriginal;

	QPixmap imageSourceScaled;
	QImage imageLayerScaled;
	double imageZoom;
	void refreshImageScaled();

	QPen penBrush;
	QColor penColor;
	int penAlpha;
	void refreshPenAlpha();

	QPoint startPoint;
	PaintTool paintTool;
	bool isDrawing;
	void drawTool(const QPoint &endPoint);

	QPen penCursor;
	void refreshCursor();

	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

	void paintEvent(QPaintEvent *event) override;
};

#endif // DRAWWIDGET_H