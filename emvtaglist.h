#ifndef EMVTAGLIST_H
#define EMVTAGLIST_H

#include <QList>
#include "Tag.h"

class EmvTagList
{
private:
    QList<Tag> emvTagList;
public:
    EmvTagList();
    void initializeTags(); // Tag'leri eklemek için fonksiyon
    QList<Tag> getTags() const;
};

#endif // EMVTAGLIST_H
