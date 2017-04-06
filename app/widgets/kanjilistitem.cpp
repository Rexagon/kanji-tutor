#include "kanjilistitem.h"

#include <QGridLayout>
#include <QLabel>

KanjiListItem::KanjiListItem(Hieroglyph* hieroglyph, QWidget *parent) : QPushButton(parent)
{
	this->setFixedHeight(100);
	this->setFlat(true);
	this->setCursor(QCursor(Qt::PointingHandCursor));

	QGridLayout* gridLayout = new QGridLayout();
	this->setLayout(gridLayout);

	// Hieroglyph symbol
	QLabel* labelSymbol = new QLabel(hieroglyph->getSymbol());
	labelSymbol->setFont(QFont("Tahoma", 30, 20));
	gridLayout->addWidget(labelSymbol, 0, 0, 3, 2);

	// Translations
	QString translations;
	std::vector<QString> hieroglyphTranslations = hieroglyph->getTranslations();
	for (unsigned int i = 0; i < hieroglyphTranslations.size(); ++i) {
		translations += hieroglyphTranslations[i];
		if (i != hieroglyphTranslations.size() - 1) {
			translations += ", ";
		}
	}
	QLabel* labelTranslations = new QLabel(translations);
	labelTranslations->setFont(QFont("Tahoma", 10, 10));
	gridLayout->addWidget(labelTranslations, 4, 0, 1, 2);


	QFont font("Tahoma", 12, 20);
	// Onyuomi
	QLabel* labelOnyomi = new QLabel("Он: " + hieroglyph->getOnyomi()[0]);
	labelOnyomi->setFont(font);
	gridLayout->addWidget(labelOnyomi, 0, 3, 2, 4);

	QLabel* labelKunyomi = new QLabel("Кун: " + hieroglyph->getKunyomi()[0]);
	labelKunyomi->setFont(font);
	gridLayout->addWidget(labelKunyomi, 2, 3, 2, 4);

	QFrame* horizontalLineWidget = new QFrame();
	horizontalLineWidget->setFrameShape(QFrame::HLine);
	horizontalLineWidget->setFixedHeight(1);
	horizontalLineWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	gridLayout->addWidget(horizontalLineWidget, 5, 0, 1, 8, Qt::AlignBottom);
}
