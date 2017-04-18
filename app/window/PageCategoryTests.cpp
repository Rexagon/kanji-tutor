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

	unsigned int hieroglyphsNum = 50;
	std::vector<Hieroglyph*> hieroglyphs;
	std::vector<Lesson*> lessons = category->getLessons();
	for (unsigned int i = 0; i < lessons.size(); ++i) {
		std::vector<Hieroglyph*> lessonHieroglyphs = lessons[i]->getHieroglyphs();
		hieroglyphs.insert(hieroglyphs.end(), lessonHieroglyphs.begin(), lessonHieroglyphs.end());
	}
	std::random_shuffle(hieroglyphs.begin(), hieroglyphs.end());
	if (hieroglyphs.size() > hieroglyphsNum) {
		hieroglyphs.erase(hieroglyphs.begin() + hieroglyphsNum, hieroglyphs.end());
	}

	// Setting events
	for (int i = 0; i < ExerciseType::ExercisesNum; ++i) {
		QString title = category->getName() + ". Тест " + QString::number(i + 1);
		ExerciseListItem* listItem = m_pageExercise->createListItem(this, category->getName(), title, i, hieroglyphs).release();
		m_ui->categoryTestsPageExercisesList->addWidget(listItem);
	}
}
