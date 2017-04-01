#include "kanji.h"

Kanji::Kanji(const QString &symbol) :
    m_symbol(symbol)
{
}


QString Kanji::getSymbol() const
{
    return m_symbol;
}


void Kanji::addKunyomi(const QString &kunyomi)
{
    m_kunyomi.push_back(kunyomi);
}

bool Kanji::hasKunyomi(const QString &kunyomi) const
{
    for (unsigned int i = 0; i < m_kunyomi.size(); ++i) {
        if (m_kunyomi[i] == kunyomi) return true;
    }
    return false;
}

std::vector<QString> Kanji::getKunyomi() const
{
    return m_kunyomi;
}


void Kanji::addOnyomi(const QString &onyomi)
{
    m_onyomi.push_back(onyomi);
}

bool Kanji::hasOnyomi(const QString &onyomi) const
{
    for (unsigned int i = 0; i < m_onyomi.size(); ++i) {
        if (m_onyomi[i] == onyomi) return true;
    }
    return false;
}

std::vector<QString> Kanji::getOnyomi() const
{
    return m_onyomi;
}


void Kanji::addTranslation(const QString &translation)
{
    m_translations.push_back(translation);
}

bool Kanji::hasTranslation(const QString& translation) const
{
    for (unsigned int i = 0; i < m_translations.size(); ++i) {
        if (m_translations[i] == translation) return true;
    }
    return false;
}

std::vector<QString> Kanji::getTranslations()
{
    return m_translations;
}
