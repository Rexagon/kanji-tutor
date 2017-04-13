#include "mainwindow.h"
#include <ui_mainwindow.h>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	createMenu();

	m_pageStart = std::make_unique<PageStart>(ui);
	m_pageCategory = std::make_unique<PageCategory>(ui);
	m_pageLesson = std::make_unique<PageLesson>(ui);
	m_pageCategoryKanji = std::make_unique<PageCategoryKanji>(ui);
	m_pageCategoryTests = std::make_unique<PageCategoryTests>(ui);

	// Start page events
	connect(m_pageStart.get(), &PageStart::categorySelected, this, [this](Category* category) {
		m_pageCategory->setCategory(category);
		m_pageCategory->setCurrent();
	});

	// Category page events
	connect(m_pageCategory.get(), &PageCategory::backButtonPressed, this, [this]() {
		m_pageStart->setCurrent();
	});

	connect(m_pageCategory.get(), &PageCategory::kanjiButtonPressed, this, [this](Category* category) {
		m_pageCategoryKanji->setCategory(category);
		m_pageCategoryKanji->setCurrent();
	});

	connect(m_pageCategory.get(), &PageCategory::testsButtonPressed, this, [this](Category* category) {
		m_pageCategoryTests->setCategory(category);
		m_pageCategoryTests->setCurrent();
	});

	connect(m_pageCategory.get(), &PageCategory::lessonSelected, this, [this](Lesson* lesson) {
		m_pageLesson->setLesson(lesson);
		m_pageLesson->setCurrent();
	});

	// Lesson page events
	connect(m_pageLesson.get(), &PageLesson::backButtonPressed, this, [this]() {
		m_pageCategory->setCurrent();
	});

	// Category kanji page
	connect(m_pageCategoryKanji.get(), &PageCategoryKanji::backButtonPressed, this, [this]() {
		m_pageCategory->setCurrent();
	});

	// Category tests page
	connect(m_pageCategoryTests.get(), &PageCategoryTests::backButtonPressed, this, [this]() {
		m_pageCategory->setCurrent();
	});
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::createMenu()
{
    // File menu
    connect(ui->menuItemExit, &QAction::triggered, this, [this]() {
        this->close();
    });

    // Help menu
    connect(ui->menuItemAbout, &QAction::triggered, this, [this]() {
		QMessageBox messageBox;
		messageBox.setWindowTitle("О программе");
		messageBox.setText("<h3><b>Kanji tutor</b> <small>v1.2</small></h3>");
		messageBox.setInformativeText("<p>Небольшой помощник в непростом деле изучения японских иероглифов. С помощью тестов и карточек выучить их будет немного проще.</p>"\
									  "<p>Все уроки и категории данной программы хранятся как отдельные ресурсы, поэтому при обнаружении каких-то ошибок или неточностей "\
									  "всё можно исправить самому. Также можно писать и свои уроки. Не стесняйтесь добавлять их в репозиторий.<p><hr>"\
									  "Создатель:<br>"\
									  "&nbsp;&nbsp;&nbsp;<i>Ivan Kalinin</i><br>"\
									  "Репозиторий:<br>"\
									  "&nbsp;&nbsp;&nbsp;github.com/Rexagon/kanji-tutor");
		messageBox.setIconPixmap(QPixmap("icon.png"));
		messageBox.setStandardButtons(QMessageBox::Ok);
		messageBox.setDefaultButton(QMessageBox::Ok);
		messageBox.exec();
    });
}
