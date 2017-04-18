#ifndef KANJILISTITEM_H
#define KANJILISTITEM_H

#include <QPushButton>

#include "../models/Hieroglyph.h"

class KanjiListItem : public QPushButton
{
	Q_OBJECT
public:
	explicit KanjiListItem(Hieroglyph* hieroglyph, QWidget *parent = 0);
};

#endif // KANJILISTITEM_H
