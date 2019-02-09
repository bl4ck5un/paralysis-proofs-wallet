#ifndef PARALYSISPROOFS_BACKEND_H
#define PARALYSISPROOFS_BACKEND_H

#include <QObject>
#include <QString>
#include <log4cxx/logger.h>

#include "pp_ui.h"

class WalletForm : public QWidget {
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

private:
  Ui::Wallet ui;
};
#endif // PARALYSISPROOFS_BACKEND_H
