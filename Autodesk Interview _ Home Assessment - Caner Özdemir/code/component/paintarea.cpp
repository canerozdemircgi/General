#include "paintarea.h"

#include "data/configuration.h"

#include <QMouseEvent>
#include <QPainter>

PaintArea::PaintArea(QWidget *parent)
	: QWidget(parent)
	, penBrush(QColor(), 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
	, penCursor(QColor(), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
{
	this->setImageSource(QPixmap(Configuration::initialImageBackground));
}

void PaintArea::setImageSource(const QPixmap &imageSource)
{
	this->imageSourceOriginal = imageSource;
	this->imageLayerOriginal = QImage(imageSource.size(), QImage::Format_RGBA8888);
	this->refreshImageScaled();
}

void PaintArea::setImageZoom(const double imageZoom)
{
	this->imageZoom = imageZoom;
	this->refreshImageScaled();
}

void PaintArea::refreshImageScaled()
{
	const QSize size(this->imageSourceOriginal.size() * this->imageZoom);

	this->imageSourceScaled = this->imageSourceOriginal.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	this->imageLayerScaled = this->imageLayerOriginal.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	this->resize(size);
}

void PaintArea::setPenSize(const double penSize)
{
	this->penBrush.setWidthF(penSize);
	this->refreshCursor();
}

void PaintArea::setPenColor(const QColor &penColor)
{
	this->penColor = penColor;
	const int penAlpha(this->penBrush.color().alpha());

	this->penBrush.setColor(QColor(penColor.red(), penColor.green(), penColor.blue(), penAlpha));
	this->penCursor.setColor(penColor);

	this->refreshCursor();
}

void PaintArea::setPenAlpha(const int penAlpha)
{
	this->penAlpha = penAlpha;
	this->refreshPenAlpha();
}

void PaintArea::setPaintTool(const PaintTool paintTool)
{
	this->paintTool = paintTool;
	switch (this->paintTool)
	{
		case Pen:
			this->penCursor.setColor(this->penColor);
			break;
		case Eraser:
			this->penCursor.setColor(Qt::black);
			break;
	}
	this->refreshCursor();
	this->refreshPenAlpha();
}

void PaintArea::refreshCursor()
{
	const double circleWidth(this->penCursor.widthF());
	const double cursorSize(this->penBrush.widthF() + circleWidth);

	QPixmap pixmap(cursorSize, cursorSize);
	pixmap.fill(Qt::transparent);

	QPainter painter(&pixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(this->penCursor);
	painter.drawEllipse(circleWidth / 2, circleWidth / 2, cursorSize - circleWidth, cursorSize - circleWidth);

	this->setCursor(QCursor(pixmap));
}

void PaintArea::refreshPenAlpha()
{
	const QColor penColor(this->penBrush.color());
	this->penBrush.setColor(QColor(penColor.red(), penColor.green(), penColor.blue(), this->paintTool == Eraser ? 255 - this->penAlpha : this->penAlpha));
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
	this->isDrawing = true;
	this->startPoint = event->pos();
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
	this->drawTool(event->pos());
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
	this->drawTool(event->pos());
	this->isDrawing = false;
	this->update(); // full update is required to reconstruct image with SmoothTransformation
}

void PaintArea::drawTool(const QPoint &endPoint)
{
	QPainter painter(&this->imageLayerOriginal);
	switch (this->paintTool)
	{
		/*
		case Pen:
			painter.setCompositionMode(QPainter::CompositionMode_SourceOver); // default composition mode is CompositionMode_SourceOver anyway
			break;
		*/
		case Eraser:
			painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
			break;
	}
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(this->penBrush);
	const double zoomInverse(1 / this->imageZoom);
	painter.drawLine(this->startPoint * zoomInverse, endPoint * zoomInverse);
	this->imageLayerScaled = this->imageLayerOriginal.scaled(this->imageSourceScaled.size(), Qt::IgnoreAspectRatio, isDrawing ? Qt::FastTransformation : Qt::SmoothTransformation);

	const int radius((this->penBrush.widthF() + 1) / 2);
	this->update(QRect(this->startPoint, endPoint).normalized().adjusted(-radius, -radius, radius, radius));
	this->startPoint = endPoint;
}

void PaintArea::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.drawPixmap(0, 0, this->imageSourceScaled);
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage(0, 0, this->imageLayerScaled);
}