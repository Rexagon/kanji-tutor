#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QMainWindow>
#include <QPushButton>

#include "pagecategorytests.h"
#include "pagecategorykanji.h"
#include "pagecategory.h"
#include "pagelesson.h"
#include "pagestart.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
private:
    enum Pages {
        StartPage,
        CategoryPage,
		LessonPage,
		CategoryKanjiPage,
		CategoryTestsPage
	};

	void createMenu();

	Ui::MainWindow *ui;

	std::unique_ptr<PageStart> m_pageStart;
	std::unique_ptr<PageCategory> m_pageCategory;
	std::unique_ptr<PageLesson> m_pageLesson;
	std::unique_ptr<PageCategoryKanji> m_pageCategoryKanji;
	std::unique_ptr<PageCategoryTests> m_pageCategoryTests;
};

#endif // MAINWINDOW_H
