#include "stidents.h"

Stidents::Stidents(QObject *parent):QObject(parent)
{
}
//--------------------------------
//--Attributes--------------------
Stidents::Stidents(QString nombre, QString apellido, float n1, float n2)
{
    m_nombre=nombre;
    m_apellido=apellido;
    m_n1=n1;
    m_n2=n2;
}
//--------------------------------
//--Getters-----------------------
QString Stidents::nombre() const
{
    return m_nombre;
}

QString Stidents::apellido() const
{
    return m_apellido;
}

float Stidents::n1() const
{
    return m_n1;
}

float Stidents::n2() const
{
    return m_n2;
}
//--------------------------------
//--Method------------------------
float Stidents::promedio(float note1, float note2)
{
    return (note1+note2);
}
//--------------------------------
//--------------------------------

