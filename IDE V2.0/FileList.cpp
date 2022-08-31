#include "FileList.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QTextStream>
#include<QDebug>
#include<QToolTip>
FileList::FileList(QTreeWidget *parent) : QTreeWidget(parent)
{
    // setAttribute(Qt::WA_StyledBackground, true);


    QFont fileListFont("Microsoft YaHei", 10, 50);
    this->setHeaderHidden(true);
    this->setMouseTracking(true);
    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(OnFileChanged(QTreeWidgetItem*,int)));
    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(DoubleClickedItem(QTreeWidgetItem*,int)));
    connect(this,SIGNAL(itemEntered(QTreeWidgetItem*,int)),this,SLOT(ShowPath(QTreeWidgetItem*,int)));
//    this->setStyleSheet(
//                "QListWidget {background-color:rgb(242, 239, 249);outline: 0px;padding: 10px;border: none;border-radius: 20px }"
//                "QListWidget::item {border: none;border-radius: 15px;padding: 10px;color: rgb(93, 93, 94) }"
//                "QListWidget::item:hover {background: rgb(187, 160, 250)}"
//                "QListWidget::item:selected { background: rgb(147, 115, 238);color: white}"
//                );

//    this->verticalScrollBar()->setStyleSheet(
//                "QScrollBar:vertical{background-color:none;width:12px;border-radius:6px}"
//                "QScrollBar::handle:vertical{background:rgb(187, 160, 250);border-radius:6px;min-height:20;}"
//                "QScrollBar::handle:vertical:hover{background:rgb(147, 115, 238);border-radius:6px;min-height:20;}"
//                "QScrollBar::add-line:vertical{height:0px;width:0px;}"
//                "QScrollBar::sub-line:vertical{height:0px;width:0px;}"
//                "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{width:0px;background:rgb(242, 239, 249);}"
//                );
//    this->horizontalScrollBar()->setStyleSheet(
//                "QScrollBar:horizontal{background:none;height:12px;border-radius:6px}"
//                "QScrollBar::handle:horizontal{background:rgb(187, 160, 250);border-radius:6px;min-width:20;}"
//                "QScrollBar::handle:horizontal:hover{background:rgb(147, 115, 238);border-radius:6px;min-width:20;}"
//                "QScrollBar::add-line:horizontal{height:0px;width:0px;}"
//                "QScrollBar::sub-line:horizontal{height:0px;width:0px;}"
//                "QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal{height:0px;background:rgb(242, 239, 249);}"
//                );
    this->setFont(fileListFont);
}

//void FileList::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event);
//    QStyleOption opt;
//    opt.init(this);
//    QPainter p(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//}


bool FileList::MaybeSave(){
    if(!curIsModified)//没有做出修改
        return true;
    //已做出修改，选择是否保存
    const QMessageBox::StandardButton mesgbutton
            =QMessageBox::warning(this,tr("Warning"),tr("Not saved yet"),
                                  QMessageBox::Save|QMessageBox::Cancel);

    switch (mesgbutton) {
    case QMessageBox::Save:
        return Save();//保存
        break;
     case QMessageBox::Cancel://不保存
        return true;
    default:
        break;
    }
    return false;
}
bool FileList::loadFile(const QString &filename){
    QFile file(filename);
    if(!file.open(QFile::ReadOnly|QFile::Text)){//打开文件失败
        QMessageBox::warning(this,tr("Error"),tr("Open File failed"));
        return false;
    }
    QTextStream streamin(&file);
    emit(LoadData(streamin.readAll()));//向编辑区发送从文件中获取的内容
    setCurrentFile(filename);//重置当前文件信息
    return true;
}

bool FileList::OpenFile(){

    if(MaybeSave()){//打开文件前先判断是否保存之前文件内容
        QString path=QFileDialog::getOpenFileName(this,tr("打开文件"),tr(""),tr("C source files(*.c)"));
        if(!path.isEmpty())//已选择文件
            return loadFile(path);
    }
    return false;
}

bool FileList::openStartFile(){

    QString path=QFileDialog::getOpenFileName(this,tr("打开文件"),tr(""),tr("C source files(*.c)"));
    if(!path.isEmpty())//已选择文件
        return loadFile(path);
    return false;
}
bool FileList::Save(){
    if(currentFile.isEmpty()){//新建文件，先另存
        return SaveAs();
    }else{
       return SaveFile(currentFile);
    }
}

bool FileList::SaveFile(const QString &filename){
    QFile file(filename);
    if(!file.open(QFile::WriteOnly|QFile::Text)){//保存失败
        QMessageBox::warning(this,tr("Error"),tr("Save File failed"));
        return false;
    }
    QTextStream out(&file);

    emit(GetText());//从编辑区获取文本

    out<<curPlainText;

    setCurrentFile(filename);//重置当前编辑文件状态
    return true;
}
bool FileList::NewFile(){
    if(MaybeSave()){//新建文件前先保存
        emit(ClearText());//发送清空编辑区信号
        QString path=QFileDialog::getSaveFileName(this,tr("新建文件"),tr(""),tr("C source files(*.c)"));
        if(!path.isEmpty()) return SaveFile(path);

    }
    return false;
}

bool FileList::newStartFile()
{
    emit(ClearText());//发送清空编辑区信号
    QString path=QFileDialog::getSaveFileName(this,tr("新建文件"),tr(""),tr("C source files(*.c)"));
    if(!path.isEmpty())  return SaveFile(path);
    return false;
}

bool FileList::SaveAs(){
//    QFileDialog dialog(this);
//    dialog.setWindowModality(Qt::WindowModal);
//    dialog.setAcceptMode((QFileDialog::AcceptSave));

//    if (dialog.exec() != QDialog::Accepted)
//              return false;
//          return SaveFile(dialog.selectedFiles().first());
       QTreeWidgetItem * curItem;
       if(!currentFile.isEmpty())  curItem=files.value(currentFile);

    QString path=QFileDialog::getSaveFileName(this,tr("另存文件"),tr(""),tr("C source files(*.c)"));
    bool flag;
    if(!path.isEmpty()) {
       flag=SaveFile(path);
    }
    else flag=false;
    if(flag){//未选择另存文件或另存失败
       if(curItem!=NULL){
           QTreeWidgetItem *parentItem=curItem->parent();
        files.remove(files.key(curItem));
        this->removeItemWidget(curItem,1);
        delete curItem;

        int chiladNum=parentItem->childCount();
        if(chiladNum==0){
            dirs.remove(dirs.key(parentItem));
            this->removeItemWidget(parentItem,1);
            delete parentItem;
        }
       }
        return true;
    }
    else return false;

}
void FileList::setCurrentFile(const QString &filename){
    currentFile= filename;
    curIsModified=false;//设置为未修改过

    if(currentFile.isEmpty())
        shownName="未命名";
    else shownName=QFileInfo(currentFile).fileName();
    QString dirPath=QFileInfo(currentFile).absolutePath();
    QString dirName=QFileInfo(dirPath).fileName();
    if(!files.contains(filename)){
        if(!dirs.contains(dirPath)){
            QTreeWidgetItem * dirItem=new QTreeWidgetItem(this);
            dirItem->setText(0,dirName);
            dirs.insert(dirPath,dirItem);
        }
        QTreeWidgetItem * fileItem=new QTreeWidgetItem(dirs.value(dirPath));
        fileItem->setText(0,shownName);
        files.insert(filename,fileItem);
        this->setCurrentItem(fileItem);
    }else{
        QTreeWidgetItem * nowItem=files.value(currentFile);
        this->setCurrentItem(nowItem);
    }
    emit(SetTitle(shownName));
}
bool FileList::OpenDirectory(){
    QString dirPath=QFileDialog::getExistingDirectory();
    if(dirPath.isEmpty()) return false;
    QTreeWidgetItem * dirItem;
    if(!dirs.contains(dirPath)){
        dirItem=new QTreeWidgetItem(this);
        dirItem->setText(0,QFileInfo(dirPath).fileName());
        dirs.insert(dirPath,dirItem);
    }
    QDir dir(dirPath);
    //遍历文件夹
         //列出dir(path)目录文件下所有文件和目录信息，存储到file_list容器
                QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
                //进行筛选
                foreach (QFileInfo fileinfo, fileInfoList)
                {
                   QString filter=fileinfo.suffix();
                    if(filter!="c")
                    {
                         continue;
                     }
                    QString filePath=fileinfo.absoluteFilePath();
                    QString fileName=fileinfo.fileName();
                    if(!files.contains(filePath)){
                        QTreeWidgetItem * fileItem=new QTreeWidgetItem(dirs.value(dirPath));
                        fileItem->setText(0,fileName);
                        files.insert(filePath,fileItem);
                    }

                }
}

void FileList::OnFileChanged(QTreeWidgetItem *Item,int colum){
//    if(files.contains())
    QTreeWidgetItem * preItem;
    if(!currentFile.isEmpty()) {
        preItem=files.value(currentFile);
        //Save();
    }
    QString after=files.key(Item);
    QString dir;

    if(!after.isEmpty()){
        if(!currentFile.isEmpty())Save();
        emit setedit();
        loadFile(after);}
    else {
//      if(!currentFile.isEmpty())  setCurrentItem(preItem,1);
//      dir=dirs.key(Item);
//      if(!dir.isEmpty()){
//          if(Item->isExpanded()) Item->setExpanded(false);
//          else  Item->setExpanded(true);
//      }
    }
}
void FileList::ShowPath(QTreeWidgetItem *item, int column){
    QString path=files.key(item);
    if(path.isEmpty()) path=dirs.key(item);
    if(!path.isEmpty()){
        QToolTip::showText(QCursor::pos(),path);
    }
}

void FileList::DoubleClickedItem(QTreeWidgetItem *Item, int column){

}

void FileList::Close(){//关闭当前文件
    if(MaybeSave()){
        QTreeWidgetItem * curItem=files.value(currentFile);
        files.remove(currentFile);
        QTreeWidgetItem * parentItem=curItem->parent();

        this->removeItemWidget(curItem,1);
        delete curItem;

        int chiladNum=parentItem->childCount();
        if(chiladNum==0){
            dirs.remove(dirs.key(parentItem));
            this->removeItemWidget(parentItem,1);
            delete parentItem;
        }
        if(dirs.size()==0&&files.size()==0){

        }else{
            this->setCurrentItem(files.begin().value());
            loadFile(files.begin().key());
        }

    }
}
void FileList::SetCurrentFilemodified(){//编辑区做出修改
    curIsModified=true;
}
void FileList::GetPlainText(QString Text){//从编辑区收到文本内容
    curPlainText=Text;
}
