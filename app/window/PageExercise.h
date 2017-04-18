#ifndef PAGEEXERCISE_H
#define PAGEEXERCISE_H

#include <memory>

#include <QAbstractButton>
#include <QTimer>

#include "../widgets/ExerciseListItem.h"
#include "../models/Hieroglyph.h"
#include "PageResults.h"


enum ExerciseType {
	KanjiTranslation,
	TranslationKanji,
	KanjiReading,

	ExercisesNum
};

class PageExercise : public Page
{
	Q_OBJECT
public:
	PageExercise(Ui::MainWindow* ui);

	void setExercise(const QString& title, int type, const std::vector<Hieroglyph*>& hieroglyphs);

	std::unique_ptr<ExerciseListItem> createListItem(Page* page, const QString& categoryName, const QString& title,
													 int type, const std::vector<Hieroglyph*>& hieroglyphs);
signals:
	void backButtonPressed();
	void exerciseCompleted(int percentage);
private:
	void restartExercise();

	void updateTask();

	void makeKanjiTranslationTask(Hieroglyph* hieroglyph, const std::vector<Hieroglyph*>& otherHieroglyphs);
	void makeTranslationKanjiTask(Hieroglyph* hieroglyph, const std::vector<Hieroglyph*>& otherHieroglyphs);
	void makeKanjiReadingTask(Hieroglyph* hieroglyph, const std::vector<Hieroglyph*>& otherHieroglyphs);

	template<class QOptionType>
	void updateOptions(std::vector<QString> options);

	std::vector<Hieroglyph*> m_hieroglyphs;
	int m_currentExerciseType;

	std::vector<QAbstractButton*> m_currentOptions;
	QFont m_currentOptionsFont;

	std::vector<QString> m_currentAnswer;

	unsigned int m_currentHieroglyph;

	int m_numCorrectTasks;
	int m_numHintsUsed;
	int m_maximumScore;
	int m_currentScore;


	std::unique_ptr<PageResults> m_pageResults;
};

#endif // PAGEEXERCISE_H
