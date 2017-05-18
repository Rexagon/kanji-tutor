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

	Exercise(const QString& categoryName, const QString& title, int type, const std::vector<Hieroglyph*> hieroglyphs);

	void restart();
	void update();

	int useHint();
	void answer(const std::vector<QAbstractButton*> options);

	bool isCompleted();

	QString getCategoryName() const;
	QString getTitle() const;
	int getType() const;

	int getTasksNumber() const;

	int getCurrentTaskNumber() const;
	QString getCurrentTask() const;
	std::vector<QString> getCurrentAnswer() const;
	std::vector<QString> getCurrentOptions() const;

	int getMaximumScore() const;
	int getCurrentScore() const;
private:
	void makeKanjiTranslationTask(Hieroglyph* hieroglyph, const std::vector<Hieroglyph*>& otherHieroglyphs);
	void makeTranslationKanjiTask(Hieroglyph* hieroglyph, const std::vector<Hieroglyph*>& otherHieroglyphs);
	void makeKanjiReadingTask(Hieroglyph* hieroglyph, const std::vector<Hieroglyph*>& otherHieroglyphs);

	QString m_categoryName;
	QString m_title;
	int m_type;
	std::vector<Hieroglyph*> m_hieroglyphs;

	int m_currentTaskNumber;
	QString m_currentTask;
	std::vector<QString> m_currentAnswer;
	std::vector<QString> m_currentOptions;

	int m_maximumScore;
	int m_currentScore;

	int m_numHintsUsed;
};

#endif // EXERCISE_H
