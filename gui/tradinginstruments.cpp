#include "tradinginstruments.h"
#include "ui_tradinginstruments.h"

TradingInstruments::TradingInstruments(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TradingInstruments)
{
    ui->setupUi(this);
}

TradingInstruments::~TradingInstruments()
{
    delete ui;
}
