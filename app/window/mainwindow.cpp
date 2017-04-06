#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QGridLayout>
#include <QMessageBox>
#include <QJsonArray>
#include <QFile>

#include <cmath>

#include "widgets/lessonlistitem.h"
#include "widgets/kanjilistitem.h"

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
	ui->startPageScrollArea->setLayout(groupsList);

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
				ui->pageSelector->setCurrentIndex(CategoryPage);
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
	ui->categoryPageNameLabel->setText(category->getName());

	connect(ui->categoryPageBackButton, &QPushButton::pressed, this, [this]() {
		ui->pageSelector->setCurrentIndex(StartPage);
	});

	ui->categoryPageLessonsList->clear();

	std::vector<Lesson*> lessons = category->getLessons();

	for (unsigned int i = 0; i < lessons.size(); ++i) {
		Lesson* lesson = lessons[i];

		LessonListItem* widget = new LessonListItem(lesson);

		connect(widget, &LessonListItem::pressed, this, [lesson, this]() {
			createLessonPage(lesson);
			ui->pageSelector->setCurrentIndex(LessonPage);
		});

		QListWidgetItem* item = new QListWidgetItem();
		item->setSizeHint(QSize(0, widget->size().height()));
		item->setFlags(Qt::NoItemFlags);
		ui->categoryPageLessonsList->addItem(item);
		ui->categoryPageLessonsList->setItemWidget(item, widget);
	}
}

void MainWindow::createLessonPage(Lesson* lesson)
{
	ui->lessonPageNameLabel->setText(lesson->getName());

	connect(ui->lessonPageBackButton, &QPushButton::pressed, this, [this]() {
		ui->pageSelector->setCurrentIndex(CategoryPage);
    });

	ui->lessonPageKanjiList->clear();

	std::vector<Hieroglyph*> hieroglyphs = lesson->getHieroglyphs();
    for (unsigned int i = 0; i < hieroglyphs.size(); ++i) {
		Hieroglyph* hieroglyph = hieroglyphs[i];

		KanjiListItem* widget = new KanjiListItem(hieroglyph);

		connect(widget, &KanjiListItem::pressed, this, [this]() {

		});

        QListWidgetItem* item = new QListWidgetItem();
		item->setSizeHint(QSize(0, widget->size().height()));
        item->setFlags(Qt::NoItemFlags);
		ui->lessonPageKanjiList->addItem(item);
		ui->lessonPageKanjiList->setItemWidget(item, widget);
    }
}
