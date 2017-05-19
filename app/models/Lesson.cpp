#include "Lesson.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

#include "ExerciseKanjiTranslation.h"
#include "ExerciseTranslationKanji.h"
#include "ExerciseKanjiReading.h"
#include "Category.h"

Lesson::Lesson(const QString &path, Category* category, int id) :
	m_category(category), m_id(id)
{
    QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
		throw QString("Невозможно открыть урок \"" + path + "\"");
    }

    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();

    m_name = json["name"].toString();

    QJsonArray kanji = json["kanji"].toArray();
    for (int i = 0; i < kanji.size(); ++i) {
		m_hieroglyphs.push_back(std::make_unique<Hieroglyph>(kanji[i].toObject(), this));
    }

	// Creating exercises
	std::vector<Hieroglyph*> hieroglyphs = getHieroglyphs();

	QString title = m_name + ". Упражнение " + QString::number(1);
	m_exercises.push_back(std::make_unique<ExerciseKanjiTranslation>(m_category->getName(), title, hieroglyphs));

	title = m_name + ". Упражнение " + QString::number(2);
	m_exercises.push_back(std::make_unique<ExerciseTranslationKanji>(m_category->getName(), title, hieroglyphs));

	title = m_name + ". Упражнение " + QString::number(3);
	m_exercises.push_back(std::make_unique<ExerciseKanjiReading>(m_category->getName(), title, hieroglyphs));

	// Creating revision exercises
	unsigned int hieroglyphsNum = 25;
	std::vector<Lesson*> lessons = m_category->getLessons();
	for (int i = m_id - 1; i > -1 && m_id - 1 - i < 4; --i) {
		std::vector<Hieroglyph*> lessonHieroglyphs = lessons[i]->getHieroglyphs();
		hieroglyphs.insert(hieroglyphs.end(), lessonHieroglyphs.begin(), lessonHieroglyphs.end());
	}
	std::random_shuffle(hieroglyphs.begin() + m_hieroglyphs.size(), hieroglyphs.end());
	if (hieroglyphs.size() > hieroglyphsNum) {
		hieroglyphs.erase(hieroglyphs.begin() + hieroglyphsNum, hieroglyphs.end());
	}
	std::random_shuffle(hieroglyphs.begin(), hieroglyphs.end());

	title = m_name + ". Повторение " + QString::number(1);
	m_revisionExercises.push_back(std::make_unique<ExerciseKanjiTranslation>(m_category->getName(), title, hieroglyphs));

	title = m_name + ". Повторение " + QString::number(2);
	m_revisionExercises.push_back(std::make_unique<ExerciseTranslationKanji>(m_category->getName(), title, hieroglyphs));

	title = m_name + ". Повторение " + QString::number(3);
	m_revisionExercises.push_back(std::make_unique<ExerciseKanjiReading>(m_category->getName(), title, hieroglyphs));

}

Lesson::~Lesson()
{
    m_hieroglyphs.clear();
}

QString Lesson::getName() const
{
	return m_name;
}

Category*Lesson::getCategory() const
{
	return m_category;
}

int Lesson::getId() const
{
	return m_id;
}

std::vector<Hieroglyph*> Lesson::getHieroglyphs() const
{
    std::vector<Hieroglyph*> result(m_hieroglyphs.size());
    for (unsigned int i = 0; i < m_hieroglyphs.size(); ++i) {
        result[i] = m_hieroglyphs[i].get();
    }
	return result;
}

unsigned int Lesson::getNumHieroglyphs() const
{
	return m_hieroglyphs.size();
}

std::vector<Exercise*> Lesson::getExercises() const
{
	std::vector<Exercise*> result(m_exercises.size());
	for (unsigned int i = 0; i < m_exercises.size(); ++i) {
		result[i] = m_exercises[i].get();
	}
	return result;
}

std::vector<Exercise*> Lesson::getRevisionExercises() const
{
	std::vector<Exercise*> result(m_revisionExercises.size());
	for (unsigned int i = 0; i < m_revisionExercises.size(); ++i) {
		result[i] = m_revisionExercises[i].get();
	}
	return result;
}
