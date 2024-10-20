#ifndef TAG_H
#define TAG_H
#include <QString>
#include <QString>
class Tag
{
private:
    QString tag;
    QString name;
   // QString template;
public:
    Tag(const QString &tag, const QString &name)
        : tag(tag), name(name) {}
//, template(template)
    //,const QString &template
    QString getTag() const { return tag; }
    QString getName() const { return name; }
   // QString getTemplate() const { return template; }


};


#endif // TAG_H
