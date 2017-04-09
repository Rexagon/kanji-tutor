#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QGridLayout>
#include <QMessageBox>
#include <QJsonArray>
#include <QPixmap>
#include <QDebug>
#include <QFile>

#include <cmath>

#include "widgets/exerciselistitem.h"
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
		throw QString("Невозможно открыть файл с категориями");
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
		messageBox.setText("<h3><b>Kanji tutor</b> <small>v1.01</small></h3>");
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

			connect(button, &QPushButton::pressed, this, [this, category]() {
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

	connect(ui->categoryPageKanjiButton, &QPushButton::pressed, this, [this, category]() {
		createCategoryKanjiPage(category);
		ui->pageSelector->setCurrentIndex(CategoryKanjiPage);
	});

	connect(ui->categoryPageTestsButton, &QPushButton::pressed, this, [this, category]() {
		connect(ui->categoryTestsPageBackButton, &QPushButton::pressed, this, [this]() {
			ui->pageSelector->setCurrentIndex(CategoryPage);
		});

		//TODO: REWRITE IT!!!
		QLayoutItem* item;
		while ((item = ui->categoryTestsPageExercisesList->takeAt(0)) != NULL)
		{
			delete item->widget();
			delete item;
		}

		ui->categoryTestsPageExercisesList->setAlignment(Qt::AlignTop);

		ExerciseListItem* firstExercise = new ExerciseListItem("Упражнение 1", "Кандзи/русский перевод");
		ui->categoryTestsPageExercisesList->addWidget(firstExercise);

		ExerciseListItem* secondExercise = new ExerciseListItem("Упражнение 2", "Русский перевод/кандзи");
		ui->categoryTestsPageExercisesList->addWidget(secondExercise);

		ExerciseListItem* thirdExercise = new ExerciseListItem("Упражнение 3", "Кандзи/чтение");
		ui->categoryTestsPageExercisesList->addWidget(thirdExercise);
		ui->pageSelector->setCurrentIndex(CategoryTestsPage);
	});

	ui->categoryPageLessonsList->clear();

	std::vector<Lesson*> lessons = category->getLessons();

	for (unsigned int i = 0; i < lessons.size(); ++i) {
		Lesson* lesson = lessons[i];

		LessonListItem* widget = new LessonListItem(lesson);

		connect(widget, &LessonListItem::pressed, this, [this, lesson]() {
			createLessonPage(lesson);
			ui->pageSelector->setCurrentIndex(LessonPage);
		});

		QListWidgetItem* itemWidget = new QListWidgetItem();
		itemWidget->setSizeHint(QSize(0, widget->size().height()));
		ui->categoryPageLessonsList->addItem(itemWidget);
		ui->categoryPageLessonsList->setItemWidget(itemWidget, widget);
	}
}

void MainWindow::createLessonPage(Lesson* lesson)
{
	ui->lessonPageNameLabel->setText(lesson->getName());

	connect(ui->lessonPageBackButton, &QPushButton::pressed, this, [this]() {
		ui->pageSelector->setCurrentIndex(CategoryPage);
    });

	ui->lessonPageTabWidget->setCurrentIndex(0);

	// First tab
	ui->lessonPageKanjiList->clear();
	ui->lessonPageKanjiList->scrollToTop();

	std::vector<Hieroglyph*> hieroglyphs = lesson->getHieroglyphs();
    for (unsigned int i = 0; i < hieroglyphs.size(); ++i) {
		Hieroglyph* hieroglyph = hieroglyphs[i];

		KanjiListItem* widget = new KanjiListItem(hieroglyph);

		connect(widget, &KanjiListItem::pressed, this, [this]() {

		});

        QListWidgetItem* item = new QListWidgetItem();
		item->setSizeHint(QSize(0, widget->size().height()));
		ui->lessonPageKanjiList->addItem(item);
		ui->lessonPageKanjiList->setItemWidget(item, widget);
	}

	// Second tab
	//TODO: rewrite it
	QLayoutItem* item;
	while ((item = ui->lessonPageExercisesList->takeAt(0)) != NULL)
	{
		delete item->widget();
		delete item;
	}

	ui->lessonPageExercisesList->setAlignment(Qt::AlignTop);

	ExerciseListItem* firstExercise = new ExerciseListItem("Упражнение 1", "Кандзи/русский перевод");
	ui->lessonPageExercisesList->addWidget(firstExercise);

	ExerciseListItem* secondExercise = new ExerciseListItem("Упражнение 2", "Русский перевод/кандзи");
	ui->lessonPageExercisesList->addWidget(secondExercise);

	ExerciseListItem* thirdExercise = new ExerciseListItem("Упражнение 3", "Кандзи/чтение");
	ui->lessonPageExercisesList->addWidget(thirdExercise);
}

void MainWindow::createCategoryKanjiPage(Category* category)
{
	ui->categoryKanjiPageNameLabel->setText(category->getName() + ". Иероглифы");

	connect(ui->categoryKanjiPageBackButton, &QPushButton::pressed, this, [this]() {
		ui->pageSelector->setCurrentIndex(CategoryPage);
	});

	ui->categoryKanjiPageKanjiList->clear();
	ui->categoryKanjiPageKanjiList->scrollToTop();

	std::vector<Lesson*> lessons = category->getLessons();
	for (unsigned int i = 0; i < lessons.size(); ++i) {
		Lesson* lesson = lessons[i];

		std::vector<Hieroglyph*> hieroglyphs = lesson->getHieroglyphs();
		for (unsigned int j = 0; j < hieroglyphs.size(); ++j) {
			Hieroglyph* hieroglyph = hieroglyphs[j];

			KanjiListItem* widget = new KanjiListItem(hieroglyph);

			connect(widget, &KanjiListItem::pressed, this, [this]() {

			});

			QListWidgetItem* item = new QListWidgetItem();
			item->setSizeHint(QSize(0, widget->size().height()));
			ui->categoryKanjiPageKanjiList->addItem(item);
			ui->categoryKanjiPageKanjiList->setItemWidget(item, widget);
		}
	}
}
