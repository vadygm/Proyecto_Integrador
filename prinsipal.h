#ifndef PRINSIPAL_H
#define PRINSIPAL_H

#include <QMainWindow>
#include <QPen>
#include <QPainter>
#include <QStandardItemModel>

struct Nodo{
public:
 QString Date_L;
 float Date_T;
 Nodo* siguiente;

 Nodo* right;
 Nodo* left;
};

typedef struct Nodo *ABB;

QT_BEGIN_NAMESPACE
namespace Ui { class Prinsipal; }
QT_END_NAMESPACE

class Prinsipal : public QMainWindow
{
    Q_OBJECT

public:
    Prinsipal(QWidget *parent = nullptr);
    ~Prinsipal();
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    void insertList(Nodo *&list, QString n,QString p,float n1, float n2, float nt);
    void showList(Nodo *);
    void lookFor(Nodo *,QString n);
    //--------------------------------------------------------------------
    //--------------------------------------------------------------------
    Nodo *crearNodo(float n);
    void insertNodo(Nodo *&,float);
    void showYggdrasil(ABB tree,float);
    void preOrder(Nodo *tree);
    void inOrder(Nodo *tree);
    void postOrder(Nodo *tree);
    void showElementsTree();
    void initLienzo(int h, int w);
    void circle(int r,int x,int y,int incX,int incY,QString text,QColor cf,QColor cl);
    //-------------------------
    //--Start-Table------------
    void Satr_Table_Student();
    void Satr_Table_Notes();
    //-------------------------
    //--Enter-Date-------------
    void contator();
    void entranceStudents();
    void entranceNotesStudents();
    void cleanerDatesCamps();
    void statisticalGraph();
    //-------------------------
    //--File-Options-----------
    void folderLocation();
    void saveFileAs();
    void saveFile();
    void openFile();
    void saverPicture();
    //-------------------------
    //--Show-Window------------
    void verificationChangeWindows();
    void startedChangeWindows();
    void aspect(QString title);
    //-------------------------
    //-------------------------
    void efectsSave();
    void complement();
    void limpieza();
    void resetList(Nodo *&list, QString &n);
    //-------------------------
    //--VADY-------------------
    void Enterokay(int width, int tall);
    void dialogue(int x, int y, QString dialogue, int size);
    void coordinates(int startx,int starty, int thickness, int width, int tall, QColor color);
    void bar(int displacement,int startx, int starty, int tall, int note, QString name);
    void lines(int startx, int tall, int average);

    int width=500;
    int tall=500;
    int startx=50;
    int starty=85;

    //Vady

private slots:
    //-------------------------
    //--Show-Window------------
    void on_cmd_PageStudents_clicked();
    void on_cmd_PageNotes_clicked();
    void on_cmd_PageTree_clicked();
    void on_cmd_PageStadistic_clicked();
    void on_cmd_PageConfig_clicked();
    //-------------------------
    //--Progra-actions---------
    void on_cm_Add_clicked();
    void on_cmd_Reload_clicked();
    void on_cm_Calculate_clicked();
    //-------------------------
    //--File-Actions-----------
    void on_cmd_Open_clicked();
    void on_cmd_Save_clicked();
    void on_cm_SaveImagen_clicked();
    void on_action_Save_triggered();
    void on_burron_refresh_clicked();

    void on_cmd_NewFile_clicked();

private:
    Ui::Prinsipal *ui;
    QString TITEL="Assign notes";

    Nodo *list = NULL;
    Nodo *tree = NULL;
    int contador=0;

    QPixmap lienzo;
    QPixmap lienzo2;

    void dibujar();


    float totalAverage;
    QString datosTree;

    int r=30;
    int xe=20;
    int ye=40;
    int incX=0;
    int incY=0;
    //-------------------------
    //--VADY-------------------
    QPixmap pixmap;
    QPen pen;
    QPainter painter;
    //VADY
};
//----------------------
//----------------------
#endif // PRINSIPAL_H
