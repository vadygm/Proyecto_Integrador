#ifndef STATICBAR_H
#define STATICBAR_H

#include <QObject>

class StaticBarInter : public QObject
{
    Q_OBJECT

public:
    //explicit StaticBarInter(QObject *parent = nullptr);
    StaticBarInter(QString nom,float nt1,float nt2);

    QString fname() const;
    void setFname(const QString &fname);

    float n1() const;
    void setN1(float n1);

    float n2() const;
    void setN2(float n2);

private:
    QString m_fname;
    float m_n1;
    float m_n2;
};

#endif // STATICBAR_H
