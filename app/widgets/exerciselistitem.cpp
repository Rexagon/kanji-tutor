#include "exerciselistitem.h"

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

ExerciseListItem::ExerciseListItem(const QString& title, const QString& description)
{
	this->setFixedHeight(100);

	QGridLayout* gridLayout = new QGridLayout();
	this->setLayout(gridLayout);

	// Title
	QLabel* labelTitle = new QLabel(title);
	labelTitle->setFont(QFont("Tahoma", 11, 10));
	gridLayout->addWidget(labelTitle, 0, 0, 1, 1);

	// Description
	QLabel* labelDescription = new QLabel(description);
	gridLayout->addWidget(labelDescription, 1, 0, 1, 1);

	// Percentage
	// TODO: get info from lesson or profile
	QLabel* labelPercentage = new QLabel("0%");
	labelPercentage->setAlignment(Qt::AlignRight);
	labelPercentage->setFont(QFont("Tahoma", 16, 10));
	gridLayout->addWidget(labelPercentage, 0, 1, 2, 1);

	// Start button
	QPushButton* buttonStart = new QPushButton("Начать");
	gridLayout->addWidget(buttonStart, 2, 0, 1, 2);

    connect(buttonStart, &QPushButton::pressed, this, [this] {
        emit onStart();
    });

	// Devider
	QFrame* horizontalLine = new QFrame();
	horizontalLine->setFixedHeight(10);
	horizontalLine->setFrameShape(QFrame::HLine);
	horizontalLine->setFrameShadow(QFrame::Sunken);
	gridLayout->addWidget(horizontalLine, 3, 0, 1, 2);
}
