#include "glavniprozor.h"
#include "ui_glavniprozor.h"
#include "konekcija.h"
#include "unos.h"
#include "spisakpasaporasi.h"

GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor)
{
    ui->setupUi(this);
}

GlavniProzor::~GlavniProzor()
{
    delete ui;
}

void GlavniProzor::on_actionIzlaz_triggered()
{
    this->close();
}

void GlavniProzor::on_actionUnos_triggered()
{
    Unos *u = new Unos(this);
    u->setModal(true);
    u->show();
}

void GlavniProzor::on_actionSpisak_pasa_po_rasi_triggered()
{
    SpisakPasaPoRasi *sppr = new SpisakPasaPoRasi(this);
    sppr->setModal(true);
    sppr->show();
}
