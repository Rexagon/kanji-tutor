#include "PageExercise.h"

#include <cmath>

#include <ui_mainwindow.h>

#include <QRadioButton>
#include <QCheckBox>
#include <QTimer>

#include "PageLesson.h"
#include "../App.h"

using namespace std::chrono_literals;

PageExercise::PageExercise(Ui::MainWindow* ui) :
	Page(ui, Id::ExercisePage), m_exercise(nullptr)
{
	m_pageResults = std::make_unique<PageResults>(m_ui);

	m_ui->exercisePageOptionsList->setAlignment(Qt::AlignTop);

	connect(m_ui->exercisePageBackButton, &QPushButton::pressed, this, [this]() {
		emit backButtonPressed();
	});

	connect(m_ui->exercisePageHintButton, &QPushButton::pressed, this, [this]() {
		if (m_exercise != nullptr) {
			int answer = m_exercise->useHint();
			if (answer > -1) {
				m_currentOptions[answer]->setChecked(true);
				m_currentOptions[answer]->setEnabled(false);
				m_ui->exercisePageHintButton->setEnabled(false);
			}
		}
	});

	connect(m_ui->exercisePageNextButton, &QPushButton::pressed, this, [this]() {
		m_ui->exercisePageNextButton->setEnabled(false);

		m_exercise->answer(m_currentOptions);

		QTimer::singleShot(1000, this, [this]() {
			if (m_exercise->isCompleted()) {
				m_pageResults->setResult(m_ui->exercisePageNameLabel->text(),
										 m_exercise->getPercentage(),
										 m_exercise->getNumTasks(), m_exercise->getNumTasksCompleted(),
										 m_exercise->getNumHintsUsed());

				m_pageResults->setCurrent();
			}
			else {
				updateTask();
			}
		});
	});

	connect(m_pageResults.get(), &PageResults::restartButtonPressed, this, [this]() {
		m_exercise->restart();
		updateTask();
		this->setCurrent();
	});

	connect(m_pageResults.get(), &PageResults::backButtonPressed, this, [this]() {
		emit exerciseCompleted(m_exercise->getPercentage());
	});
}

void PageExercise::setExercise(Exercise* exercise)
{
	if (exercise == nullptr) return;

	m_exercise = exercise;

	m_ui->exercisePageNameLabel->setText(m_exercise->getTitle());
	m_ui->exercisePageTaskLabel->setFont(m_exercise->getTaskFont());

	m_exercise->restart();
	updateTask();
}

std::unique_ptr<ExerciseListItem> PageExercise::createListItem(Page* page, Exercise* exercise)
{
	if (exercise == nullptr) return nullptr;

	std::unique_ptr<ExerciseListItem> listItem = std::make_unique<ExerciseListItem>(exercise->getTitle(), exercise->getDescription());
	listItem->setPercentage(App::getTaskResult(exercise->getCategoryName(), exercise->getTitle()));
	ExerciseListItem* listItemPtr = listItem.get();
	connect(listItemPtr, &ExerciseListItem::onStart, this, [exercise, page, listItemPtr, this]() {
		disconnect(this, &PageExercise::backButtonPressed, 0, 0);
		connect(this, &PageExercise::backButtonPressed, this, [page]() {
			page->setCurrent();
		});

		disconnect(this, &PageExercise::exerciseCompleted, 0, 0);
		connect(this, &PageExercise::exerciseCompleted, this, [page, exercise, listItemPtr](int percentage) {
			App::setTaskResult(exercise->getCategoryName(), exercise->getTitle(), percentage);
			listItemPtr->setPercentage(percentage);

			if (page->getId() == Page::LessonPage) {
				LessonListItem* lessonListItem = dynamic_cast<PageLesson*>(page)->getListItem();
				if (lessonListItem != nullptr) {
					lessonListItem->updatePercentage();
				}
			}

			page->setCurrent();
		});

		setExercise(exercise);
		setCurrent();
	});

	return std::move(listItem);
}

void PageExercise::updateTask()
{
	m_exercise->update();
	m_ui->exercisePageProgress->setText(QString::number(m_exercise->getCurrentTaskNumber() + 1) + "/" +
										QString::number(m_exercise->getNumTasks()));
	m_ui->exercisePageHintButton->setEnabled(true);
	m_ui->exercisePageTaskLabel->setText(m_exercise->getCurrentTask());

	updateOptions();
}

void PageExercise::updateOptions()
{
	QLayoutItem* item;
	while ((item = m_ui->exercisePageOptionsList->takeAt(0)) != nullptr)
	{
		delete item->widget();
		delete item;
	}
	m_currentOptions.clear();

	std::vector<QString> options = m_exercise->getCurrentOptions();

	for (unsigned int i = 0; i < options.size(); ++i) {
		QAbstractButton* optionItem = m_exercise->createOptionItem(options[i]);
		m_currentOptions.push_back(optionItem);
		m_ui->exercisePageOptionsList->addWidget(optionItem);

		auto handleChanging = [this](bool checked) {
			if (checked) {
				m_ui->exercisePageNextButton->setEnabled(true);
			}
			else {
				for (unsigned int j = 0; j < m_currentOptions.size(); ++j) {
					if (m_currentOptions[j]->isChecked()) {
						return;
					}
				}
				m_ui->exercisePageNextButton->setEnabled(false);
			}
		};

		connect(optionItem, &QAbstractButton::toggled, this, handleChanging);
	}
}
