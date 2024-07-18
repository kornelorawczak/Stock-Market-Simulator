#include "startmenu.h"
#include "./ui_startmenu.h"
#include "deposit.h"
#include "withdrawal.h"
#include "history.h"
#include "tradinginstruments.h"
#include "portfolio.h"
#include "details.h"
#include "data.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
    , balance(0.0)
    , allocatedFunds(0.0)
    , freeFunds(0.0)
    , currentWeekday(QDate::currentDate().dayOfWeek())
{
    ui->setupUi(this);

    loadSettingsfromCSV();
    loadBalancefromCSV();

    updateBalanceDisplay();
    updateAllocatedFundsDisplay();
    updateFreeFundsDisplay();

    ui->instrumentsButton->setStyleSheet("QPushButton { color: lime; font-size: 22px; }");
    ui->refreshValue->setStyleSheet("QPushButton { font-size: 15px; }");

    ui->refreshValue->setVisible(true);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StartMenu::updateDateTime);
    timer->start(1000);

    midnightTimer = new QTimer(this);
    connect(midnightTimer, &QTimer::timeout, this, &StartMenu::updateMarketStatus);
    midnightTimer->start(10000);

    if (currentWeekday == 6 || currentWeekday == 7) {
        marketStatus = "closed";
        ui->marketStatusValue->setStyleSheet("QLabel { color: red; font-size: 18px; }");
    } else {
        marketStatus = "open";
        ui->marketStatusValue->setStyleSheet("QLabel { color: lime; font-size: 18px; }");
    }
    ui->marketStatusValue->setText(marketStatus);

    QStackedWidget* historyWidget = findChild<QStackedWidget*>("historyWidget");
    History* historyWidgetObject = new History();
    historyWidget->addWidget(historyWidgetObject);
    historyWidget->setVisible(false);

    QStackedWidget* detailsWidget = findChild<QStackedWidget*>("detailsWidget");
    details* detailsWidgetObject = new details();
    detailsWidget->addWidget(detailsWidgetObject);
    detailsWidget->setVisible(false);

    QStackedWidget* tradingInstrumentsWidget = findChild<QStackedWidget*>("tradingInstrumentsWidget");
    TradingInstruments* tradingInstrumentsObject = new TradingInstruments();
    tradingInstrumentsWidget->addWidget(tradingInstrumentsObject);
    tradingInstrumentsWidget->setVisible(true);

    tradingInstrumentsWidget->setCurrentWidget(tradingInstrumentsObject);

    QStackedWidget* portfolioWidget = findChild<QStackedWidget*>("portfolioWidget");
    Portfolio* portfolioObject = new Portfolio();
    portfolioWidget->addWidget(portfolioObject);
    portfolioWidget->setVisible(false);

    fetchDataAndWriteToCSV();

    tradingInstrumentsObject->loadInstruments(QCoreApplication::applicationDirPath() + "/../../data/instruments.csv");

    connect(ui->historyButton, &QPushButton::clicked, [this, historyWidget, historyWidgetObject, tradingInstrumentsWidget, portfolioWidget, detailsWidget]() {
        tradingInstrumentsWidget->setVisible(false);
        portfolioWidget->setVisible(false);
        detailsWidget->setVisible(false);
        historyWidget->setVisible(true);
        ui->instrumentsButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        ui->historyButton->setStyleSheet("QPushButton { color: lime; font-size: 22px; }");
        ui->portfolioButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        historyWidget->setCurrentWidget(historyWidgetObject);

        historyWidgetObject->loadHistory(QCoreApplication::applicationDirPath() + "/../../data/history.csv");
    });

    connect(ui->instrumentsButton, &QPushButton::clicked, [this, tradingInstrumentsWidget, tradingInstrumentsObject, historyWidget, portfolioWidget, detailsWidget]() {
        historyWidget->setVisible(false);
        portfolioWidget->setVisible(false);
        detailsWidget->setVisible(false);
        tradingInstrumentsWidget->setVisible(true);
        ui->instrumentsButton->setStyleSheet("QPushButton { color: lime; font-size: 22px; }");
        ui->historyButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        ui->portfolioButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        tradingInstrumentsWidget->setCurrentWidget(tradingInstrumentsObject);

        tradingInstrumentsObject->loadInstruments(QCoreApplication::applicationDirPath() + "/../../data/instruments.csv");
    });

    connect(ui->portfolioButton, &QPushButton::clicked, [this, portfolioWidget, portfolioObject, tradingInstrumentsWidget, historyWidget, detailsWidget]() {
        historyWidget->setVisible(false);
        portfolioWidget->setVisible(true);
        tradingInstrumentsWidget->setVisible(false);
        detailsWidget->setVisible(false);
        ui->instrumentsButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        ui->historyButton->setStyleSheet("QPushButton { color: white; font-size: 22px; }");
        ui->portfolioButton->setStyleSheet("QPushButton { color: lime; font-size: 22px; }");
        portfolioWidget->setCurrentWidget(portfolioObject);

        portfolioObject->loadPortfolio(QCoreApplication::applicationDirPath() + "/../../data/portfolio.csv");
    });

    connect(tradingInstrumentsObject, &TradingInstruments::instrumentSelected,
            [this, portfolioWidget, detailsWidget, tradingInstrumentsWidget, historyWidget, detailsWidgetObject](const QString &instrumentName) {
                portfolioWidget->setVisible(false);
                tradingInstrumentsWidget->setVisible(false);
                historyWidget->setVisible(false);
                detailsWidget->setVisible(true);
                showDetailsWidget(instrumentName);

                connect(detailsWidgetObject, &details::balanceUpdated, this, &StartMenu::updateBalanceDisplays);
            });

    connect(ui->depositButton, &QPushButton::clicked, this, &StartMenu::showDepositDialog);
    connect(ui->withdrawalButton, &QPushButton::clicked, this, &StartMenu::showWithdrawalDialog);
    connect(ui->refreshValue, &QPushButton::clicked, this, &StartMenu::updateRefreshButton);

    connect(ui->refreshValue, &QPushButton::clicked, this, &StartMenu::refreshDataAndReloadTable); // Connect refresh button

    connect(ui->refreshValue, &QPushButton::clicked, this, &StartMenu::updateBalanceDisplays);

    updateBalanceDisplay();
    updateAllocatedFundsDisplay();
    updateFreeFundsDisplay();
}

StartMenu::~StartMenu()
{
    saveSettingstoCSV();
    delete ui;
    delete timer;
}

void StartMenu::showDetailsWidget(const QString &instrumentName) {
    QStackedWidget* detailsWidget = findChild<QStackedWidget*>("detailsWidget");
    details* detailsWidgetObject = findChild<details*>();

    if (!detailsWidget || !detailsWidgetObject) {
        qDebug() << "Details widget or object not found or not properly initialized";
        return;
    }

    detailsWidget->setCurrentWidget(detailsWidgetObject);
    detailsWidgetObject->updateDetails(instrumentName.toUpper());
    detailsWidget->setVisible(true);
}

void StartMenu::showDetails(const QString &instrumentName) {
    QStackedWidget* detailsWidget = findChild<QStackedWidget*>("detailsWidget");
    details* detailsWidgetObject = new details();
    detailsWidgetObject->updateDetails(instrumentName);
    ui->detailsWidget->setCurrentWidget(detailsWidget);
    detailsWidget->setVisible(true);
    qDebug() << qPrintable(instrumentName);
}

void StartMenu::updateDateTime() {
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeText = dateTime.toString("hh:mm:ss dd.MM.yyyy");
    ui->dateTimeLabel->setText(dateTimeText);
}

void StartMenu::updateRefreshButton() {
    QDateTime now = QDateTime::currentDateTime();
    QString dateTimeText = now.toString("hh:mm:ss dd.MM.yyyy");
    ui->refreshValue->setText(dateTimeText);
    updateBalanceDisplays();
}

void StartMenu::updateMarketStatus() {
    int newWeekDay = QDate::currentDate().dayOfWeek();
    if (newWeekDay != currentWeekday) {
        currentWeekday = newWeekDay;
        if (currentWeekday == 6 || currentWeekday == 7) {
            marketStatus = "closed";
            ui->marketStatusValue->setStyleSheet("QLabel { color: red; font-size: 18px; }");
        } else {
            marketStatus = "open";
            ui->marketStatusValue->setStyleSheet("QLabel { color: lime; font-size: 18px; }");
        }
    }
    ui->marketStatusValue->setText(marketStatus);
}

void StartMenu::addDepositAmount(double amount)
{
    balance += amount;
    freeFunds += amount;
    saveBalancetoCSV();
    emit balanceChanged(balance);
    emit freeFundsChanged(freeFunds);
    updateBalanceDisplay();
    updateFreeFundsDisplay();
}

void StartMenu::subtractWithdrawalAmount(double amount)
{
    balance -= amount;
    freeFunds -= amount;
    saveBalancetoCSV();
    emit balanceChanged(balance);
    emit freeFundsChanged(freeFunds);
    updateBalanceDisplay();
    updateFreeFundsDisplay();
}

void StartMenu::updateBalanceDisplay()
{
    ui->balanceValue->setStyleSheet("QLabel { font-size: 24px; }");
    ui->balanceValue->setText(QString::number(balance, 'f', 2));
}

void StartMenu::updateAllocatedFundsDisplay()
{
    ui->allocatedFundsValue->setStyleSheet("QLabel { font-size: 24px; }");
    ui->allocatedFundsValue->setText(QString::number(allocatedFunds, 'f', 2));
}

void StartMenu::updateFreeFundsDisplay()
{
    ui->freeFundsValue->setStyleSheet("QLabel { font-size: 24px; }");
    ui->freeFundsValue->setText(QString::number(freeFunds, 'f', 2));
}

void StartMenu::updateBalanceDisplays()
{
    loadBalancefromCSV();
}

void StartMenu::showDepositDialog() {
    Deposit depositDialog(this);
    connect(&depositDialog, &Deposit::depositMade, this, &StartMenu::addDepositAmount);
    depositDialog.exec();
}

void StartMenu::showWithdrawalDialog() {
    withdrawal withdrawalDialog(this);
    connect(&withdrawalDialog, &withdrawal::withdrawalMade, this, &StartMenu::subtractWithdrawalAmount);
    withdrawalDialog.exec();
}

void StartMenu::saveSettingstoCSV() {
    QFile file("settings.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing.";
        return;
    }

    QTextStream out(&file);
    out << "LastRefresh,Balance,FreeFunds,AllocatedFunds\n";
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << ","
        << balance << ","
        << freeFunds << ","
        << allocatedFunds << "\n";

    file.close();
}

void StartMenu::loadSettingsfromCSV() {
    QFile file("settings.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading.";
        return;
    }

    QTextStream in(&file);
    QString header = in.readLine();
    QString line = in.readLine();
    QStringList fields = line.split(',');

    if (fields.size() == 4) {
        QDateTime lastRefresh = QDateTime::fromString(fields[0], "yyyy-MM-dd hh:mm:ss");
        balance = fields[1].toDouble();
        freeFunds = fields[2].toDouble();
        allocatedFunds = fields[3].toDouble();

        ui->refreshValue->setText(lastRefresh.toString("hh:mm:ss dd.MM.yyyy"));
        updateBalanceDisplay();
        updateFreeFundsDisplay();
        updateAllocatedFundsDisplay();
    }

    file.close();
}

void StartMenu::loadBalancefromCSV() {
    QFile file(QCoreApplication::applicationDirPath() + "/../../data/balance.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open balance file for reading.";
        return;
    }

    QTextStream in(&file);
    QString line = in.readLine();
    QStringList fields = line.split(' ');

    if (fields.size() == 2) {
        freeFunds = fields[0].toDouble();
        allocatedFunds = fields[1].toDouble();
        balance = freeFunds + allocatedFunds;

        updateFreeFundsDisplay();
        updateAllocatedFundsDisplay();
        updateBalanceDisplay();
    }

    file.close();
}

void StartMenu::saveBalancetoCSV() {
    QFile file(QCoreApplication::applicationDirPath() + "/../../data/balance.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open balance file for writing.";
        return;
    }

    QTextStream out(&file);
    out << freeFunds << " " << allocatedFunds << "\n";

    file.close();
}

void StartMenu::fetchDataAndWriteToCSV() {
    auto gold = Gold();
    auto usd = Currency("USD");
    auto eur = Currency("EUR");
    auto btc = CryptoApi("BTC");
    auto jpy = Currency("JPY");
    auto gbp = Currency("GBP");

    gold.refreshData();
    usd.refreshData();
    eur.refreshData();
    btc.refreshData();
    jpy.refreshData();
    gbp.refreshData();

    QFile file(QCoreApplication::applicationDirPath() + "/../../data/instruments.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open instruments file for writing.";
        return;
    }

    QTextStream out(&file);
    out << gold.getName() << "," << gold.getValue() << "," << gold.difference() << "\n";
    out << usd.getName() << "," << usd.getValue() << "," << usd.difference() << "\n";
    out << eur.getName() << "," << eur.getValue() << "," << eur.difference() << "\n";
    out << btc.getName() << "," << btc.getValue() << "," << btc.difference() << "\n";
    out << jpy.getName() << "," << jpy.getValue() << "," << jpy.difference() << "\n";
    out << gbp.getName() << "," << gbp.getValue() << "," << gbp.difference() << "\n";

    file.close();
}

void StartMenu::refreshDataAndReloadTable() {
    fetchDataAndWriteToCSV();

    QStackedWidget* tradingInstrumentsWidget = findChild<QStackedWidget*>("tradingInstrumentsWidget");
    TradingInstruments* tradingInstrumentsObject = findChild<TradingInstruments*>();
    if (tradingInstrumentsWidget && tradingInstrumentsObject) {
        tradingInstrumentsObject->loadInstruments(QCoreApplication::applicationDirPath() + "/../../data/instruments.csv");
    }
}
