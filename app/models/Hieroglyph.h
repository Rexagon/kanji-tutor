#ifndef KANJI_H
#define KANJI_H

#include <vector>

#include <QStringList>
#include <QJsonObject>
#include <QString>

class Lesson;

class Hieroglyph
{
public:
	Hieroglyph(const QJsonObject& json, Lesson* lesson = nullptr, int id = -1);

	Lesson* getLesson() const;
	int getId() const;

    QString getSymbol() const;

    void addOnyomi(const QString& onyomi);
    bool hasOnyomi(const QString& onyomi) const;
	std::vector<QString> getOnyomi() const;
	std::vector<QString> getRandomOnyomi(unsigned int size) const;
	unsigned int getOnyomiNum() const;

    void addKunyomi(const QString& kunyomi);
    bool hasKunyomi(const QString& kunyomi) const;
	std::vector<QString> getKunyomi() const;
	std::vector<QString> getRandomKunyomi(unsigned int size) const;
	unsigned int getKunyomiNum() const;

    void addTranslation(const QString& translation);
    bool hasTranslation(const QString& translation) const;
	std::vector<QString> getTranslations() const;
	std::vector<QString> getRandomTranslations(unsigned int size) const;
	unsigned int getTranslationsNum() const;
private:
	Lesson* m_lesson;
	int m_id;

    QString m_symbol;
	std::vector<QString> m_kunyomi;
	std::vector<QString> m_onyomi;
	std::vector<QString> m_translations;
};

#endif // KANJI_H
