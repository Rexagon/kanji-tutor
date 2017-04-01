#ifndef KANJI_H
#define KANJI_H

#include <vector>
#include <QString>

class Kanji
{
public:
    Kanji(const QString& symbol);

    QString getSymbol() const;

    void addKunyomi(const QString& kunyomi);
    bool hasKunyomi(const QString& kunyomi) const;
    std::vector<QString> getKunyomi() const;

    void addOnyomi(const QString& onyomi);
    bool hasOnyomi(const QString& onyomi) const;
    std::vector<QString> getOnyomi() const;

    void addTranslation(const QString& translation);
    bool hasTranslation(const QString& translation) const;
    std::vector<QString> getTranslations();
private:
    QString m_symbol;

    std::vector<QString> m_kunyomi;
    std::vector<QString> m_onyomi;

    std::vector<QString> m_translations;
};

#endif // KANJI_H
