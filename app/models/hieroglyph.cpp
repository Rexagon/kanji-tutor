#include "hieroglyph.h"

#include <QJsonArray>

Hieroglyph::Hieroglyph(const QJsonObject &json)
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

Hieroglyph::Hieroglyph(const QString &symbol) :
    m_symbol(symbol)
{
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

std::vector<QString> Hieroglyph::getTranslations()
{
    return m_translations;
}
