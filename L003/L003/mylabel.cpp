#include "mylabel.h"

MyLabel::MyLabel(QWidget * parent):QLabel(parent) {
    this->styleDefault = "min-width:32px;min-height:32px;max-width:32px;max-height:32px;border-radius:16px;border:1px solid black;";
    this->setStyleSheet(this->styleDefault+"background: purple");
    this->styleCurrent=false;
}

void MyLabel::soltLabelStyleSheetUpdate()
{
    if(this->styleCurrent){
        this->setStyleSheet(this->styleDefault+"background:red");
        this->styleCurrent = false;
    }else{
        this->setStyleSheet(this->styleDefault+"background:green");
        this->styleCurrent = true;
    }
}
