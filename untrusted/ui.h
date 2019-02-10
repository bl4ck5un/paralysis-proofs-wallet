#ifndef PARALYSISPROOFS_BACKEND_H
#define PARALYSISPROOFS_BACKEND_H

#include <QObject>
#include <QString>
#include <log4cxx/logger.h>

#include "ui_pp.h"

class WalletForm : public QMainWindow {
  Q_OBJECT

private:
  log4cxx::LoggerPtr logger;

public:
  explicit WalletForm(QWidget *parent = nullptr);

private slots:
  void on_loadButton_clicked(bool);
  void on_exitButton_clicked(bool);
  void on_loadExampleButton_clicked(bool);
  void on_accuseButton_clicked(bool);
  void on_actionQuit_triggered(bool);
  void on_actionLoadWallet_triggered(bool);

private:
  Ui::MainWindow ui;
};
#endif // PARALYSISPROOFS_BACKEND_H
