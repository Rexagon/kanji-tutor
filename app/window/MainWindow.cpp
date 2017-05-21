#include "MainWindow.h"

#include <ui_mainwindow.h>
#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>

#include "../App.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	m_ui(new Ui::MainWindow)
{
	m_ui->setupUi(this);

	createMenu();

	m_pageStart = std::make_unique<PageStart>(m_ui);
	m_pageCategory = std::make_unique<PageCategory>(m_ui);
	m_pageCategoryKanji = std::make_unique<PageCategoryKanji>(m_ui);

	m_pageExercise = std::make_unique<PageExercise>(m_ui);

	m_pageLesson = std::make_unique<PageLesson>(m_ui, m_pageExercise.get());
	m_pageCategoryTests = std::make_unique<PageCategoryTests>(m_ui, m_pageExercise.get());

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

	connect(m_pageCategory.get(), &PageCategory::lessonSelected, this, [this](LessonListItem* listItem, Lesson* lesson) {
		m_pageLesson->setLesson(lesson);
		m_pageLesson->setListItem(listItem);
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
	delete m_ui;
}

void MainWindow::createMenu()
{
    // File menu
	connect(m_ui->menuItemExit, &QAction::triggered, this, [this]() {
        this->close();
    });

	// Profile menu
	connect(m_ui->menuItemReset, &QAction::triggered, this, [this]() {
		QMessageBox messageBox;
		messageBox.setWindowTitle("Сброс статистики");
		messageBox.setText("Вы действительно хотите удалить все ваши результаты?");
		messageBox.setIcon(QMessageBox::Question);
		messageBox.addButton("Нет", QMessageBox::NoRole);
		QAbstractButton* messageBoxYesButton = messageBox.addButton("Да", QMessageBox::YesRole);
		messageBox.exec();

		if (messageBox.clickedButton() == messageBoxYesButton) {
			App::resetProfile();
			m_pageStart->setCurrent();
		}
	});

	// Kana menu
	m_hiriganaWindow = new QDialog(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
	m_hiriganaWindow->resize(400, 200);
	m_hiriganaWindow->setWindowTitle("Хиригана");
	QString hirigana = "ん    わ   をらりるれろや ゆ よまみむめもはひふへほなにぬねのたちつてとさしすせそかきくけこあいうえお";
	QGridLayout* hiriganaLayout = new QGridLayout();
	m_hiriganaWindow->setLayout(hiriganaLayout);
	for (int i = 0; i < hirigana.size(); i += 5) {
		for (int j = 0; j < 5; ++j) {
			QLabel* label = new QLabel(QString(hirigana[i + j]));
			label->setFont(QFont(App::getKanaFont(), 15, 50));
			hiriganaLayout->addWidget(label, j, i, 1, 1);
		}
	}

	m_katakanaWindow = new QDialog(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
	m_katakanaWindow->resize(400, 200);
	m_katakanaWindow->setWindowTitle("Катакана");
	QString katakana = "ン    ワ   ヲラリルレロヤ ユ ヨマミムメモハヒフヘホナニヌネノタチツテトサシスセソカキクケコアイウエオ";
	QGridLayout* katakanaLayout = new QGridLayout();
	m_katakanaWindow->setLayout(katakanaLayout);
	for (int i = 0; i < katakana.size(); i += 5) {
		for (int j = 0; j < 5; ++j) {
			QLabel* label = new QLabel(QString(katakana[i + j]));
			label->setFont(QFont(App::getKanaFont(), 15, 50));
			katakanaLayout->addWidget(label, j, i, 1, 1);
		}
	}


	connect(m_ui->menuItemHirigana, &QAction::triggered, this, [this]() {
		if (!m_hiriganaWindow->isVisible()) {
			m_hiriganaWindow->show();
		}
	});

	connect(m_ui->menuItemKatakana, &QAction::triggered, this, [this]() {
		if (!m_katakanaWindow->isVisible()) {
			m_katakanaWindow->show();
		}
	});

    // Help menu

	// Updater
	connect(m_ui->menuItemUpdate, &QAction::triggered, this, [this]() {
		QDesktopServices::openUrl(QUrl("https://github.com/Rexagon/kanji-tutor/releases", QUrl::TolerantMode));
	});

	// Information
	connect(m_ui->menuItemAbout, &QAction::triggered, this, [this]() {
		QMessageBox messageBox;
		messageBox.setWindowTitle("О программе");
		messageBox.setText("<h3><b>Kanji tutor</b> <small>v" + App::getVersion() + "</small></h3>");
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
