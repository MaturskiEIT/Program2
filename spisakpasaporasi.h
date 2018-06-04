#ifndef SPISAKPASAPORASI_H
#define SPISAKPASAPORASI_H

#include <QDialog>

namespace Ui {
class SpisakPasaPoRasi;
}

class SpisakPasaPoRasi : public QDialog
{
    Q_OBJECT

public:
    explicit SpisakPasaPoRasi(QWidget *parent = 0);
    ~SpisakPasaPoRasi();

private slots:
    void on_pushButtonIzadji_clicked();

    void on_pushButtonPrikazi_clicked();

private:
    Ui::SpisakPasaPoRasi *ui;
};

#endif // SPISAKPASAPORASI_H
