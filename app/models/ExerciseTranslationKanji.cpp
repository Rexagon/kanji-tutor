#include "ExerciseTranslationKanji.h"

#include <QRadioButton>

#include "App.h"

ExerciseTranslationKanji::ExerciseTranslationKanji(const QString& categoryName, const QString& title, const std::vector<Hieroglyph*>& hieroglyphs) :
	Exercise(categoryName, title, TranslationKanji, hieroglyphs)
{
	m_description = "Русский перевод/кандзи";
	m_taskFont = QFont(App::getDefaultFont(), 24, 20);
	m_optionsFont = QFont(App::getHieroglyphsFont(), 20, 10);
}

void ExerciseTranslationKanji::update()
{
	Exercise::update();

	Hieroglyph* hieroglyph = m_hieroglyphs[m_currentTaskNumber];
	std::vector<Hieroglyph*> otherHieroglyphs = m_hieroglyphs;
	otherHieroglyphs.erase(otherHieroglyphs.begin() + m_currentTaskNumber);
	std::random_shuffle(otherHieroglyphs.begin(), otherHieroglyphs.end());

	unsigned int maxOptionsSize = 6;

	// Task
	std::vector<QString> translations = hieroglyph->getRandomTranslations(1);
	if (translations.size() > 0) {
		m_currentTask = translations[0];
	}
	else {
		m_currentTask = "--"; // don't know how to handle
	}

	// Answer
	m_currentAnswer = { hieroglyph->getSymbol() };

	// Options
	m_currentOptions = m_currentAnswer;
	for (unsigned int i = 0; i < otherHieroglyphs.size() && m_currentOptions.size() < maxOptionsSize; ++i) {
		m_currentOptions.push_back(otherHieroglyphs[i]->getSymbol());
	}
	std::random_shuffle(m_currentOptions.begin(), m_currentOptions.end());
}

QAbstractButton*ExerciseTranslationKanji::createOptionItem(const QString& text) const
{
	auto item = new QRadioButton(text);
	item->setFont(m_optionsFont);
	return item;
}
