#include "PageCategoryTests.h"

#include <ui_mainwindow.h>

#include "../widgets/ExerciseListItem.h"
#include "../models/Lesson.h"

PageCategoryTests::PageCategoryTests(Ui::MainWindow* ui, PageExercise* pageExercise) :
	Page(ui, Id::CategoryTestsPage), m_pageExercise(pageExercise)
{
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
	ExerciseListItem* firstExercise = new ExerciseListItem("Тест 1", "Кандзи/русский перевод");
	connect(firstExercise, &ExerciseListItem::onStart, this,
			createStartEvent(category->getName() + ". Тест 1",
							 ExerciseType::KanjiTranslation, hieroglyphs));
	m_ui->categoryTestsPageExercisesList->addWidget(firstExercise);

	ExerciseListItem* secondExercise = new ExerciseListItem("Тест 2", "Русский перевод/кандзи");
	connect(secondExercise, &ExerciseListItem::onStart, this,
			createStartEvent(category->getName() + ". Тест 2",
							 ExerciseType::TranslationKanji, hieroglyphs));
	m_ui->categoryTestsPageExercisesList->addWidget(secondExercise);

	ExerciseListItem* thirdExercise = new ExerciseListItem("Тест 3", "Кандзи/чтение");
	connect(thirdExercise, &ExerciseListItem::onStart, this,
			createStartEvent(category->getName() + ". Тест 3",
							 ExerciseType::KanjiReading, hieroglyphs));
	m_ui->categoryTestsPageExercisesList->addWidget(thirdExercise);
}

std::function<void ()> PageCategoryTests::createStartEvent(const QString& title, int type, const std::vector<Hieroglyph*>& hieroglyphs)
{
	return [title, type, hieroglyphs, this]() {
		connect(m_pageExercise, &PageExercise::backButtonPressed, this, [this]() {
			this->setCurrent();
		});
		connect(m_pageExercise, &PageExercise::exerciseCompleted, this, [this](int maximumScore, int score) {
			this->setCurrent();
		});
		m_pageExercise->setExercise(title, type, hieroglyphs);
		m_pageExercise->setCurrent();
	};
}
