#include "prinsipal.h"
#include "ui_prinsipal.h"
#include "dialog_save.h"
#include "barraestadisticaestudiantes.h"
#include "stidents.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QSplitter>
#include <QKeyEvent>
#include <QPainter>
#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QDir>

Prinsipal::Prinsipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Prinsipal)
{
    ui->setupUi(this);
    Satr_Table_Student();
    Satr_Table_Notes();

    ui->stackedWidget->setCurrentWidget(ui->page_2);

    connect(ui->actionSave_As,SIGNAL(triggered()),
            this,SLOT(on_cmd_Save_clicked()));
    connect(ui->action_Open_file,SIGNAL(triggered()),
            this,SLOT(on_cmd_Open_clicked()));
    connect(ui->action_Option,SIGNAL(triggered()),
            this,SLOT(on_cmd_PageConfig_clicked()));
    connect(ui->action_New_file,SIGNAL(triggered()),
            this,SLOT(on_cmd_NewFile_clicked()));

    verificationChangeWindows();
    aspect(TITEL);

    lienzo = QPixmap(800,580);
    ui->out_grafic->setPixmap(lienzo);
    initLienzo(200,200);
    //VADY
   // ui->setupUi(this);
    ui->out_grafic->resize(tall+40,width+20);
    pixmap = QPixmap(ui->out_grafic->size());
    Enterokay(width,10);
    coordinates(startx, starty, 2,width,tall,Qt::black);
    ui->out_grafic->setPixmap(pixmap);
}


Prinsipal::~Prinsipal()
{
    delete ui;
}

//--------------------------------------------------
//--Date-List---------------------------------------
void Prinsipal::insertList(Nodo *&list, QString n, QString p,float n1, float n2, float nt)
{
    Nodo *new_nodo = new Nodo();

    new_nodo->Date_L = n+";"+p+";"+QString::number(n1)+";"+QString::number(n2)+";"+QString::number(nt);

    Nodo *aux1 = list;
    Nodo *aux2;

    while((aux1 != NULL)&&(aux1->Date_L < n)){
        aux2 = aux1;
        aux1 = aux1->siguiente;
    }

    if(list == aux1){
        list = new_nodo;
    }else{
        aux2->siguiente = new_nodo;
    }

    new_nodo->siguiente = aux1;
}

void Prinsipal::showList(Nodo *)
{
    Nodo *actual = new Nodo();
    actual = list;
    //int date2=0;
    //int i=0,date2=0,flag=0,flag1=1,flag2=4, note,accumulator=0, counter=0;
    //QString name2, surname2;

    ui->select_stidents->clear();
    limpieza();

    while (actual !=NULL) {
        QStringList date = actual->Date_L.split(";");
        QString name = date[0];
        QString firstname = date[1];

        float n1 = date[2].toFloat();
        float n2 = date[3].toFloat();
        float nt = date[4].toFloat();

        /*bar(date2,startx, starty,tall,(n1+n2),name);
        date2=date2+30;
        ui->out_grafic->setPixmap(pixmap);*/

        ui->select_stidents->addItem(firstname+" "+name);

        int posicition = ui->out_StudentName->rowCount();
        ui->out_StudentName->insertRow(posicition);
        ui->out_NoteStudents->insertRow(posicition);

        ui->out_StudentName->setItem(posicition,0, new QTableWidgetItem(name));
        ui->out_StudentName->setItem(posicition,1, new QTableWidgetItem(firstname));

        ui->out_NoteStudents->setItem(posicition,0, new QTableWidgetItem(name));
        ui->out_NoteStudents->setItem(posicition,1, new QTableWidgetItem(firstname));
        ui->out_NoteStudents->setItem(posicition,2, new QTableWidgetItem(QString::number(n1)));
        ui->out_NoteStudents->setItem(posicition,3, new QTableWidgetItem(QString::number(n2)));
        ui->out_NoteStudents->setItem(posicition,4, new QTableWidgetItem(QString::number(nt)));

        actual = actual->siguiente;
    }
}

void Prinsipal::lookFor(Nodo *,QString n)
{
    Nodo *actual = new Nodo();
    Stidents *prom = new Stidents;
    actual = list;

    QString n1 = QString::number(ui->in_Notes1->value());
    QString n2 = QString::number(ui->in_Notes2->value());
    float nt1 = ui->in_Notes1->value();
    float nt2 = ui->in_Notes2->value();
    float nt_ave = prom->promedio(nt1,nt2);

    while ((actual != NULL)) {
        QStringList date = actual->Date_L.split(";");
        QString name = date[0];
        QString firstname = date[1];
        QString D_actual = firstname+" "+name;

        if(D_actual == n){
            actual->Date_L = name+";"+firstname+";"+n1+";"+n2+";"+QString::number(nt_ave,'f',2);

            insertNodo(tree,nt_ave);
        }
        actual = actual->siguiente;
    }

}
//--------------------------------------------------
//--Date-Tree---------------------------------------
Nodo *Prinsipal::crearNodo(float n)
{
    Nodo *new_nodo = new Nodo();

    new_nodo->Date_T = n;
    new_nodo->right = NULL;
    new_nodo->left = NULL;

    return new_nodo;
}

void Prinsipal::insertNodo(Nodo *&tree, float n)
{
    if(tree == NULL){
        Nodo *new_nodo = crearNodo(n);
        tree = new_nodo;
    }else{
        float valorRaiz = tree->Date_T;

        if(n < valorRaiz){
            insertNodo(tree->left,n);
        }else{
            insertNodo(tree->right,n);
        }
    }
}
void Prinsipal::preOrder(Nodo *tree)
{
    if(tree!=NULL)
    {
        ui->in_showTreeTipe->insertPlainText(QString::number(tree->Date_T,'f',2)+" - ");
        preOrder(tree->left);
        preOrder(tree->right);
    }
}
void Prinsipal::inOrder(Nodo *tree){
    if(tree!=NULL){
        inOrder(tree->left);
        ui->in_showTreeTipe->insertPlainText(QString::number(tree->Date_T,'f',2)+" - ");
        inOrder(tree->right);
    }
}
void Prinsipal::postOrder(Nodo *tree)
{
    if(tree!=NULL)
    {
         postOrder(tree->left);
         postOrder(tree->right);
         ui->in_showTreeTipe->insertPlainText(QString::number(tree->Date_T,'f',2)+" - ");
    }
}

void Prinsipal::showElementsTree()
{
    incX=0;
    incY=0;

    showYggdrasil(tree,0);
    ui->in_showTreeTipe->appendPlainText("*** Tree walk ***");
    ui->in_showTreeTipe->appendPlainText("In order: ");
    inOrder(tree);
    ui->in_showTreeTipe->appendPlainText("");
    ui->in_showTreeTipe->appendPlainText("Pre order: ");
    preOrder(tree);
    ui->in_showTreeTipe->appendPlainText("");
    ui->in_showTreeTipe->appendPlainText("Post order: ");
    postOrder(tree);
}

void Prinsipal::initLienzo(int h, int w)
{
    ui->in_showTree->resize(h+50,w+30);
    lienzo2= QPixmap(ui->in_showTree->size());
    lienzo2.fill(Qt::white);
    ui->in_showTree->setPixmap(lienzo2);
}

void Prinsipal::circle(int r, int x, int y, int incX, int incY, QString text, QColor cf, QColor cl)
{
    QPainter painter(&lienzo2);
    if (incX==0)
        painter.setBrush(cf);
    else
        painter.setBrush(Qt::green);
    QPen pen(cl);
    painter.setPen(pen);
    painter.drawEllipse(x+incX,y+incY,r,r);
    painter.setPen(pen);
    painter.drawText(x+incX+2,y+incY+20,text);
    ui->in_showTree->setPixmap(lienzo2);
}
//--------------------------------------------
void Prinsipal::showYggdrasil(ABB tree, float cont)
{
    if(tree==NULL){return;}
    showYggdrasil(tree->right,cont+1);
    incX = 0;
    for(int i=0;i<cont;i++) {
        incX += 30;
    }

    circle(r,xe,ye,incX,incY,QString::number(tree->Date_T,'f',2),Qt::yellow,Qt::black);
    incX -= 40;
    incY += 30;
    showYggdrasil(tree->left, cont+1);
}
//--------------------------------------------------
//--Start-Table-------------------------------------
void Prinsipal::Satr_Table_Student()
{
    QStringList cabecera = {"Nombres", "Apellidos"};
    ui->out_StudentName->setColumnCount(2);
    ui->out_StudentName->setHorizontalHeaderLabels(cabecera);
}

void Prinsipal::Satr_Table_Notes()
{
    QStringList cabecera = {"Nombres", "Apellidos","Parcial 1","Parcial 2","Promedio"};
    ui->out_NoteStudents->setColumnCount(5);
    ui->out_NoteStudents->setHorizontalHeaderLabels(cabecera);
}
//--------------------------------------------------
//--Enter-Date--------------------------------------
void Prinsipal::contator()
{
    ui->out_courseOverall->clear();
    int posicion = ui->out_StudentName->rowCount();
    float div;
    totalAverage = 0;
    Nodo *actual = new Nodo();
    actual = list;

    for (int v=0;v<posicion;v++) {
        float vart = ui->out_NoteStudents->item(v,4)->text().toFloat();
        totalAverage += vart;
    }

    div = totalAverage/posicion;
    ui->out_courseOverall->setText(QString::number(div,'f',2));
    insertNodo(tree,div);

    while (actual !=NULL) {
        QStringList date = actual->Date_L.split(";");
        float nt = date[4].toFloat();
        insertNodo(tree,nt);
        actual = actual->siguiente;
    }
    showElementsTree();
}
void Prinsipal::entranceStudents()
{
    QString name = ui->in_Name->text();
    QString firstname = ui->in_LastName->text();

    if(name=="" || firstname==""){
        return;
    }
    insertList(list,name,firstname,0,0,0);
    showList(list);
}
void Prinsipal::entranceNotesStudents()
{
    QString indice = ui->select_stidents->currentText();
    lookFor(list,indice);
    showList(list);
    contator();
}
//--The-Cleaners--
void Prinsipal::cleanerDatesCamps()
{
    ui->in_Name->clear();
    ui->in_LastName->clear();
    ui->in_Name->hasFocus();
}
//--------------------------------------------------
//--File-Options------------------------------------
void Prinsipal::folderLocation()
{
    QString intfolder = "C:/Users/Kenneth D/Documents/Notes_manager/Document_Notes";
    QString file_name = QFileDialog::getSaveFileName(this,tr("Save file"),intfolder,"Notes files (*.kvj)");

    QFile file(file_name);
    int position = ui->out_NoteStudents->rowCount();

    if(file.open(QFile::WriteOnly|QFile::Truncate)){
        QTextStream out(&file);
        for (int x=0;x<position;x++) {
            out << ui->out_NoteStudents->item(x,0)->text()<<";"<<
                   ui->out_NoteStudents->item(x,1)->text()<<";"<<
                   ui->out_NoteStudents->item(x,2)->text()<<";"<<
                   ui->out_NoteStudents->item(x,3)->text()<<";"<<
                   ui->out_NoteStudents->item(x,4)->text()<<"\n";
        }
        out << ui->out_NoteStudents;

        QMessageBox::information(this, tr("Mensaje"),tr("Guardado correctamente"));
    }else{
        QMessageBox::information(this, tr("Error"),tr("No guardo el archivo"));
    }
}

void Prinsipal::saveFileAs()
{
    QDir directory;
    directory.setPath("C:/Users/Kenneth D/Documents");
    int count = directory.count();

    for (int x=2;x<count;++x) {
        if(directory[x]=="Notes_manager"){
            folderLocation();
            return;
        }
    }
    directory.mkdir("Notes_manager");
    folderLocation();
}

void Prinsipal::saveFile()
{
    QFileDialog::getSaveFileName();
}

void Prinsipal::openFile()
{
    int date2=0;
    QString OpenDir = "C:/Users/Kenneth D/Documents/Notes_manager";
    //QString OpenDir = "D:/";
    QString tipeFile = QFileDialog::getOpenFileName(this,("Open file"),OpenDir,"File to configuration (*.kvj)");
    QFile file_name(tipeFile);

    bool lastLine = true;
    if(file_name.open(QFile::ReadOnly)){
        QTextStream in(&file_name);
        while(!in.atEnd()){
            QString line = in.readLine();
            QList<QStandardItem *> standardItemsList;
            if(in.atEnd()){
                lastLine = false;
                continue;
            }

            QStringList date = line.split(";");
            QString D_Name = date[0];
            QString D_FirtName = date[1];
            float D_Note1 = date[2].toFloat();
            float D_Note2 = date[3].toFloat();
            float D_Average = date[4].toFloat();

            bar(date2,startx, starty,tall,(D_Note1+D_Note2),D_Name);
            date2=date2+30;
            ui->out_grafic->setPixmap(pixmap);

            insertList(list,D_Name,D_FirtName,D_Note1,D_Note2,D_Average);
        }
        QMessageBox::information(this, tr("Mensaje"),tr("Document read correctly "));
    }
}

void Prinsipal::saverPicture()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(
                this,"Save picture",
                "Estadistic.png",
                "Picture (*.png)");
    if(!nombreArchivo.isEmpty()){
        if(lienzo.save(nombreArchivo)){
            QMessageBox::information(this,"Save picture","File saved in: " + nombreArchivo);
        }else{
            QMessageBox::warning(this,"Save picture","The file could not be saved");
        }
    }
}
//--------------------------------------------------
//--Show-Window-------------------------------------
void Prinsipal::verificationChangeWindows()
{
    ui->in_ChangeWindows->addItem("Window mode");
    ui->in_ChangeWindows->addItem("Fullscreen");
}

void Prinsipal::startedChangeWindows()
{
    if(ui->in_ChangeWindows->currentText()=="Window mode"){
        return showNormal();
    }else{
        return showFullScreen();
    }
}
//--------------------------------------------------
//--Windows-Chabge----------------------------------
void Prinsipal::aspect(QString title)
{
    ui->label->clear();
    TITEL = title;
    ui->label->setText("<font size = 150 px>"
                       "<font color='white'>"+TITEL+"</font>");
    ui->label->setAlignment(Qt::AlignCenter);
}

void Prinsipal::efectsSave()
{
    Dialog_Save *saverFile = new Dialog_Save(this);
    Nodo *actual = new Nodo();

    if(ui->out_StudentName->item(0,0)){
        saverFile->exec();
        if(saverFile->getDesitio() == 'y'){
            saveFileAs();


            limpieza();
            complement();
        }else if(saverFile->getDesitio() == 'c'){
            return;
        }else if(saverFile->getDesitio() == 'n'){
            while (list != NULL) {
                resetList(list,actual->Date_L);
            }

            limpieza();
            complement();
        }
    }else{
        complement();
    }
    showList(list);
    contator();
}

void Prinsipal::complement()
{
    openFile();
    QString title=("Assign notes");
    aspect(title);
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void Prinsipal::limpieza()
{

    while (ui->out_NoteStudents->rowCount() > 0)
    {
        ui->out_NoteStudents->removeRow(0);
        ui->out_StudentName->removeRow(0);
        ui->select_stidents->removeItem(0);
        ui->in_showTreeTipe->clear();
        ui->in_showTree->clear();
        //ui->out_grafic->setPixmap(pixmap);
    }
}

void Prinsipal::resetList(Nodo *&list,QString &n)
{
    Nodo *aux = list;
    n = aux->Date_L;
    list = aux->siguiente;
    delete aux;
}
//VADY
void Prinsipal::Enterokay(int width, int tall)
{
    pixmap.fill(Qt::white);
    painter.begin(&pixmap);
    pen.setColor(Qt::black);
    dialogue((width / 3), tall+15, "Note weighting", 23);
}

void Prinsipal::dialogue(int x, int y, QString dialogue, int size)
{
    painter.setPen(pen);
    QFont font = painter.font();
    font.setPixelSize(size);
    painter.setFont(font);
    painter.drawText(x,y,dialogue);
}

void Prinsipal::coordinates(int startx, int starty, int thickness, int width, int tall, QColor color)
{
    pen.setWidth(thickness);
    pen.setColor(Qt::red);
    pen.setJoinStyle(Qt::MiterJoin);
    painter.setPen(pen);
    painter.drawLine(startx,starty-30,startx,tall);
    dialogue(startx-12, 40, "100", 16);
    painter.drawLine(startx,tall,width,tall);
    dialogue(width, tall+10, "100", 16);
    painter.drawLine(startx +450,tall/2,12,tall/2);
    pen.setColor(Qt::black);
    dialogue(0, tall/2, "70", 18);
}

void Prinsipal::bar(int displacement, int startx, int starty, int tall, int note, QString name)
{
    if (note < 50){
        painter.setBrush(Qt::red);
    }else if(note < 79){
        painter.setBrush(Qt::yellow);
    }else {
        painter.setBrush(Qt::green);
    }
    pen.setColor(Qt::black);
    painter.setPen(pen);
    if (note==0)
       starty=tall;
    else
       if (note==70)
          starty=(tall/2);
       else
             starty= tall -((tall*note)/100)+70;
    dialogue(startx+18+displacement, starty-8, name, 11);
    dialogue(startx+18+displacement, starty-20, QString::number(note), 10);
    painter.drawRect(startx+20+displacement, starty, 20,tall - starty);
}

void Prinsipal::lines(int startx, int tall, int average)
{
    painter.setBrush(Qt::green);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    int value;
       if (average==50)
          value=-(tall/2);
       else
          value= tall -((tall*average)/100)+15;
    painter.drawRect(startx+18, value ,width-20,1);
    dialogue(startx+18, value+18 ,QString::number(average), 10);
}
//--------------------------------------------------
//VADY
void Prinsipal::on_cmd_PageStudents_clicked(){
    QString title=("Add new student");
    aspect(title);
    ui->stackedWidget->setCurrentWidget(ui->page_1);
}

void Prinsipal::on_cmd_PageNotes_clicked(){
    QString title=("Assign notes");
    aspect(title);
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void Prinsipal::on_cmd_PageTree_clicked(){
    QString title=("Grade statistics");
    aspect(title);
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void Prinsipal::on_cmd_PageStadistic_clicked(){
    QString title=("Data tree");
    aspect(title);
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}

void Prinsipal::on_cmd_PageConfig_clicked(){
    QString title=("Simple settings");
    aspect(title);
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}
//--------------------------------------------------
//--Progra-actions----------------------------------
void Prinsipal::on_cm_Add_clicked()
{
    entranceStudents();
    cleanerDatesCamps();
}

void Prinsipal::on_cmd_Reload_clicked()
{
    startedChangeWindows();
}

void Prinsipal::on_cm_Calculate_clicked()
{
    entranceNotesStudents();

}
void Prinsipal::on_cmd_Open_clicked()
{
    efectsSave();
}

void Prinsipal::on_cm_SaveImagen_clicked()
{
    saverPicture();
}
void Prinsipal::on_action_Save_triggered()
{
    saveFile();
}

void Prinsipal::on_cmd_NewFile_clicked()
{
    limpieza();
    QString title=("Add new student");
    aspect(title);
    ui->stackedWidget->setCurrentWidget(ui->page_1);
}
//--------------------------------------------------
//--File-Actions------------------------------------
void Prinsipal::on_cmd_Save_clicked()
{
    saveFileAs();

}
//--------------------------------------------------
//--------------------------------------------------

void Prinsipal::on_burron_refresh_clicked()
{
    QString indice = ui->select_stidents->currentText();
    lookFor(list,indice);
    showList(list);
}

