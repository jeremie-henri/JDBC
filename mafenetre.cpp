#include "mafenetre.h"
#include <QFont>
#include <QHeaderView>
#include <sstream>
#include <iostream>


MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent){

    setFixedSize(1400,825);

    read_csv(m_mat, m_vet, "data.csv");

    vector<string> truc = chargerComboBox();


    m_fievre = new QLabel("Fievre", this);
    m_fievre->setFont(QFont("Helvetica", 12, QFont::Light, true));
    m_fievre->move(600,150);
    m_douleur = new QLabel("Douleur", this);
    m_douleur->setFont(QFont("Helvetica", 12, QFont::Light, true));
    m_douleur->move(740,150);
    m_toux = new QLabel("Toux", this);
    m_toux->setFont(QFont("Helvetica", 12, QFont::Light, true));
    m_toux->move(900,150);
    m_val_text = new QLabel("Les valeurs des attributs:", this);
    m_val_text->setFont(QFont("Helvetica", 12, QFont::Light, true));
    m_val_text->setGeometry(300,208,200,15);
    m_maladie = new QLabel("Maladie : ", this);
    m_maladie->setFont(QFont("Helvetica", 12, QFont::Light, true));
    m_maladie->setGeometry(650,250,200,20);

    m_bou = new QPushButton("Quitter", this);
    m_bou->setGeometry(1320,0,80,40);
    m_predire = new QPushButton("Predire", this);
    m_predire->setGeometry(1050,196,100,40);

    m_combo_fievre = new QComboBox(this);
    m_combo_fievre->setGeometry(550,200,140,30);
    m_combo_fievre->addItem("NULL");
    m_combo_fievre->addItem("Oui");
    m_combo_fievre->addItem("Non");
    m_combo_douleur = new QComboBox(this);
    m_combo_douleur->setGeometry(700,200,140,30);
    m_combo_douleur->addItem("NULL");
    m_combo_douleur->addItem("Abdomen");
    m_combo_douleur->addItem("Gorge");
    m_combo_douleur->addItem("Non");
    m_combo_toux = new QComboBox(this);
    m_combo_toux->setGeometry(850,200,140,30);
    m_combo_toux->addItem("NULL");
    m_combo_toux->addItem("Oui");
    m_combo_toux->addItem("Non");

    m_tab = new QTableWidget(this);
    m_tab->setGeometry(199,300,1002,352);
    m_tab->setColumnCount(4);
    m_tab->setRowCount(10);
    for (int i(0);i<4;i++) {
        m_tab->setColumnWidth(i,250);

    }
    for (int i(0);i<10;i++) {
        m_tab->setRowHeight(i,350/10);

    }
    m_tab->verticalHeader()->setVisible(false);
    m_tab->horizontalHeader()->setVisible(false);


    connect(m_bou, SIGNAL(clicked()), this, SLOT(setQuitter()));
    connect(m_predire, SIGNAL(clicked()), this, SLOT(predire()));



}
void MaFenetre::setQuitter(){
    exit(0);
}


void MaFenetre::creer_mat(){
    for (unsigned long j(0);j<m_vet.size();j++) {
        m_tab->setItem(0,j,new QTableWidgetItem(m_vet[j].c_str()));
    }

    for (unsigned long i(0);i<m_mat.size();i++) {
        for (unsigned long j(0);j<m_vet.size();j++) {
            m_tab->setItem(i+1,j,new QTableWidgetItem(m_mat[i][j].c_str()));
        }
    }

}

vector<string> MaFenetre::chargerComboBox(){

    vector<string> machin;

    for(unsigned long i = 0; i < m_mat.size(); ++i){
        for(unsigned long j = 0; j < m_mat.size()/2; ++j){
            machin.push_back(m_mat[i][j]);
        }
    }
    return machin;
}

void MaFenetre::score(string maladie, string fievre, string douleur, string toux, vector<double> &Scores, unsigned total){
    double Score;
    double Freq;
    double Conf;
    double Conf_f;
    double Conf_d;
    double Conf_t;
    double cpt0 = 0.0;
    double cpt1 = 0.0;
    double cpt2 = 0.0;
    double cpt3 = 0.0;
    for (unsigned long i(0);i<total;i++) {
        if(m_mat[i][3] == maladie)cpt0 += 1.0;
    }
    for (int i(0);i<total;i++) {
        if(m_mat[i][3] == maladie){
            if(m_mat[i][0] == fievre){
                cpt1 += 1.0;
            }
            if (m_mat[i][1] == douleur) {
                cpt2 += 1.0;
            }
            if (m_mat[i][2] == toux) {
                cpt3 += 1.0;
            }
        }
    }
    Freq=cpt0;
    if (fievre == "NULL")
        Conf_f = 1;
    else
        Conf_f = cpt1/Freq;
    if (douleur == "NULL")
        Conf_d = 1;
    else
        Conf_d = cpt2/Freq;
    if (toux == "NULL")
        Conf_t = 1;
    else
        Conf_t = cpt3/Freq;

    Conf=Conf_f*Conf_d*Conf_t;
    Score=(Freq/total)*Conf;
    Scores.push_back(Score);
}

void MaFenetre::predire(){
    string fievre = (m_combo_fievre->currentText()).toStdString();
    string douleur = (m_combo_douleur->currentText().toStdString());
    string toux = (m_combo_toux->currentText().toStdString());
    vector<double> Scores(0,0);
    double total = m_mat.size();
    m_alert = new QMessageBox;
    if(fievre == "NULL" && douleur == "NULL" && toux == "NULL"){
        m_maladie->setText("NULL");
    }
    else {
        for (unsigned i(0);i<5;i++) {
            switch (i) {
            case 0:
                score("Appendicite",  fievre,  douleur,  toux,  Scores,  total);
                break;
            case 1:
                score("Rhume",  fievre,  douleur,  toux,  Scores,  total);
                break;
            case 2:
                score("Mal de gorge",  fievre,  douleur,  toux,  Scores,  total);
                break;
            case 3:
                score("Refroidissement",  fievre,  douleur,  toux,  Scores,  total);
                break;
            case 4:
                score("Aucune",  fievre,  douleur,  toux,  Scores,  total);
                break;
            }
        }
        if(Scores[0] == Scores[1] == Scores[2] == Scores[3] == Scores[4]){
            m_maladie->setText("Maladie : Aucune");
        }

        int max =distance(Scores.begin(), max_element(Scores.begin(), Scores.end()));
        switch (max) {
        case 0:
            m_maladie->setText("Maladie : Appendicite");
            break;
        case 1:
            m_maladie->setText("Maladie : Rhume");
            break;
        case 2:
            m_maladie->setText("Maladie : Mal de gorge");
            break;
        case 3:
            m_maladie->setText("Maladie : Refroidissement");
            break;
        case 4:
            m_maladie->setText("Maladie : Aucune");
            break;
        }
    }
}
