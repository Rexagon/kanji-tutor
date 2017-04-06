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
			gridLayout->addWidget(createCategoryButton(categories[j]), j / 3, j % 3, 1, 1);
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
	connect(ui->buttonBack, &QPushButton::pressed, this, [this]() {
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

		widget->setLayout(gridLayout);

		QListWidgetItem* item = new QListWidgetItem();
		item->setSizeHint(QSize(0,50));
		item->setFlags(Qt::NoItemFlags);
		ui->lessonsList->addItem(item);
		ui->lessonsList->setItemWidget(item, widget);

		connect(widget, &mousePressEvent, this, [this](QMouseEvent* event) {
			QMessageBox::about(this, "asd", "qwe");
		});

		if (i != lessons.size() - 1) {
			QFrame* horizontalLine = new QFrame();
			horizontalLine->setFrameShape(QFrame::HLine);

			QListWidgetItem* separator = new QListWidgetItem();
			separator->setSizeHint(QSize(50,1));
			separator->setFlags(Qt::NoItemFlags);
			ui->lessonsList->addItem(separator);
			ui->lessonsList->setItemWidget(separator, horizontalLine);
		}
	}
}

void MainWindow::createLessonPage(Lesson* lesson)
{

}

QPushButton *MainWindow::createCategoryButton(Category* category)
{
	QPushButton* button = new QPushButton(category->getName());

	connect(button, &QPushButton::pressed, this, [category, this]() {
		createCategoryPage(category);
        ui->stackedWidget->setCurrentIndex(CategoryPage);
		ui->labelCategoryName->setText(category->getName());
    });

    button->setFont(QFont("Verdana", 10, 10));
	button->setFixedSize(118, 80);

    return button;
}
