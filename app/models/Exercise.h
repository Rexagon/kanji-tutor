#ifndef EXERCISE_H
#define EXERCISE_H

#include "Hieroglyph.h"

#include <QAbstractButton>

class Exercise
{
public:
	enum Type {
		KanjiTranslation,
		TranslationKanji,
		KanjiReading,

		ExercisesNum
	};

	Exercise(const QString& categoryName, const QString& title, int type, const std::vector<Hieroglyph*>& hieroglyphs);
	virtual ~Exercise() {}

	void restart();
	virtual void update();

	int useHint();
	void answer(const std::vector<QAbstractButton*>& options);

	bool isCompleted();

	int getType() const;
	QString getTitle() const;
	QString getDescription() const;
	QString getCategoryName() const;

	QFont getTaskFont() const;
	QFont getOptionsFont() const;

	virtual QAbstractButton* createOptionItem(const QString& text) const;

	int getNumTasksCompleted() const;
	int getNumTasks() const;

	int getCurrentTaskNumber() const;
	QString getCurrentTask() const;
	std::vector<QString> getCurrentAnswer() const;
	std::vector<QString> getCurrentOptions() const;

	int getNumHintsUsed() const;
	int getMaximumScore() const;
	int getCurrentScore() const;
	int getPercentage() const;

	int getSavedPercentage() const;
protected:
	int m_type;
	QString m_title;
	QString m_description;
	QString m_categoryName;
	std::vector<Hieroglyph*> m_hieroglyphs;

	QFont m_taskFont;
	QFont m_optionsFont;

	int m_currentTaskNumber;
	QString m_currentTask;
	std::vector<QString> m_currentAnswer;
	std::vector<QString> m_currentOptions;

	int m_maximumScore;
	int m_currentScore;
	int m_numTasksCompleted;
	int m_numHintsUsed;
};

#endif // EXERCISE_H
