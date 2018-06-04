#ifndef UNOS_H
#define UNOS_H

#include <QDialog>

namespace Ui {
class Unos;
}

class Unos : public QDialog
{
    Q_OBJECT

public:
    explicit Unos(QWidget *parent = 0);
    ~Unos();

private slots:
    void on_pushButtonIzadji_clicked();

    void on_radioButtonUpis_clicked();

    void on_radioButtonBrisanje_clicked();

    void on_lineEditMesto_textChanged(const QString &arg1);

    void on_dateEditDatum_dateChanged(const QDate &date);

    void on_pushButtonUpisi_clicked();

    void on_pushButtonObrisi_clicked();

private:
    Ui::Unos *ui;
};

#endif // UNOS_H
