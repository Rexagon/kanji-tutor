#include "pagecategorytests.h"

#include <ui_mainwindow.h>

#include "../widgets/exerciselistitem.h"

PageCategoryTests::PageCategoryTests(Ui::MainWindow* ui) :
	Page(ui, Id::CategoryTestsPage)
{
	connect(ui->categoryTestsPageBackButton, &QPushButton::pressed, this, [this]() {
		emit backButtonPressed();
	});
}

void PageCategoryTests::setCategory(Category* category)
{
	m_ui->categoryTestsPageNameLabel->setText(category->getName() + ". Тесты");

	QLayoutItem* item;
	while ((item = m_ui->categoryTestsPageExercisesList->takeAt(0)) != NULL)
	{
		delete item->widget();
		delete item;
	}

	m_ui->categoryTestsPageExercisesList->setAlignment(Qt::AlignTop);

	ExerciseListItem* firstExercise = new ExerciseListItem("Тест 1", "Кандзи/русский перевод");
	m_ui->categoryTestsPageExercisesList->addWidget(firstExercise);

	ExerciseListItem* secondExercise = new ExerciseListItem("Тест 2", "Русский перевод/кандзи");
	m_ui->categoryTestsPageExercisesList->addWidget(secondExercise);

	ExerciseListItem* thirdExercise = new ExerciseListItem("Тест 3", "Кандзи/чтение");
	m_ui->categoryTestsPageExercisesList->addWidget(thirdExercise);
}
