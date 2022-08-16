#ifndef MYLABEL_H
#define MYLABEL_H
#include <QLabel>

class MyLabel : public QLabel
{
private:
    bool styleCurrent;//当前状态
    QString styleDefault;//当前默认风格
public:
    MyLabel(QWidget * parent = 0);
    void soltLabelStyleSheetUpdate();
};

#endif // MYLABEL_H
