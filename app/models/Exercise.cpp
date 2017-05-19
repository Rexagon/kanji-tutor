#include "Exercise.h"

Exercise::Exercise(const QString& categoryName, const QString& title, int type, const std::vector<Hieroglyph*>& hieroglyphs) :
	m_type(type), m_title(title), m_categoryName(categoryName), m_hieroglyphs(hieroglyphs),
	m_currentTaskNumber(-1), m_maximumScore(0), m_currentScore(0), m_numTasksCompleted(0), m_numHintsUsed(0)
{
}

void Exercise::restart()
{
	std::random_shuffle(m_hieroglyphs.begin(), m_hieroglyphs.end());
	m_currentTaskNumber = -1;
	m_maximumScore = 0;
	m_currentScore = 0;
	m_numHintsUsed = 0;
	m_numTasksCompleted = 0;
}

void Exercise::update()
{
	if (isCompleted()) return;
	m_currentTaskNumber++;

	m_currentTask.clear();
	m_currentAnswer.clear();
	m_currentOptions.clear();
}

int Exercise::useHint()
{
	if (m_currentAnswer.size() > 0) {
		for (unsigned int i = 0; i < m_currentOptions.size(); ++i) {
			if (m_currentOptions[i] == m_currentAnswer[0]) {
				m_currentScore--;
				m_numHintsUsed++;
				return i;
			}
		}
	}

	return -1;
}

void Exercise::answer(const std::vector<QAbstractButton*>& options)
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

bool Exercise::isCompleted()
{
	return m_currentTaskNumber >= static_cast<int>(m_hieroglyphs.size()) - 1;
}

QString Exercise::getCategoryName() const
{
	return m_categoryName;
}

QFont Exercise::getTaskFont() const
{
	return m_taskFont;
}

QFont Exercise::getOptionsFont() const
{
	return m_optionsFont;
}

QAbstractButton* Exercise::createOptionItem(const QString& text) const
{
	return nullptr;
}

QString Exercise::getTitle() const
{
	return m_title;
}

QString Exercise::getDescription() const
{
	return m_description;
}

int Exercise::getType() const
{
	return m_type;
}

int Exercise::getNumTaskCompleted() const
{
	return m_numTasksCompleted;
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
