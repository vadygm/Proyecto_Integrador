#include "barraestadisticaestudiantes.h"

BarraEstadisticaEstudiantes::BarraEstadisticaEstudiantes(QObject *parent):QObject(parent)
{

}
BarraEstadisticaEstudiantes::BarraEstadisticaEstudiantes(QString nom, float nt1, float nt2)
{
    this->m_fname = nom;
    this->m_n1 = nt1;
    this->m_n2 = nt2;
}
QString BarraEstadisticaEstudiantes::fname() const
{
    return m_fname;
}

void BarraEstadisticaEstudiantes::setFname(const QString &fname)
{
    m_fname = fname;
}

float BarraEstadisticaEstudiantes::n1() const
{
    return m_n1;
}

void BarraEstadisticaEstudiantes::setN1(float n1)
{
    m_n1 = n1;
}

float BarraEstadisticaEstudiantes::n2() const
{
    return m_n2;
}

void BarraEstadisticaEstudiantes::setN2(float n2)
{
    m_n2 = n2;
}
