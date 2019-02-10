#include "ui.h"
#include "Enclave_u.h"
#include "enclave-utils.h"

#include <sgx_eid.h>
#include <sgx_error.h>

#include "../common/message.h"
#include "default-values.h"

#include <QErrorMessage>
#include <QFileDialog>
#include <QtGlobal>

extern sgx_enclave_id_t eid;

WalletForm::WalletForm(Wallet *c, QWidget *parent)
    : QMainWindow(parent), logger(log4cxx::Logger::getLogger(__FILE__)),
      controller(c) {
  ui.setupUi(this);

  error = QErrorMessage::qtHandler();
  error->setWindowTitle("Oops");

  ui.userInfoView->setModel(c->get_model());
  ui.userInfoView->setVisible(false);
  ui.userInfoView->resizeColumnsToContents();
}

#include <iostream>

void WalletForm::on_actionQuit_triggered(bool) { QApplication::quit(); }

void WalletForm::on_actionLoadWallet_triggered(bool) {
  QFileDialog getWallet(this);
  getWallet.setFileMode(QFileDialog::ExistingFile);
  getWallet.setViewMode(QFileDialog::Detail);

  QStringList fileName;
  if (getWallet.exec()) {
    fileName = getWallet.selectedFiles();
  }

  Q_ASSERT(fileName.size() == 1);

  try {
    controller->loadJSON(fileName[0].toStdString());
    ui.statusbar->showMessage(QString("%1 loaded.").arg(fileName[0]), 5000);

    ui.info->setTitle(
        QString("Wallet %1").arg(controller->get_wallet_address().c_str()));

    ui.userInfoView->setVisible(true);
    ui.userInfoView->resizeColumnsToContents();

    ui.walletAddress->setText(
        QString::fromStdString(controller->get_wallet_address()));
    ui.walletVersion->setText(
        QString::fromStdString(controller->get_version()));
    ui.walletFeeAddress->setText(
        QString::fromStdString(controller->get_fee_payment_address()));
    ui.walletPeriod->setText(QString::number(controller->get_grace_period()));

    ui.whoToRemove->addItems(controller->get_user_names());
    ui.whoToAppeal->addItems(controller->get_user_names());
  } catch (const std::exception &e) {
    ui.statusbar->showMessage(e.what());
    qCritical("Can't load JSON: %s", e.what());
  }
}

void WalletForm::on_loadRemovalExampleButton_clicked(bool) {
  ui.walletTx->setPlainText(DEFAULT_WALLET_UTXO);
  ui.feeTx->setPlainText(DEFAULT_FEE_PAYMENT_TX);
  ui.whoToRemove->setCurrentIndex(DEFAULT_ACCUSATION_IDX);
}

void WalletForm::on_loadAppealExampleButton_clicked(bool) {
  ui.whoToAppeal->setCurrentIndex(DEFAULT_ACCUSATION_IDX);
  ui.lifesignalTx->setPlainText(DEFAULT_LIFE_SIGNAL_TX);
}

void WalletForm::on_removeActionButton_clicked(bool) {
  if (ui.feeTx->toPlainText().isEmpty() || 0 == ui.whoToRemove->count()) {
    qCritical("Empty input");
    return;
  }
  auto accused_index = ui.whoToRemove->currentIndex();

  int ret;
  sgx_status_t st;
  auto result = accusation_result_init();

  auto stupid_mid_val_feeTx = ui.feeTx->toPlainText().toStdString();
  auto stupid_mid_val_walletTx = ui.walletTx->toPlainText().toStdString();
  st = accuse(eid, &ret, stupid_mid_val_feeTx.c_str(),
              stupid_mid_val_walletTx.c_str(), accused_index, &result);

  if (SGX_SUCCESS != st || ret != 0) {
    if (SGX_SUCCESS != st) {
      print_error_message(st);
    }
    LOG4CXX_ERROR(logger, "error return code " << ret);
  } else {
    ui.output->setPlainText(
        QString("Tx1=%1\n\nTx2=%2")
            .arg(hexStr(result.tx1, result.tx1_len).c_str())
            .arg(hexStr(result.tx2, result.tx2_len).c_str()));
  }
}

void WalletForm::on_appealActionButton_clicked(bool) {
  if (ui.lifesignalTx->toPlainText().isEmpty() ||
      0 == ui.whoToAppeal->count()) {
    qCritical("Empty input");
    return;
  }

  auto accused_index = ui.whoToRemove->currentIndex();

  int ret = 0;
  sgx_status_t st;
  auto result = appeal_result_init();

  LOG4CXX_ERROR(logger, "here");

  auto stupid_mid_val = ui.lifesignalTx->toPlainText().toStdString();
  st = appeal(eid, &ret, stupid_mid_val.c_str(), accused_index, &result);
  if (SGX_SUCCESS != st || ret != 0) {
    if (SGX_SUCCESS != st) {
      print_error_message(st);
    }
    LOG4CXX_ERROR(logger, "error return code " << ret);
  } else {
    ui.output->setPlainText(QString("tx appeal (hex) =%1")
                                .arg(hexStr(result.tx, result.len).c_str()));
  }
}