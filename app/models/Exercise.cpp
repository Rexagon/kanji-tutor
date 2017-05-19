#include "Exercise.h"

Exercise::Exercise(const QString& categoryName, const QString& title, int type, const std::vector<Hieroglyph*> hieroglyphs) :
	m_categoryName(categoryName), m_title(title), m_type(type), m_hieroglyphs(hieroglyphs)
{
}

void Exercise::restart()
{
	std::random_shuffle(m_hieroglyphs.begin(), m_hieroglyphs.end());
	m_currentTaskNumber = -1;
	m_maximumScore = 0;
	m_currentScore = 0;
	m_numHintsUsed = 0;
}

void Exercise::update()
{
	if (isCompleted()) return;
	m_currentTaskNumber++;

	m_currentTask.clear();
	m_currentAnswer.clear();
	m_currentOptions.clear();

	Hieroglyph* hieroglyph = m_hieroglyphs[m_currentTaskNumber];
	std::vector<Hieroglyph*> otherHieroglyphs = m_hieroglyphs;
	otherHieroglyphs.erase(otherHieroglyphs.begin() + m_currentTaskNumber);
	std::random_shuffle(otherHieroglyphs.begin(), otherHieroglyphs.end());

	switch (m_type) {
	case KanjiTranslation:
		makeKanjiTranslationTask(hieroglyph, otherHieroglyphs);
		break;
	case TranslationKanji:
		makeTranslationKanjiTask(hieroglyph, otherHieroglyphs);
		break;
	case KanjiReading:
		makeKanjiReadingTask(hieroglyph, otherHieroglyphs);
		break;
	}
}

int Exercise::useHint()
{
	if (m_currentAnswer.size() > 0) {
		for (unsigned int i = 0; i < m_currentOptions.size(); ++i) {
			if (m_currentOptions[i] == m_currentAnswer[0]) {
				m_numHintsUsed++;
				return i;
			}
		}
	}

	return -1;
}

void Exercise::answer(const std::vector<QAbstractButton*> options)
{
	int score = 0;

	for (unsigned int i = 0; i < options.size(); ++i) {
		options[i]->setEnabled(false);

		bool correct = false;
		for (unsigned int j = 0; j < m_currentAnswer.size(); ++j) {
			if (options[i]->text() == m_currentAnswer[j]) {
				correct = true;
				break;
			}
		}

		if (options[i]->isChecked()) {
			if (correct) {
				score++;
				options[i]->setStyleSheet("color: green;");
			}
			else {
				score--;
				options[i]->setStyleSheet("color: red;");
			}
		}
		else if (correct) {
			options[i]->setStyleSheet("color: orange;");
		}
	}

	if (score > 0) {
		m_currentScore += score;
	}
	m_maximumScore += m_currentAnswer.size();
}

void Exercise::makeKanjiTranslationTask(Hieroglyph* hieroglyph, const std::vector<Hieroglyph*>& otherHieroglyphs)
{
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

void Exercise::makeTranslationKanjiTask(Hieroglyph* hieroglyph, const std::vector<Hieroglyph*>& otherHieroglyphs)
{
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
}

void Exercise::makeKanjiReadingTask(Hieroglyph* hieroglyph, const std::vector<Hieroglyph*>& otherHieroglyphs)
{
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

bool Exercise::isCompleted()
{
	return m_currentTaskNumber >= static_cast<int>(m_hieroglyphs.size()) - 1;
}

QString Exercise::getCategoryName() const
{
	return m_categoryName;
}

QString Exercise::getTitle() const
{
	return m_title;
}

int Exercise::getType() const
{
	return m_type;
}

int Exercise::getTasksNumber() const
{
	return m_hieroglyphs.size();
}

int Exercise::getCurrentTaskNumber() const
{
	return m_currentTaskNumber;
}

QString Exercise::getCurrentTask() const
{
	return m_currentTask;
}

std::vector<QString> Exercise::getCurrentAnswer() const
{
	return m_currentAnswer;
}

std::vector<QString> Exercise::getCurrentOptions() const
{
	return m_currentOptions;
}

int Exercise::getNumHintsUsed() const
{
	return m_numHintsUsed;
}

int Exercise::getMaximumScore() const
{
	return m_maximumScore;
}

int Exercise::getCurrentScore() const
{
	return m_currentScore;
}

int Exercise::getPercentage() const
{
	return std::floor(static_cast<float>(m_currentScore) / static_cast<float>(m_maximumScore) * 100.0f);
}
