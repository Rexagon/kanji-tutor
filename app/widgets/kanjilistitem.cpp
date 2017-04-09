#include "kanjilistitem.h"

#include <QGridLayout>
#include <QLabel>

KanjiListItem::KanjiListItem(Hieroglyph* hieroglyph, QWidget *parent) : QPushButton(parent)
{
	this->setFixedHeight(99);
	this->setCursor(QCursor(Qt::PointingHandCursor));
	this->setStyleSheet("\
	QPushButton {\
		border: none;\
		border-bottom: 1px solid gray;\
		background: white;\
	}\
	QPushButton:hover {\
		background: #c7ffad;\
		border-bottom: 2px solid gray;\
	}");

	QGridLayout* gridLayout = new QGridLayout();
	this->setLayout(gridLayout);

	// Hieroglyph symbol
	QLabel* labelSymbol = new QLabel(hieroglyph->getSymbol());
	labelSymbol->setFont(QFont("Tahoma", 30, 20));
	gridLayout->addWidget(labelSymbol, 0, 0, 3, 1);

	// Translations
	QString translations = "Перевод: ";
	std::vector<QString> hieroglyphTranslations = hieroglyph->getTranslations();
	for (unsigned int i = 0; i < hieroglyphTranslations.size(); ++i) {
		translations += hieroglyphTranslations[i];
		if (i != hieroglyphTranslations.size() - 1) {
			translations += ", ";
		}
	}
	QLabel* labelTranslations = new QLabel(translations);
	labelTranslations->setFont(QFont("Tahoma", 10, 10));
	gridLayout->addWidget(labelTranslations, 4, 0, 1, 7);


	// Readings font
	QFont font("Tahoma", 12, 50);

	// Onyuomi
	QString onyomi = "Он: ";
	std::vector<QString> hieroglyphOnyomi = hieroglyph->getOnyomi();
	for (unsigned int i = 0; i < hieroglyphOnyomi.size(); ++i) {
		onyomi += hieroglyphOnyomi[i];
		if (i != hieroglyphOnyomi.size() - 1) {
			onyomi.push_back(", ");
		}
	}
	QLabel* labelOnyomi = new QLabel(onyomi);
	labelOnyomi->setFont(font);
	gridLayout->addWidget(labelOnyomi, 0, 3, 2, 4);

	// Kunyomi
	QString kunyomi = "Кун: ";
	std::vector<QString> hieroglyphKunyomi = hieroglyph->getKunyomi();
	for (unsigned int i = 0; i < hieroglyphKunyomi.size(); ++i) {
		kunyomi += hieroglyphKunyomi[i];
		if (i != hieroglyphKunyomi.size() - 1) {
			kunyomi.push_back(", ");
		}
	}
	QLabel* labelKunyomi = new QLabel(kunyomi);
	labelKunyomi->setFont(font);
	gridLayout->addWidget(labelKunyomi, 2, 3, 2, 4);
}
