#include "ExerciseKanjiTranslation.h"

#include <QCheckBox>

#include "App.h"

ExerciseKanjiTranslation::ExerciseKanjiTranslation(const QString& categoryName, const QString& title, const std::vector<Hieroglyph*>& hieroglyphs) :
	Exercise(categoryName, title, KanjiTranslation, hieroglyphs)
{
	m_description = "Кандзи/русский перевод";
	m_taskFont = QFont(App::getHieroglyphsFont(), 24, 20);
	m_optionsFont = QFont(App::getDefaultFont(), 12, 10);
}

void ExerciseKanjiTranslation::update()
{
	Exercise::update();

	Hieroglyph* hieroglyph = m_hieroglyphs[m_currentTaskNumber];
	std::vector<Hieroglyph*> otherHieroglyphs = m_hieroglyphs;
	otherHieroglyphs.erase(otherHieroglyphs.begin() + m_currentTaskNumber);
	std::random_shuffle(otherHieroglyphs.begin(), otherHieroglyphs.end());

	unsigned int maxAnswersSize = rand() % 2 + 1;
	unsigned int maxOptionsSize = 6;

	// Task
	m_currentTask = hieroglyph->getSymbol();

	// Answer
	m_currentAnswer = hieroglyph->getRandomTranslations(maxAnswersSize);

	// Options
	m_currentOptions = m_currentAnswer;
	for (unsigned int i = 0; i < otherHieroglyphs.size() && m_currentOptions.size() < maxOptionsSize; ++i) {
		std::vector<QString> translations = otherHieroglyphs[i]->getRandomTranslations(1);
		if (translations.size() > 0) {
			m_currentOptions.push_back(translations[0]);
		}
	}
}

QAbstractButton*ExerciseKanjiTranslation::createOptionItem(const QString& text) const
{
	auto item = new QCheckBox(text);
	item->setFont(m_optionsFont);
	return item;
}

