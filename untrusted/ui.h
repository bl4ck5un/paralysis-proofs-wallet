#ifndef PARALYSISPROOFS_BACKEND_H
#define PARALYSISPROOFS_BACKEND_H

#include <QErrorMessage>
#include <QObject>
#include <QString>
#include <log4cxx/logger.h>

#include "ui_pp.h"
#include "wallet.h"

class WalletForm : public QMainWindow {
  Q_OBJECT

private:
  log4cxx::LoggerPtr logger;
  QErrorMessage *error;
  Wallet *controller;

public:
  explicit WalletForm(Wallet *c, QWidget *parent = nullptr);

private slots:
  void on_loadRemovalExampleButton_clicked(bool);
  void on_loadAppealExampleButton_clicked(bool);
  void on_removeActionButton_clicked(bool);
  void on_appealActionButton_clicked(bool);
  void on_actionQuit_triggered(bool);
  void on_actionLoadWallet_triggered(bool);

private:
  Ui::MainWindow ui;
};
#endif // PARALYSISPROOFS_BACKEND_H
