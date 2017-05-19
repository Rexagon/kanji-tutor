#include "ExerciseKanjiReading.h"

#include <QCheckBox>

#include "App.h"

ExerciseKanjiReading::ExerciseKanjiReading(const QString& categoryName, const QString& title, const std::vector<Hieroglyph*>& hieroglyphs) :
	Exercise(categoryName, title, KanjiReading, hieroglyphs)
{
	m_description = "Кандзи/чтения";
	m_taskFont = QFont(App::getHieroglyphsFont(), 40, 20);
	m_optionsFont = QFont(App::getHieroglyphsFont(), 20, 10);
}

void ExerciseKanjiReading::update()
{
	Exercise::update();

	Hieroglyph* hieroglyph = m_hieroglyphs[m_currentTaskNumber];
	std::vector<Hieroglyph*> otherHieroglyphs = m_hieroglyphs;
	otherHieroglyphs.erase(otherHieroglyphs.begin() + m_currentTaskNumber);
	std::random_shuffle(otherHieroglyphs.begin(), otherHieroglyphs.end());

	unsigned int maxAnswersSize = 3;
	unsigned int maxOptionsSize = 6;

	// Task
	m_currentTask = hieroglyph->getSymbol();

	// Answer
	std::vector<QString> kunyomi = hieroglyph->getRandomKunyomi(maxAnswersSize / 2);
	std::vector<QString> onyomi = hieroglyph->getRandomOnyomi(maxAnswersSize - maxAnswersSize / 2);

	m_currentAnswer = kunyomi;
	m_currentAnswer.insert(m_currentAnswer.end(), onyomi.begin(), onyomi.end());

	// Options
	m_currentOptions = m_currentAnswer;
	for (unsigned int i = 0; i < otherHieroglyphs.size() && m_currentOptions.size() < maxOptionsSize; ++i) {
		int readingType = rand() % 2;
		kunyomi = otherHieroglyphs[i]->getRandomKunyomi(readingType);
		onyomi = otherHieroglyphs[i]->getRandomOnyomi(1 - readingType);

		m_currentOptions.insert(m_currentOptions.end(), kunyomi.begin(), kunyomi.end());
		m_currentOptions.insert(m_currentOptions.end(), onyomi.begin(), onyomi.end());
	}
}

QAbstractButton* ExerciseKanjiReading::createOptionItem(const QString& text) const
{
	auto item = new QCheckBox(text);
	item->setFont(m_optionsFont);
	return item;
}
