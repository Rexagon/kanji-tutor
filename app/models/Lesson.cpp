#include "Lesson.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

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

unsigned int Lesson::getHieroglyphsNum() const
{
	return m_hieroglyphs.size();
}
