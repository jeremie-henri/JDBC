#ifndef MAFENETRE_H
#define MAFENETRE_H

#endif // MAFENETRE_H
#include "charger_csv.h"
#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QTableWidget>


class MaFenetre : public QMainWindow
{
Q_OBJECT
public slots:
    void setQuitter();
    void setColor();

public :
    void setForm(unsigned long numeroCollone);
    MaFenetre(QWidget *parent = nullptr);
    ~MaFenetre();

private :
    CVString m_vet;
    CMatString m_mat;
    QLabel *m_lab;
    QLabel *m_tra;
    QLabel *m_lra;
    QTableWidget *m_tab;
    QPushButton *m_bou;
    QComboBox *m_box;
    QString *m_list;
    QString couleur;
};
