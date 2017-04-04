#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QGridLayout>
#include <QMessageBox>
#include <QJsonArray>
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadData();

    createMenu();

    createStartPage();
    createCategoryPage();
    createLessonPage();
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

void MainWindow::createCategoryPage()
{
    connect(ui->buttonBack, &QPushButton::pressed, this, [this]() {
        ui->stackedWidget->setCurrentIndex(StartPage);
    });
}

void MainWindow::createLessonPage()
{

}

QPushButton *MainWindow::createCategoryButton(Category* category)
{
    QPushButton* button = new QPushButton(category->getName());

    connect(button, &QPushButton::pressed, this, [category, this]() {
        ui->stackedWidget->setCurrentIndex(CategoryPage);
        ui->labelCategoryName->setText(category->getName());
    });

    button->setFont(QFont("Verdana", 10, 10));
    button->setFixedSize(118, 80);

    return button;
}
