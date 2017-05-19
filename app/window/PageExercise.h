#ifndef PAGEEXERCISE_H
#define PAGEEXERCISE_H

#include <memory>

#include <QAbstractButton>
#include <QTimer>

#include "../widgets/ExerciseListItem.h"
#include "../models/Exercise.h"
#include "PageResults.h"

class PageExercise : public Page
{
	Q_OBJECT
public:
	PageExercise(Ui::MainWindow* ui);

	std::unique_ptr<ExerciseListItem> createListItem(Page* page, Exercise* exercise);
signals:
	void backButtonPressed();
	void exerciseCompleted(int percentage);
private:
	void setExercise(Exercise* exercise);

	void updateTask();
	void updateOptions();

	Exercise* m_exercise;

	ExerciseListItem* m_itemToUpdate;

	std::unique_ptr<PageResults> m_pageResults;
	std::vector<QAbstractButton*> m_currentOptions;
};

#endif // PAGEEXERCISE_H
