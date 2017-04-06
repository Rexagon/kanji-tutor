#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QGridLayout>
#include <QMessageBox>
#include <QJsonArray>
#include <QDebug>
#include <QFile>

#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadData();

    createMenu();

	createStartPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadData()
{
    QFile file("data/categories.json");
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Невозможно открыть файл с категориями");
    }

    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();

    QJsonArray groups = json["groups"].toArray();
    for (int i = 0; i < groups.size(); ++i) {
        m_groups.push_back(std::make_unique<Group>(groups[i].toObject()));
    }
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
		messageBox.setText("Kanji tutor");
		messageBox.setInformativeText("Нечто неопределённое, созданные чтобы помочь изучить иероглифы методом простой зубрёжки и тестов.");
		messageBox.setIcon(QMessageBox::Information);
		messageBox.setStandardButtons(QMessageBox::Ok);
		messageBox.setDefaultButton(QMessageBox::Ok);
		messageBox.exec();
    });
}

void MainWindow::createStartPage()
{
	QVBoxLayout* groupsList = new QVBoxLayout();
	groupsList->setAlignment(Qt::AlignTop);
	groupsList->setContentsMargins(0, 12, 0, 0);
	groupsList->setSizeConstraint(QLayout::SetMinimumSize);
	ui->widgetScrollArea->setLayout(groupsList);

	for (unsigned int i = 0; i < m_groups.size(); ++i) {
		Group* group = m_groups[i].get();
		std::vector<Category*> categories = group->getCategories();

		QGridLayout* gridLayout = new QGridLayout();
		gridLayout->setContentsMargins(0,0,16,20);

		for (unsigned int j = 0; j < categories.size(); j++) {
            Category* category = categories[j];
            QPushButton* button = new QPushButton(category->getName());

            connect(button, &QPushButton::pressed, this, [category, this]() {
                createCategoryPage(category);
                ui->stackedWidget->setCurrentIndex(CategoryPage);
            });

            button->setFont(QFont("Verdana", 10, 10));
            button->setFixedSize(118, 80);

            gridLayout->addWidget(button, j / 3, j % 3, 1, 1);
        }

		QWidget* widget = new QWidget(this);
		widget->setLayout(gridLayout);
		widget->setFixedSize(381, static_cast<int>(ceil(categories.size() / 3.0)) * 85 + 20);

		QLabel* title = new QLabel(group->getTitle());
		title->setMargin(0);
		title->setFont(QFont("Verdana", 12, 10));

		groupsList->addWidget(title);
		groupsList->addWidget(widget);
	}
}

void MainWindow::createCategoryPage(Category* category)
{
    ui->labelCategoryName->setText(category->getName());

    connect(ui->buttonBackToStart, &QPushButton::pressed, this, [this]() {
		ui->stackedWidget->setCurrentIndex(StartPage);
	});

	ui->lessonsList->clear();

	std::vector<Lesson*> lessons = category->getLessons();

	for (unsigned int i = 0; i < lessons.size(); ++i) {
		Lesson* lesson = lessons[i];

		QWidget* widget = new QWidget();
		QGridLayout* gridLayout = new QGridLayout();

		QLabel* name = new QLabel(lesson->getName());
		name->setFont(QFont("Verdana", 10, 10));
		gridLayout->addWidget(name, 0, 0, 1, 4);

		QLabel* kanjiList = new QLabel();
		QString kanjiListText;
		std::vector<Kanji*> lessonKanji = lesson->getKanji();
		for (unsigned int j = 0; j < lessonKanji.size(); ++j) {
			kanjiListText += lessonKanji[j]->getSymbol();
		}
		kanjiList->setText(kanjiListText);
		gridLayout->addWidget(kanjiList, 1, 0, 1, 4);

        QPushButton* button = new QPushButton();
        button->setText("Начать");
        button->setFixedHeight(30);
        connect(button, &QPushButton::pressed, this, [lesson, this]() {
            createLessonPage(lesson);
            ui->stackedWidget->setCurrentIndex(LessonPage);
        });

        gridLayout->addWidget(button, 0, 5, 2, 2);

		widget->setLayout(gridLayout);

		QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(QSize(0,50));
        item->setFlags(Qt::NoItemFlags);
		ui->lessonsList->addItem(item);
		ui->lessonsList->setItemWidget(item, widget);

        QFrame* horizontalLine = new QFrame();
        horizontalLine->setFrameShape(QFrame::HLine);

        QListWidgetItem* separator = new QListWidgetItem();
        separator->setSizeHint(QSize(50,1));
        separator->setFlags(Qt::NoItemFlags);
        ui->lessonsList->addItem(separator);
        ui->lessonsList->setItemWidget(separator, horizontalLine);
	}
}

void MainWindow::createLessonPage(Lesson* lesson)
{
    ui->labelLessonName->setText(lesson->getName());

    connect(ui->buttonBackToCategory, &QPushButton::pressed, this, [this]() {
        ui->stackedWidget->setCurrentIndex(CategoryPage);
    });

    ui->kanjiList->clear();

    std::vector<Kanji*> hieroglyphs = lesson->getKanji();
    for (unsigned int i = 0; i < hieroglyphs.size(); ++i) {
        Kanji* kanji = hieroglyphs[i];

        QWidget* widget = new QWidget();
        QGridLayout* gridLayout = new QGridLayout();


        QLabel* symbol = new QLabel(kanji->getSymbol());
        symbol->setFont(QFont("Tahoma", 30, 20));
        gridLayout->addWidget(symbol, 0, 0, 3, 2);

        QLabel* translation = new QLabel(kanji->getTranslations()[0]);
        translation->setFont(QFont("Tahoma", 10, 10));
        gridLayout->addWidget(translation, 4, 0, 1, 2);

        QLabel* onyomi = new QLabel(kanji->getOnyomi()[0]);
        gridLayout->addWidget(onyomi, 0, 3, 2, 3);

        QLabel* kunyomi = new QLabel(kanji->getKunyomi()[0]);
        gridLayout->addWidget(kunyomi, 3, 3, 2, 3);

        widget->setLayout(gridLayout);

        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(QSize(0,80));
        item->setFlags(Qt::NoItemFlags);
        ui->kanjiList->addItem(item);
        ui->kanjiList->setItemWidget(item, widget);

        QFrame* horizontalLine = new QFrame();
        horizontalLine->setFrameShape(QFrame::HLine);

        QListWidgetItem* separator = new QListWidgetItem();
        separator->setSizeHint(QSize(50,1));
        separator->setFlags(Qt::NoItemFlags);
        ui->kanjiList->addItem(separator);
        ui->kanjiList->setItemWidget(separator, horizontalLine);
    }
}
