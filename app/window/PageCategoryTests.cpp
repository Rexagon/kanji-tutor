#include "PageCategoryTests.h"

#include <ui_mainwindow.h>

#include "../widgets/ExerciseListItem.h"
#include "../models/Lesson.h"

PageCategoryTests::PageCategoryTests(Ui::MainWindow* ui, PageExercise* pageExercise) :
	Page(ui, Id::CategoryTestsPage), m_pageExercise(pageExercise)
{
	m_ui->categoryTestsExercisesContainer->setStyleSheet("\
	QWidget#categoryTestsExercisesContainer { \
		background-color: white;\
		border-top: 1px solid darkGray;\
	}");

	connect(ui->categoryTestsPageBackButton, &QPushButton::pressed, this, [this]() {
		emit backButtonPressed();
	});
}

void PageCategoryTests::setCategory(Category* category)
{
	m_ui->categoryTestsPageNameLabel->setText(category->getName() + ". Тесты");

	QLayoutItem* item;
	while ((item = m_ui->categoryTestsPageExercisesList->takeAt(0)) != nullptr)
	{
		delete item->widget();
		delete item;
	}

	m_ui->categoryTestsPageExercisesList->setAlignment(Qt::AlignTop);

	// Setting events
	std::vector<Exercise*> exercises = category->getExercises();
	for (unsigned int i = 0; i < exercises.size(); ++i) {
		ExerciseListItem* listItem = m_pageExercise->createListItem(this, exercises[i]).release();
		m_ui->categoryTestsPageExercisesList->addWidget(listItem);
	}
}
