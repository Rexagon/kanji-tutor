#ifndef PAGERESULTS_H
#define PAGERESULTS_H

#include "Page.h"

class PageResults : public Page
{
	Q_OBJECT
public:
	PageResults(Ui::MainWindow* ui);

	void setResult(const QString& title, int maxScore, int score, int numTasks, int numCorrectTasks);
signals:
	void backButtonPressed();
	void restartButtonPressed();
};

#endif // PAGERESULTS_H
