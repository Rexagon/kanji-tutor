#include "ExerciseListItem.h"

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include "../App.h"

ExerciseListItem::ExerciseListItem(const QString& title, const QString& description)
{
	this->setFixedHeight(100);

	QGridLayout* gridLayout = new QGridLayout();
	this->setLayout(gridLayout);

	// Title
	QLabel* labelTitle = new QLabel(title);
	labelTitle->setFont(QFont(App::getDefaultFont(), 11, 10));
	gridLayout->addWidget(labelTitle, 0, 0, 1, 1);

	// Description
	QLabel* labelDescription = new QLabel(description);
	gridLayout->addWidget(labelDescription, 1, 0, 1, 1);

	// Percentage
	m_labelPercentage = new QLabel("0%");
	m_labelPercentage->setAlignment(Qt::AlignRight);
	m_labelPercentage->setFont(QFont(App::getDefaultFont(), 16, 10));
	gridLayout->addWidget(m_labelPercentage, 0, 1, 2, 1);

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

void ExerciseListItem::setPercentage(int percentage)
{
	m_labelPercentage->setText(QString::number(percentage) + "%");

	if (percentage < 50) {
		m_labelPercentage->setStyleSheet("color: red");
	}
	else if (percentage >= 50 && percentage < 70) {
		m_labelPercentage->setStyleSheet("color: orange");
	}
	else if (percentage >= 70 && percentage < 90) {
		m_labelPercentage->setStyleSheet("color: green");
	}
	else if (percentage >= 90) {
		m_labelPercentage->setStyleSheet("color: blue");
	}
}
