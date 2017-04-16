#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QMainWindow>
#include <QPushButton>

#include "PageCategoryTests.h"
#include "PageCategoryKanji.h"
#include "PageCategory.h"
#include "PageExercise.h"
#include "PageLesson.h"
#include "PageStart.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
private:
	void createMenu();

	Ui::MainWindow* m_ui;

	std::unique_ptr<PageStart> m_pageStart;
	std::unique_ptr<PageCategory> m_pageCategory;
	std::unique_ptr<PageLesson> m_pageLesson;
	std::unique_ptr<PageCategoryKanji> m_pageCategoryKanji;
	std::unique_ptr<PageCategoryTests> m_pageCategoryTests;
	std::unique_ptr<PageExercise> m_pageExercise;
};

#endif // MAINWINDOW_H
