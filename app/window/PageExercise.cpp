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
	m_ui->exercisePageOptionsList->setAlignment(Qt::AlignTop);

	connect(m_ui->exercisePageBackButton, &QPushButton::pressed, this, [this]() {
		emit backButtonPressed();
	});

	connect(m_ui->exercisePageNextButton, &QPushButton::pressed, this, [this]() {
		m_ui->exercisePageNextButton->setEnabled(false);

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
					m_currentScore++;
				}
				else {
					m_currentOptions[i]->setStyleSheet("color: red;");
				}
			}
			else if (correct) {
				m_currentOptions[i]->setStyleSheet("color: orange;");
			}
		}

		QTimer::singleShot(1000, this, [this]() {
			if (++m_currentHieroglyph < m_hieroglyphs.size()) {
				updateTask();
			}
			else {
				emit exerciseCompleted(m_currentScore);
			}
		});
	});
}

void PageExercise::setExercise(const QString& title, int type, const std::vector<Hieroglyph*>& hieroglyphs)
{
	m_ui->exercisePageNameLabel->setText(title);

	m_hieroglyphs = hieroglyphs;
	std::random_shuffle(m_hieroglyphs.begin(), m_hieroglyphs.end());

	m_currentHieroglyph = 0;
	m_currentExerciseType = type;
	m_maximumScore = 0;
	m_currentScore = 0;

	switch (m_currentExerciseType) {
	case ExerciseType::KanjiTranslation:
	case ExerciseType::KanjiReading:
		m_ui->exercisePageTaskLabel->setFont(QFont(App::getHieroglyphsFont(), 40, 20));
		break;
	default:
		m_ui->exercisePageTaskLabel->setFont(QFont(App::getDefaultFont(), 24, 20));
		break;
	}

	updateTask();
}

void PageExercise::updateTask()
{
	Hieroglyph*	hieroglyph = m_hieroglyphs[m_currentHieroglyph];

	m_ui->exercisePageProgress->setText(QString::number(m_currentHieroglyph + 1) + "/" +
	                                    QString::number(m_hieroglyphs.size()));

	m_currentTask = "--";
	m_currentAnswer.clear();
	QLayoutItem* item;
	while ((item = m_ui->exercisePageOptionsList->takeAt(0)) != nullptr)
	{
		delete item->widget();
		delete item;
	}

	unsigned int maxAnswersSize = rand() % 2 + 1;
	unsigned int maxOptionsSize = 6;

	std::vector<Hieroglyph*> otherHieroglyphs = m_hieroglyphs;
	otherHieroglyphs.erase(otherHieroglyphs.begin() + m_currentHieroglyph);
	std::random_shuffle(otherHieroglyphs.begin(), otherHieroglyphs.end());

	QFont optionsFont;
	std::vector<QString> options;

	switch (m_currentExerciseType) {
	case ExerciseType::KanjiTranslation:
	{
		// Task
		m_currentTask = hieroglyph->getSymbol();

		// Answer
		m_currentAnswer = hieroglyph->getRandomTranslations(maxAnswersSize);

		// Options
		options = m_currentAnswer;
		for (unsigned int i = 0; i < otherHieroglyphs.size() && options.size() < maxOptionsSize; ++i) {
			std::vector<QString> translations = otherHieroglyphs[i]->getRandomTranslations(1);
			if (translations.size() > 0) {
				options.push_back(translations[0]);
			}
		}
		optionsFont = QFont(App::getDefaultFont(), 12, 10);
	}
		break;
	case ExerciseType::TranslationKanji:
	{
		// Task
		std::vector<QString> translations = hieroglyph->getRandomTranslations(1);
		if (translations.size() > 0) {
			m_currentTask = translations[0];
		}

		// Answer
		m_currentAnswer.push_back(hieroglyph->getSymbol());

		// Options
		options = m_currentAnswer;
		for (unsigned int i = 0; i < otherHieroglyphs.size() && options.size() < maxOptionsSize; ++i) {
			options.push_back(otherHieroglyphs[i]->getSymbol());
		}
		optionsFont = QFont(App::getHieroglyphsFont(), 20, 10);
	}
		break;
	case ExerciseType::KanjiReading:
	{
		// Task
		m_currentTask = hieroglyph->getSymbol();

		// Answer
		maxAnswersSize = 3; // logic change
		std::vector<QString> kunyomi = hieroglyph->getRandomKunyomi(maxAnswersSize / 2);
		std::vector<QString> onyomi = hieroglyph->getRandomOnyomi(maxAnswersSize - maxAnswersSize / 2);

		m_currentAnswer.insert(m_currentAnswer.end(), kunyomi.begin(), kunyomi.end());
		m_currentAnswer.insert(m_currentAnswer.end(), onyomi.begin(), onyomi.end());


		// Options
		options = m_currentAnswer;
		for (unsigned int i = 0; i < otherHieroglyphs.size() && options.size() < maxOptionsSize; ++i) {
			int readingType = rand() % 2;
			kunyomi = otherHieroglyphs[i]->getRandomKunyomi(readingType);
			onyomi = otherHieroglyphs[i]->getRandomOnyomi(1 - readingType);

			options.insert(options.end(), kunyomi.begin(), kunyomi.end());
			options.insert(options.end(), onyomi.begin(), onyomi.end());
		}
		optionsFont = QFont(App::getHieroglyphsFont(), 20, 10);
	}
		break;
	default:
		break;
	}

	// Task
	m_ui->exercisePageTaskLabel->setText(m_currentTask);

	m_maximumScore += m_currentAnswer.size();

	// Options
	m_currentOptions.clear();

	std::random_shuffle(options.begin(), options.end());
	for (unsigned int i = 0; i < options.size(); ++i) {
		switch (m_currentExerciseType) {
		case ExerciseType::TranslationKanji:
			m_currentOptions.push_back(new QRadioButton(options[i]));
			break;
		default:
			m_currentOptions.push_back(new QCheckBox(options[i]));
			break;
		}

		QAbstractButton* optionItem = m_currentOptions.back();
		optionItem->setFont(optionsFont);
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

		connect(optionItem, &QAbstractButton::clicked, this, handleChanging);
	}
}
