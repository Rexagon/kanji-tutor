#include "PageLesson.h"

#include <ui_mainwindow.h>

#include "../widgets/ExerciseListItem.h"
#include "../widgets/KanjiListItem.h"
#include "../models/Category.h"

PageLesson::PageLesson(Ui::MainWindow* ui, PageExercise* pageExercise) :
    Page(ui, Id::LessonPage), m_pageExercise(pageExercise)
{
	connect(m_ui->lessonPageBackButton, &QPushButton::pressed, this, [this]() {
		emit backButtonPressed();
	});
}

void PageLesson::setLesson(Lesson* lesson)
{
	m_ui->lessonPageNameLabel->setText(lesson->getName());

	m_ui->lessonPageTabWidget->setCurrentIndex(0);

	updateFirstTab(lesson);
	updateSecondTab(lesson);
	updateThirdTab(lesson);
}

void PageLesson::setListItem(LessonListItem* listItem)
{
	m_listItem = listItem;
}

LessonListItem* PageLesson::getListItem()
{
	return m_listItem;
}

void PageLesson::updateFirstTab(Lesson* lesson)
{
	m_ui->lessonPageKanjiList->clear();
	m_ui->lessonPageKanjiList->scrollToTop();

	std::vector<Hieroglyph*> hieroglyphs = lesson->getHieroglyphs();
	for (unsigned int i = 0; i < hieroglyphs.size(); ++i) {
		Hieroglyph* hieroglyph = hieroglyphs[i];

		KanjiListItem* widget = new KanjiListItem(hieroglyph);

		connect(widget, &KanjiListItem::pressed, this, [this]() {

		});

		QListWidgetItem* item = new QListWidgetItem();
		item->setSizeHint(QSize(0, widget->size().height()));
		m_ui->lessonPageKanjiList->addItem(item);
		m_ui->lessonPageKanjiList->setItemWidget(item, widget);
	}
}

void PageLesson::updateSecondTab(Lesson* lesson)
{
	QLayoutItem* item;
	while ((item = m_ui->lessonPageExercisesList1->takeAt(0)) != nullptr)
	{
		delete item->widget();
		delete item;
	}

	m_ui->lessonPageExercisesList1->setAlignment(Qt::AlignTop);

	// Creating exercise list
	std::vector<Exercise*> exercises = lesson->getExercises();
	for (unsigned int i = 0; i < exercises.size(); ++i) {
		ExerciseListItem* listItem = m_pageExercise->createListItem(this, exercises[i]).release();
		m_ui->lessonPageExercisesList1->addWidget(listItem);
	}
}

void PageLesson::updateThirdTab(Lesson* lesson)
{
	QLayoutItem* item;
	while ((item = m_ui->lessonPageExercisesList2->takeAt(0)) != nullptr)
	{
		delete item->widget();
		delete item;
	}

	m_ui->lessonPageExercisesList2->setAlignment(Qt::AlignTop);

	// Creating revision exercises list
	std::vector<Exercise*> exercises = lesson->getRevisionExercises();
	for (unsigned int i = 0; i < exercises.size(); ++i) {
		ExerciseListItem* listItem = m_pageExercise->createListItem(this, exercises[i]).release();
		m_ui->lessonPageExercisesList2->addWidget(listItem);
	}
}
