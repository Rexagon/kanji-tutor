#include "Category.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

#include "ExerciseKanjiTranslation.h"
#include "ExerciseTranslationKanji.h"
#include "ExerciseKanjiReading.h"
#include "Group.h"

Category::Category(const QString& path, Group* group, int id) :
	m_group(group), m_id(id)
{
    QFile file(path);
	if (!file.open(QIODevice::ReadOnly)) {
		throw QString("Невозможно открыть файл \"" + path + "\"");
    }

    QString currentFolder = path.left(path.lastIndexOf('/') + 1);

    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();

    m_name = json["name"].toString();

    QJsonArray lessons = json["lessons"].toArray();
    for (int i = 0; i < lessons.size(); ++i) {
		m_lessons.push_back(std::make_unique<Lesson>(currentFolder + lessons[i].toString(), this, i));
    }

	// Creating exercises
	unsigned int hieroglyphsNum = 50;
	std::vector<Hieroglyph*> hieroglyphs;
	for (unsigned int i = 0; i < m_lessons.size(); ++i) {
		std::vector<Hieroglyph*> lessonHieroglyphs = m_lessons[i]->getHieroglyphs();
		hieroglyphs.insert(hieroglyphs.end(), lessonHieroglyphs.begin(), lessonHieroglyphs.end());
	}
	std::random_shuffle(hieroglyphs.begin(), hieroglyphs.end());
	if (hieroglyphs.size() > hieroglyphsNum) {
		hieroglyphs.erase(hieroglyphs.begin() + hieroglyphsNum, hieroglyphs.end());
	}

	QString title = m_name + ". Тест " + QString::number(1);
	m_exercises.push_back(std::make_unique<ExerciseKanjiTranslation>(m_name, title, hieroglyphs));

	title = m_name + ". Тест " + QString::number(2);
	m_exercises.push_back(std::make_unique<ExerciseTranslationKanji>(m_name, title, hieroglyphs));

	title = m_name + ". Тест " + QString::number(3);
	m_exercises.push_back(std::make_unique<ExerciseKanjiReading>(m_name, title, hieroglyphs));
}

Category::~Category()
{
	m_lessons.clear();
}

Group*Category::getGroup() const
{
	return m_group;
}

int Category::getId() const
{
	return m_id;
}

QString Category::getName() const
{
    return m_name;
}

std::vector<Lesson*> Category::getLessons()
{
    std::vector<Lesson*> result(m_lessons.size());
    for (unsigned int i = 0; i < m_lessons.size(); ++i) {
        result[i] = m_lessons[i].get();
    }
	return result;
}

unsigned int Category::getLessonsNum() const
{
	return m_lessons.size();
}

std::vector<Exercise*> Category::getExercises() const
{
	std::vector<Exercise*> result(m_exercises.size());
	for (unsigned int i = 0; i < m_exercises.size(); ++i) {
		result[i] = m_exercises[i].get();
	}
	return result;
}
