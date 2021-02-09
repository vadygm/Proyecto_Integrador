#ifndef STIDENTS_H
#define STIDENTS_H
#include <QObject>

class Stidents: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString nombre READ nombre)
    Q_PROPERTY(QString apellido READ apellido)
    Q_PROPERTY(float n1 READ n1)
    Q_PROPERTY(float n2 READ n2)

public:
    explicit Stidents(QObject *parent = nullptr);
    //------------------------
    //--Attributes------------
    Stidents(QString nombre, QString apellido, float n1, float n2);
    //-----------------------
    //--Getters--------------
    QString nombre() const;
    QString apellido() const;
    float n1() const;
    float n2() const;
    float nt() const;
    //-----------------------
    //--Method---------------
    float promedio(float note1, float note2);

private:
    QString m_nombre;
    QString m_apellido;
    float m_n1;
    float m_n2;
    float m_nt;
};

#endif // STIDENTS_H
