#include "Hieroglyph.h"

#include <QJsonArray>

#include "Group.h"

Hieroglyph::Hieroglyph(const QJsonObject &json, Lesson* lesson) :
	m_lesson(lesson)
{
    m_symbol = json["s"].toString();

    QJsonArray onyomi = json["on"].toArray();
    for (int i = 0; i < onyomi.size(); ++i) {
		m_onyomi.push_back(onyomi[i].toString());
    }

    QJsonArray kunyomi = json["kun"].toArray();
    for (int i = 0; i < kunyomi.size(); ++i) {
        m_kunyomi.push_back(kunyomi[i].toString());
    }

    QJsonArray translations = json["t"].toArray();
    for (int i = 0; i < translations.size(); ++i) {
		m_translations.push_back(translations[i].toString());
    }
}

Lesson* Hieroglyph::getLesson() const
{
	return m_lesson;
}


QString Hieroglyph::getSymbol() const
{
    return m_symbol;
}


void Hieroglyph::addOnyomi(const QString &onyomi)
{
    m_onyomi.push_back(onyomi);
}

bool Hieroglyph::hasOnyomi(const QString &onyomi) const
{
	for (unsigned int i = 0; i < m_onyomi.size(); ++i) {
        if (m_onyomi[i] == onyomi) return true;
    }
    return false;
}

std::vector<QString> Hieroglyph::getOnyomi() const
{
	return m_onyomi;
}

int Hieroglyph::getOnyomiSize() const
{
	return m_onyomi.size();
}

std::vector<QString> Hieroglyph::getRandomOnyomi(unsigned int size) const
{
	if (size != 0) {
		std::vector<QString> result = m_onyomi;
		std::random_shuffle(result.begin(), result.end());

		if (size > result.size()) size = result.size();

		return std::vector<QString>(result.begin(), result.begin() + size);
	} else {
		return std::vector<QString>();
	}
}


void Hieroglyph::addKunyomi(const QString &kunyomi)
{
    m_kunyomi.push_back(kunyomi);
}

bool Hieroglyph::hasKunyomi(const QString &kunyomi) const
{
	for (unsigned int i = 0; i < m_kunyomi.size(); ++i) {
        if (m_kunyomi[i] == kunyomi) return true;
    }
    return false;
}

std::vector<QString> Hieroglyph::getKunyomi() const
{
	return m_kunyomi;
}

std::vector<QString> Hieroglyph::getRandomKunyomi(unsigned int size) const
{
	if (size != 0) {
		std::vector<QString> result = m_kunyomi;
		std::random_shuffle(result.begin(), result.end());

		if (size > result.size()) size = result.size();

		return std::vector<QString>(result.begin(), result.begin() + size);
	} else {
		return std::vector<QString>();
	}
}

int Hieroglyph::getKunyomiSize() const
{
	return m_kunyomi.size();
}


void Hieroglyph::addTranslation(const QString &translation)
{
    m_translations.push_back(translation);
}

bool Hieroglyph::hasTranslation(const QString& translation) const
{
	for (unsigned int i = 0; i < m_translations.size(); ++i) {
        if (m_translations[i] == translation) return true;
    }
    return false;
}

std::vector<QString> Hieroglyph::getTranslations() const
{
	return m_translations;
}

std::vector<QString> Hieroglyph::getRandomTranslations(unsigned int size) const
{
	if (size != 0) {
		std::vector<QString> result = m_translations;
		std::random_shuffle(result.begin(), result.end());

		if (size > result.size()) size = result.size();

		return std::vector<QString>(result.begin(), result.begin() + size);
	} else {
		return std::vector<QString>();
	}
}

int Hieroglyph::getTranslationsSize() const
{
	return m_translations.size();
}

