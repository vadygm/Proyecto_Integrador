#include "staticbar.h"

/*StaticBarInter::StaticBarInter(QObject *parent):QObject(parent)
{

}*/

StaticBarInter::StaticBarInter(QString nom, float nt1, float nt2)
{
    this->m_fname = nom;
    this->m_n1 = nt1;
    this->m_n2 = nt2;
}

QString StaticBarInter::fname() const
{
    return m_fname;
}

void StaticBarInter::setFname(const QString &fname)
{
    m_fname = fname;
}

float StaticBarInter::n1() const
{
    return m_n1;
}

void StaticBarInter::setN1(float n1)
{
    m_n1 = n1;
}

float StaticBarInter::n2() const
{
    return m_n2;
}

void StaticBarInter::setN2(float n2)
{
    m_n2 = n2;
}
