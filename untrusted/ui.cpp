#include "ui.h"
#include "Enclave_u.h"
#include "Utils.h"

#include <sgx_eid.h>
#include <sgx_error.h>

#include "../common/message.h"
#include "default-values.h"

extern sgx_enclave_id_t eid;

WalletForm::WalletForm(QWidget *parent)
    : QWidget(parent), logger(log4cxx::Logger::getLogger(__FILE__)) {
  ui.setupUi(this);
}

void WalletForm::on_loadButton_clicked(bool) {
  auto redeemScript = ui.redeemScript->toPlainText();
  auto walletTx = ui.utxo->toPlainText();

  ui.walletinfo->setPlainText("working on it");

  int ret;
  sgx_status_t st;

  if (redeemScript.isEmpty() || walletTx.isEmpty()) {
    ui.walletinfo->setPlainText("Empty!");
    return;
  }

  auto stupid_mid_val_redeemScript = redeemScript.toStdString();
  auto stupid_mid_val_walletTx = walletTx.toStdString();
  st = parse_wallet_info(eid, &ret, stupid_mid_val_redeemScript.c_str(),
                         stupid_mid_val_walletTx.c_str());
  if (SGX_SUCCESS != st) {
    print_error_message(st);
  }
  if (st != SGX_SUCCESS || ret != 0) {
    ui.walletinfo->setPlainText("Error! Enclave returned " +
                                QString::number(ret));
  } else {
    ui.walletinfo->setPlainText("Done.");
  }
}

void WalletForm::on_exitButton_clicked(bool) { QApplication::quit(); }

void WalletForm::on_loadExampleButton_clicked(bool) {
  ui.redeemScript->setPlainText(DEFAULT_REDEEMSCRIPT);
  ui.utxo->setPlainText(DEFAULT_WALLET_UTXO);
  ui.feeTx->setPlainText(DEFAULT_FEE_PAYMENT_TX);
  ui.accused->setText(QString::number(DEFAULT_ACCUSATION_IDX));
}

void WalletForm::on_accuseButton_clicked(bool) {
  if (ui.accused->text().isEmpty() || ui.feeTx->toPlainText().isEmpty()) {
    LOG4CXX_INFO(logger, "empty input");
  }
  bool ok;
  auto accused_index = ui.accused->text().toInt(&ok);
  if (!ok) {
    LOG4CXX_ERROR(logger,
                  "invalid input: " << ui.accused->text().toStdString());
  }

  int ret;
  sgx_status_t st;

  auto result = ar_init();

  auto stupid_mid_val_feeTx = ui.feeTx->toPlainText().toStdString();
  auto stupid_mid_val_walletTx = ui.utxo->toPlainText().toStdString();
  st = accuse(eid, &ret, stupid_mid_val_feeTx.c_str(),
              stupid_mid_val_walletTx.c_str(), accused_index, &result);

  if (SGX_SUCCESS != st || ret != 0) {
    if (SGX_SUCCESS != st) {
      print_error_message(st);
    }
    LOG4CXX_ERROR(logger, "error return code " << ret);
  } else {
    ui.Tx1->setPlainText(
        QString::fromStdString(hexStr(result.tx1, result.tx1_len)));
    ui.Tx2->setPlainText(
        QString::fromStdString(hexStr(result.tx2, result.tx2_len)));
    ui.TxAppeal->setPlainText(
        QString::fromStdString(hexStr(result.tx_appeal, result.tx_appeal_len)));
  }
}