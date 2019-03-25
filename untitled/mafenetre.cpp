#include "mafenetre.h"
#include <iostream>
using namespace std;
MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent){
    setFixedSize(800,600);
    read_csv (m_mat, m_vet, "data.csv");

    m_box = new QComboBox(this);
    m_box->addItem("black");
    m_box->addItem("white");
    m_box->addItem("red");
    m_box->addItem("blue");

    m_tab = new QTableWidget(this);
    m_tab->setRowCount(10);
    m_tab->setColumnCount(4);
    m_tab->setGeometry(0,150,425,325);

//    setForm(1);

    m_box->move(0,100);

    m_lab = new QLabel ("Hello World!", this);
    m_lab->setFont(QFont("Helvetica",30, QFont::Bold, true));
    m_lab->move(310, 10);

    m_bou = new QPushButton("Quitter", this);
    m_bou->setGeometry(720,0,80,40);

    m_tra = new QLabel(this);
    m_tra->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_tra->move(110, 100);

    connect(m_bou, SIGNAL(clicked()), this, SLOT(setQuitter()));
    connect(m_box, SIGNAL(currentIndexChanged(const QString &)),this, SLOT(setColor()));

}

void MaFenetre::setForm(unsigned long numeroCollone){
    for(unsigned long i = 0; i < m_mat.size(); ++i){
        string a = m_mat[i][numeroCollone];
        QString qstr = QString::fromStdString(a);
        m_lra->setText(qstr);
    }

}

void MaFenetre::setQuitter()
{
    exit(0);
}

void MaFenetre::setColor()
{
    couleur = m_box->currentText();
    m_tra->setText(">> " + couleur + " <<");
}

MaFenetre::~MaFenetre(){

}
