#include "PageExercise.h"

#include <ui_mainwindow.h>

#include <QRadioButton>
#include <QCheckBox>
#include <QTimer>

#include "../App.h"

using namespace std::chrono_literals;

PageExercise::PageExercise(Ui::MainWindow* ui) :
    Page(ui, Id::ExercisePage)
{
	m_pageResults = std::make_unique<PageResults>(m_ui);

	m_ui->exercisePageOptionsList->setAlignment(Qt::AlignTop);

	connect(m_ui->exercisePageBackButton, &QPushButton::pressed, this, [this]() {
		emit backButtonPressed();
	});

	connect(m_ui->exercisePageHintButton, &QPushButton::pressed, this, [this]() {
		if (m_currentAnswer.size() > 0) {
			for (unsigned int i = 0; i < m_currentOptions.size(); ++i) {
				if (m_currentOptions[i]->text() == m_currentAnswer[0]) {
					m_currentOptions[i]->setChecked(true);
					m_currentScore--;
					m_numHintsUsed++;
					break;
				}
			}
			m_ui->exercisePageHintButton->setEnabled(false);
		}
	});

	connect(m_ui->exercisePageNextButton, &QPushButton::pressed, this, [this]() {
		m_ui->exercisePageNextButton->setEnabled(false);

		int taskScore = 0;

		for (unsigned int i = 0; i < m_currentOptions.size(); ++i) {
			m_currentOptions[i]->setEnabled(false);

			bool correct = false;
			for (unsigned int j = 0; j < m_currentAnswer.size(); ++j) {
				if (m_currentOptions[i]->text() == m_currentAnswer[j]) {
					correct = true;
					break;
				}
			}

			if (m_currentOptions[i]->isChecked()) {
				if (correct) {
					m_currentOptions[i]->setStyleSheet("color: green;");
					taskScore++;
				}
				else {
					taskScore--;
					m_currentOptions[i]->setStyleSheet("color: red;");
				}
			}
			else if (correct) {
				m_currentOptions[i]->setStyleSheet("color: orange;");
			}
		}

		if (taskScore > 0) {
			m_currentScore += taskScore;
			if (taskScore == m_currentAnswer.size()) {
				m_numCorrectTasks++;
			}
		}

		QTimer::singleShot(1000, this, [this]() {
			if (++m_currentHieroglyph < m_hieroglyphs.size()) {
				updateTask();
			}
			else {
				int percentage = std::floor(static_cast<double>(m_currentScore) / static_cast<double>(m_maximumScore) * 100.0);

				m_pageResults->setResult(m_ui->exercisePageNameLabel->text(),
				                         percentage,
				                         m_hieroglyphs.size(), m_numCorrectTasks,
				                         m_numHintsUsed);

				connect(m_pageResults.get(), &PageResults::restartButtonPressed, this, [this]() {
					restartExercise();
					this->setCurrent();
				});

				connect(m_pageResults.get(), &PageResults::backButtonPressed, this, [percentage, this]() {
					emit exerciseCompleted(percentage);
				});

				m_pageResults->setCurrent();
			}
		});
	});
}

void PageExercise::setExercise(const QString& title, int type, const std::vector<Hieroglyph*>& hieroglyphs)
{
	m_ui->exercisePageNameLabel->setText(title);

	m_currentExerciseType = type;
	m_hieroglyphs = hieroglyphs;

	switch (m_currentExerciseType) {
	case ExerciseType::KanjiTranslation:
	case ExerciseType::KanjiReading:
		m_ui->exercisePageTaskLabel->setFont(QFont(App::getHieroglyphsFont(), 40, 20));
		break;
	default:
		m_ui->exercisePageTaskLabel->setFont(QFont(App::getDefaultFont(), 24, 20));
		break;
	}

	restartExercise();
}

std::unique_ptr<ExerciseListItem> PageExercise::createListItem(Page* page, const QString& title, int type, const std::vector<Hieroglyph*>& hieroglyphs)
{
	QString description;
	switch (type) {
	case ExerciseType::KanjiTranslation:
		description = "Кандзи/русский перевод";
		break;
	case ExerciseType::TranslationKanji:
		description = "Русский перевод/кандзи";
		break;
	case ExerciseType::KanjiReading:
		description = "Кандзи/чтения";
		break;
	}

	std::unique_ptr<ExerciseListItem> listItem = std::make_unique<ExerciseListItem>(title, description);
	ExerciseListItem* listItemPtr = listItem.get();
	connect(listItemPtr, &ExerciseListItem::onStart, this, [listItemPtr, title, type, hieroglyphs, page, this]() {
		connect(this, &PageExercise::backButtonPressed, this, [page]() {
			page->setCurrent();
		});
		connect(this, &PageExercise::exerciseCompleted, this, [listItemPtr, title, page](int percentage) {
			App::setTaskResult(title, percentage);
			listItemPtr->setPercentage(percentage);
			page->setCurrent();
		});
		setExercise(title, type, hieroglyphs);
		setCurrent();
	});

	return std::move(listItem);
}

void PageExercise::restartExercise()
{
	std::random_shuffle(m_hieroglyphs.begin(), m_hieroglyphs.end());
	m_currentHieroglyph = 0;
	m_numCorrectTasks = 0;
	m_maximumScore = 0;
	m_currentScore = 0;
	m_numHintsUsed = 0;
	updateTask();
}

void PageExercise::updateTask()
{
	m_ui->exercisePageProgress->setText(QString::number(m_currentHieroglyph + 1) + "/" +
	                                    QString::number(m_hieroglyphs.size()));

	m_ui->exercisePageHintButton->setEnabled(true);

	Hieroglyph*	hieroglyph = m_hieroglyphs[m_currentHieroglyph];
	std::vector<Hieroglyph*> otherHieroglyphs = m_hieroglyphs;
	otherHieroglyphs.erase(otherHieroglyphs.begin() + m_currentHieroglyph);
	std::random_shuffle(otherHieroglyphs.begin(), otherHieroglyphs.end());

	switch (m_currentExerciseType) {
	case ExerciseType::KanjiTranslation:
		makeKanjiTranslationTask(hieroglyph, otherHieroglyphs);
		break;
	case ExerciseType::TranslationKanji:
		makeTranslationKanjiTask(hieroglyph, otherHieroglyphs);
		break;
	case ExerciseType::KanjiReading:
		makeKanjiReadingTask(hieroglyph, otherHieroglyphs);
		break;
	}

	m_maximumScore += m_currentAnswer.size();
}

void PageExercise::makeKanjiTranslationTask(Hieroglyph* hieroglyph, const std::vector<Hieroglyph*>& otherHieroglyphs)
{
	unsigned int maxAnswersSize = rand() % 2 + 1;
	unsigned int maxOptionsSize = 6;

	// Task
	m_ui->exercisePageTaskLabel->setText(hieroglyph->getSymbol());

	// Answer
	m_currentAnswer = hieroglyph->getRandomTranslations(maxAnswersSize);

	// Options
	std::vector<QString> options = m_currentAnswer;
	for (unsigned int i = 0; i < otherHieroglyphs.size() && options.size() < maxOptionsSize; ++i) {
		std::vector<QString> translations = otherHieroglyphs[i]->getRandomTranslations(1);
		if (translations.size() > 0) {
			options.push_back(translations[0]);
		}
	}

	m_currentOptionsFont = QFont(App::getDefaultFont(), 12, 10);
	updateOptions<QCheckBox>(options);
}

void PageExercise::makeTranslationKanjiTask(Hieroglyph* hieroglyph, const std::vector<Hieroglyph*>& otherHieroglyphs)
{
	unsigned int maxOptionsSize = 6;

	// Task
	std::vector<QString> translations = hieroglyph->getRandomTranslations(1);
	if (translations.size() > 0) {
		m_ui->exercisePageTaskLabel->setText(translations[0]);
	}
	else {
		m_ui->exercisePageTaskLabel->setText("--"); // don't know how to handle
	}

	// Answer
	m_currentAnswer = {hieroglyph->getSymbol()};

	// Options
	std::vector<QString> options = m_currentAnswer;
	for (unsigned int i = 0; i < otherHieroglyphs.size() && options.size() < maxOptionsSize; ++i) {
		options.push_back(otherHieroglyphs[i]->getSymbol());
	}

	m_currentOptionsFont = QFont(App::getHieroglyphsFont(), 20, 10);
	updateOptions<QRadioButton>(options);
}

void PageExercise::makeKanjiReadingTask(Hieroglyph* hieroglyph, const std::vector<Hieroglyph*>& otherHieroglyphs)
{
	unsigned int maxAnswersSize = 3;
	unsigned int maxOptionsSize = 6;

	// Task
	m_ui->exercisePageTaskLabel->setText(hieroglyph->getSymbol());

	// Answer
	std::vector<QString> kunyomi = hieroglyph->getRandomKunyomi(maxAnswersSize / 2);
	std::vector<QString> onyomi = hieroglyph->getRandomOnyomi(maxAnswersSize - maxAnswersSize / 2);

	m_currentAnswer = kunyomi;
	m_currentAnswer.insert(m_currentAnswer.end(), onyomi.begin(), onyomi.end());

	// Options
	std::vector<QString> options = m_currentAnswer;
	for (unsigned int i = 0; i < otherHieroglyphs.size() && options.size() < maxOptionsSize; ++i) {
		int readingType = rand() % 2;
		kunyomi = otherHieroglyphs[i]->getRandomKunyomi(readingType);
		onyomi = otherHieroglyphs[i]->getRandomOnyomi(1 - readingType);

		options.insert(options.end(), kunyomi.begin(), kunyomi.end());
		options.insert(options.end(), onyomi.begin(), onyomi.end());
	}

	m_currentOptionsFont = QFont(App::getHieroglyphsFont(), 20, 10);
	updateOptions<QCheckBox>(options);
}


template<class QOptionType>
void PageExercise::updateOptions(std::vector<QString> options)
{
	QLayoutItem* item;
	while ((item = m_ui->exercisePageOptionsList->takeAt(0)) != nullptr)
	{
		delete item->widget();
		delete item;
	}
	m_currentOptions.clear();
	std::random_shuffle(options.begin(), options.end());
	for (unsigned int i = 0; i < options.size(); ++i) {
		m_currentOptions.push_back(new QOptionType(options[i]));

		QAbstractButton* optionItem = m_currentOptions.back();
		optionItem->setFont(m_currentOptionsFont);
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
