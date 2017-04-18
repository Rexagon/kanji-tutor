#include "PageLesson.h"

#include <ui_mainwindow.h>

#include "../widgets/ExerciseListItem.h"
#include "../widgets/KanjiListItem.h"
#include "../models/Category.h"

#include <QDebug>

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

	// Creating hieroglyphs set
	std::vector<Hieroglyph*> hieroglyphs = lesson->getHieroglyphs();

	// Creating exercise list
	for (int i = 0; i < ExerciseType::ExercisesNum; ++i) {
		QString title = lesson->getName() + ". Упражнение " + QString::number(i + 1);
		ExerciseListItem* listItem = m_pageExercise->createListItem(this, title, i, hieroglyphs).release();
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

	// Creating hieroglyphs set
	unsigned int hieroglyphsNum = 25;
	std::vector<Hieroglyph*> hieroglyphs;
	std::vector<Lesson*> lessons = lesson->getCategory()->getLessons();
	for (int i = lesson->getId(); i > -1 && lesson->getId() - i < 4; --i) {
		std::vector<Hieroglyph*> lessonHieroglyphs = lessons[i]->getHieroglyphs();
		hieroglyphs.insert(hieroglyphs.end(), lessonHieroglyphs.begin(), lessonHieroglyphs.end());
	}
	std::random_shuffle(hieroglyphs.begin() + lesson->getHieroglyphsNum(), hieroglyphs.end());
	if (hieroglyphs.size() > hieroglyphsNum) {
		hieroglyphs.erase(hieroglyphs.begin() + hieroglyphsNum, hieroglyphs.end());
	}
	std::random_shuffle(hieroglyphs.begin(), hieroglyphs.end());

	// Creating revision exercises list
	for (int i = 0; i < ExerciseType::ExercisesNum; ++i) {
		QString title = lesson->getName() + ". Повторение " + QString::number(i + 1);
		ExerciseListItem* listItem = m_pageExercise->createListItem(this, title, i, hieroglyphs).release();
		m_ui->lessonPageExercisesList2->addWidget(listItem);
	}
}
