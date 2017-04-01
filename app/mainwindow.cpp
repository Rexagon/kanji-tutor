#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Menu actions
    connect(ui->menuItemExit, &QAction::triggered, this, [this]() {
        this->close();
    });
    connect(ui->menuItemAbout, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "О программе", "Нечто неопределённое, созданные чтобы помочь изучить иероглифы методом простой зубрёжки и тестов.");
    });

    // Elementary
    QGridLayout* elementaryGridLayout = new QGridLayout();

    for (int i = 0; i < 6; i++) {
        elementaryGridLayout->addWidget(createCategoryButton("Кёику", i + 1), i / 3, i % 3, 1, 1);
    }

    ui->widgetElementary->setLayout(elementaryGridLayout);


    // Primary
    QGridLayout* primaryGridLayout = new QGridLayout();

    for (int i = 0; i < 4; i++) {
        primaryGridLayout->addWidget(createCategoryButton("Дзёё", i + 1), i / 3, i % 3, 1, 1);
    }

    ui->widgetPrimary->setLayout(primaryGridLayout);


}

MainWindow::~MainWindow()
{
    delete ui;
}

QPushButton *MainWindow::createCategoryButton(const QString &text, int id)
{
    QPushButton* button = new QPushButton(QString::number(id) + "\n" + text);

    connect(button, &QPushButton::pressed, this, [id, this]() {
        ui->stackedWidget->setCurrentIndex(1);
    });

    button->setFont(QFont("Verdana", 10, 10));
    button->setFixedHeight(80);

    return button;
}
