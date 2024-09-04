#ifndef MENUBAR_H
#define MENUBAR_H

#include "paintarea.h"

#include <QMenuBar>

QT_BEGIN_NAMESPACE
namespace Ui { class Main_QMenuBar; }
QT_END_NAMESPACE

class MenuBar : public QMenuBar
{
	Q_OBJECT

public:
	explicit MenuBar(QWidget *parent = nullptr);
	void init(PaintArea *paintArea);
	~MenuBar() override;

private:
	Ui::Main_QMenuBar *ui;

	PaintArea *paintArea;

private slots:
	void this_Open_QAction_triggered();
};

#endif // MENUBAR_H