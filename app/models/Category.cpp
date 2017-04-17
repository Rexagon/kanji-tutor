#include "Category.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

#include "Group.h"

Category::Category(const QString& path, Group* group) :
	m_group(group)
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
}

Category::~Category()
{
	m_lessons.clear();
}

Group*Category::getGroup() const
{
	return m_group;
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
