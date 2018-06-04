#include "unos.h"
#include "ui_unos.h"
#include "konekcija.h"
#include <QMessageBox>

Unos::Unos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Unos)
{
    ui->setupUi(this);
}

Unos::~Unos()
{
    delete ui;
}

void Unos::on_pushButtonIzadji_clicked()
{
    this->close();
}

void Unos::on_radioButtonUpis_clicked()
{
    ui->lineEditSifra->setEnabled(false);
    ui->lineEditMesto->setEnabled(true);
    ui->dateEditDatum->setEnabled(true);
    ui->pushButtonUpisi->setEnabled(true);
    ui->pushButtonObrisi->setEnabled(false);
}

void Unos::on_radioButtonBrisanje_clicked()
{
    ui->lineEditSifra->setEnabled(true);
    ui->lineEditMesto->setEnabled(false);
    ui->dateEditDatum->setEnabled(false);
    ui->pushButtonUpisi->setEnabled(false);
    ui->pushButtonObrisi->setEnabled(true);
}

void Unos::on_lineEditMesto_textChanged(const QString &arg1)
{
    QString imeGrada = arg1;
    imeGrada.truncate(3);
    if(imeGrada.size() == 0)
        imeGrada = "   ";
    else if(imeGrada.size() == 1)
        imeGrada += "  ";
    else if(imeGrada.size() == 2)
        imeGrada += " ";
    QDate datum = ui->dateEditDatum->date();
    QString mesec = datum.toString("MM");
    QString godina = datum.toString("yyyy");

    QString sifraIzlozbe = imeGrada.toUpper() + mesec + godina;
    ui->lineEditSifra->setText(sifraIzlozbe);
}

void Unos::on_dateEditDatum_dateChanged(const QDate &date)
{
    QString imeGrada = ui->lineEditMesto->text();
    imeGrada.truncate(3);
    if(imeGrada.size() == 0)
        imeGrada = "   ";
    else if(imeGrada.size() == 1)
        imeGrada += "  ";
    else if(imeGrada.size() == 2)
        imeGrada += " ";
    QDate datum = date;
    QString mesec = datum.toString("MM");
    QString godina = datum.toString("yyyy");

    QString sifraIzlozbe = imeGrada.toUpper() + mesec + godina;
    ui->lineEditSifra->setText(sifraIzlozbe);
}

void Unos::on_pushButtonUpisi_clicked()
{
    QString sifraIzlozbe = ui->lineEditSifra->text();
    if(sifraIzlozbe.size() == 9)
    {
        QString mesto = ui->lineEditMesto->text();
        QString datum = ui->dateEditDatum->date().toString(Qt::TextDate);

        Konekcija baza;
        if(!baza.dbOpen())
        {
            QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
        }
        else
        {
            QSqlQuery upit;
            upit.prepare("INSERT INTO Izlozba (IzlozbaID, Mesto, Datum) VALUES (:sifraIzlozbe, :mesto, :datum);");
            upit.bindValue(":sifraIzlozbe", sifraIzlozbe);
            upit.bindValue(":mesto", mesto);
            upit.bindValue(":datum", datum);
            if(!upit.exec())
            {
                QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
            }
            else
            {
                QMessageBox::information(this, "Uspesno!!!", "Izlozba uspesno prijavljena!!!");
            }
        }
        baza.dbClose();
    }
    else
    {
        QMessageBox::critical(this, "Kriticno!!!", "Sifra nema 9 znakova!!!");
    }
}

void Unos::on_pushButtonObrisi_clicked()
{
    QString sifraIzlozbe = ui->lineEditSifra->text();
    if(sifraIzlozbe.size() == 9)
    {
        Konekcija baza;
        if(!baza.dbOpen())
        {
            QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
        }
        else
        {
            QSqlQuery upit;
            upit.prepare("DELETE FROM Izlozba WHERE IzlozbaID = :sifraIzlozbe;");
            upit.bindValue(":sifraIzlozbe", sifraIzlozbe);
            if(!upit.exec())
            {
                QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
            }
            else
            {
                QMessageBox::information(this, "Uspesno!!!", "Izlozba uspesno obrisana iz baze podataka!!!");
            }
        }
        baza.dbClose();
    }
    else
    {
        QMessageBox::critical(this, "Kriticno!!!", "Sifra nema 9 znakova!!!");
    }
}
