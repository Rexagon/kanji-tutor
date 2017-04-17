#include "PageLesson.h"

#include <ui_mainwindow.h>

#include "../widgets/ExerciseListItem.h"
#include "../widgets/KanjiListItem.h"

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

	// First tab
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

	// Second tab
	QLayoutItem* item;
	while ((item = m_ui->lessonPageExercisesList->takeAt(0)) != nullptr)
	{
		delete item->widget();
		delete item;
	}

	m_ui->lessonPageExercisesList->setAlignment(Qt::AlignTop);

	ExerciseListItem* firstExercise = new ExerciseListItem("Упражнение 1", "Кандзи/русский перевод");
	connect(firstExercise, &ExerciseListItem::onStart, this,
	        createStartEvent(lesson->getName() + ". Упражнение 1",
	                         ExerciseType::KanjiTranslation, hieroglyphs));
	m_ui->lessonPageExercisesList->addWidget(firstExercise);

	ExerciseListItem* secondExercise = new ExerciseListItem("Упражнение 2", "Русский перевод/кандзи");
	connect(secondExercise, &ExerciseListItem::onStart, this,
	        createStartEvent(lesson->getName() + ". Упражнение 2",
	                         ExerciseType::TranslationKanji, hieroglyphs));
	m_ui->lessonPageExercisesList->addWidget(secondExercise);

	ExerciseListItem* thirdExercise = new ExerciseListItem("Упражнение 3", "Кандзи/чтение");
	connect(thirdExercise, &ExerciseListItem::onStart, this,
	        createStartEvent(lesson->getName() + ". Упражнение 3",
	                         ExerciseType::KanjiReading, hieroglyphs));
	m_ui->lessonPageExercisesList->addWidget(thirdExercise);

	// Third tab
	while ((item = m_ui->lessonPageExercisesList2->takeAt(0)) != nullptr)
	{
		delete item->widget();
		delete item;
	}

	m_ui->lessonPageExercisesList2->setAlignment(Qt::AlignTop);

	ExerciseListItem* firstRevisionExercise = new ExerciseListItem("Упражнение 1", "Кандзи/русский перевод");
	connect(firstRevisionExercise, &ExerciseListItem::onStart, this, [this]() {
		//m_pageExercise->setExercise(ExerciseType::KanjiTranslation, hieroglyphs);
	});
	m_ui->lessonPageExercisesList2->addWidget(firstRevisionExercise);

	ExerciseListItem* secondRevisionExercise = new ExerciseListItem("Упражнение 2", "Русский перевод/кандзи");
	connect(secondRevisionExercise, &ExerciseListItem::onStart, this, [this]() {

	});
	m_ui->lessonPageExercisesList2->addWidget(secondRevisionExercise);

	ExerciseListItem* thirdRevisionExercise = new ExerciseListItem("Упражнение 3", "Кандзи/чтение");
	connect(thirdRevisionExercise, &ExerciseListItem::onStart, this, [this]() {

	});
	m_ui->lessonPageExercisesList2->addWidget(thirdRevisionExercise);
}

std::function<void ()> PageLesson::createStartEvent(const QString& title, int type, const std::vector<Hieroglyph*>& hieroglyphs)
{
	return [title, type, hieroglyphs, this]() {
		connect(m_pageExercise, &PageExercise::backButtonPressed, this, [this]() {
			this->setCurrent();
		});
		m_pageExercise->setExercise(title, type, hieroglyphs);
		m_pageExercise->setCurrent();
	};
}
