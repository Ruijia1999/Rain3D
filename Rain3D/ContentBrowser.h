#pragma once

#include <QWidget>
#include "ui_ContentBrowser.h"

class ContentBrowser : public QWidget
{
	Q_OBJECT

public:
	ContentBrowser(QWidget *parent = nullptr);
	~ContentBrowser();

private:
	Ui::ContentBrowserClass ui;
};
