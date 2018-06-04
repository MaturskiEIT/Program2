#include "spisakpasaporasi.h"
#include "ui_spisakpasaporasi.h"
#include "konekcija.h"
#include <QMessageBox>

SpisakPasaPoRasi::SpisakPasaPoRasi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpisakPasaPoRasi)
{
    ui->setupUi(this);

    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QSqlQuery upit;

        upit.prepare("SELECT IzlozbaID FROM Izlozba ORDER BY IzlozbaID;");
        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->comboBoxIzlozba->setModel(model);
        }

        upit.prepare("SELECT NazivRase FROM Rasa ORDER BY NazivRase;");
        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->comboBoxRasa->setModel(model);
        }
    }
    baza.dbClose();
}

SpisakPasaPoRasi::~SpisakPasaPoRasi()
{
    delete ui;
}

void SpisakPasaPoRasi::on_pushButtonIzadji_clicked()
{
    this->close();
}

void SpisakPasaPoRasi::on_pushButtonPrikazi_clicked()
{
    QString izlozbaID = ui->comboBoxIzlozba->currentText();
    QString rasa = ui->comboBoxRasa->currentText();
    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QSqlQuery upit;

        upit.prepare("SELECT COUNT (*) FROM Rezultat WHERE IzlozbaID = :izlozbaID AND Rezultat IS NOT NULL;");
        upit.bindValue(":izlozbaID", izlozbaID);
        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            upit.next();
            ui->labelBrojUcesnika->setText(upit.value(0).toString());
        }

        upit.prepare("SELECT COUNT (*) FROM Rezultat INNER JOIN Pas ON Rezultat.PasID = Pas.PasID INNER JOIN Rasa ON Pas.RasaID = Rasa.RasaID WHERE Rezultat.IzlozbaID = :izlozbaID AND Rasa.NazivRase = :rasa AND Rezultat.Rezultat IS NOT NULL;");
        upit.bindValue(":izlozbaID", izlozbaID);
        upit.bindValue(":rasa", rasa);
        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            upit.next();
            ui->labelBrojRasaUcestvovali->setText(upit.value(0).toString());
        }

        upit.prepare("SELECT Pas.Ime AS [Ime psa] FROM Pas INNER JOIN Rezultat ON Rezultat.PasID = Pas.PasID INNER JOIN Rasa ON Pas.RasaID = Rasa.RasaID WHERE Rezultat.IzlozbaID = :izlozbaID AND Rasa.NazivRase = :rasa AND Rezultat.Rezultat IS NOT NULL;");
        upit.bindValue(":izlozbaID", izlozbaID);
        upit.bindValue(":rasa", rasa);
        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->tableView->setModel(model);
        }
    }
    baza.dbClose();
}
