#ifndef PAGERESULTS_H
#define PAGERESULTS_H

#include "Page.h"

class PageResults : public Page
{
	Q_OBJECT
public:
	PageResults(Ui::MainWindow* ui);

	void setResult(const QString& title, int percentage, int numTasks, int numCorrectTasks, int numHintsUsed);
signals:
	void backButtonPressed();
	void restartButtonPressed();
};

#endif // PAGERESULTS_H
