#include "PageResults.h"

#include <ui_mainwindow.h>

#include "../App.h"

PageResults::PageResults(Ui::MainWindow* ui) :
	Page(ui, Id::ResultsPage)
{
	connect(m_ui->resultsPageRestartButton, &QPushButton::pressed, this, [this]() {
		emit restartButtonPressed();
	});

	connect(m_ui->resultsPageBackButton, &QPushButton::pressed, this, [this]() {
		emit backButtonPressed();
	});
}

void PageResults::setResult(const QString& title, int percentage, int numTasks, int numCorrectTasks, int numHintsUsed)
{
	m_ui->resultsPageNameLabel->setText(title);

	if (percentage < 50) {
		m_ui->resultsPageMark->setText("Плохо");
		m_ui->resultsPageMark->setStyleSheet("color: red");
	}
	else if (percentage >= 50 && percentage < 70) {
		m_ui->resultsPageMark->setText("Нормально");
		m_ui->resultsPageMark->setStyleSheet("color: orange");
	}
	else if (percentage >= 70 && percentage < 90) {
		m_ui->resultsPageMark->setText("Хорошо");
		m_ui->resultsPageMark->setStyleSheet("color: green");
	}
	else if (percentage >= 90) {
		m_ui->resultsPageMark->setText("Отлично");
		m_ui->resultsPageMark->setStyleSheet("color: blue");
	}

	m_ui->resultsPagePercentage->setText(QString::number(percentage) + "%");
	m_ui->resultsPageNumHintsUsed->setText(QString::number(numHintsUsed));
	m_ui->resultsPageNumCorrect->setText(QString::number(numCorrectTasks) + " из " + QString::number(numTasks));
}
