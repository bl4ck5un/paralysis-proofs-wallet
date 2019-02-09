#include <atomic>
#include <chrono>
#include <csignal>
#include <fstream>
#include <iostream>
#include <memory>
#include <sgx_urts.h>
#include <stdexcept>
#include <thread>

#include <log4cxx/logger.h>

#include "Enclave_u.h"
#include "Utils.h"
#include "bitcoindrpcclient.h"
#include "config.h"
#include "enclave-rpc-server-impl.h"
#include "external/toml.h"
#include "interrupt.h"

#include "ui.h"

#include <QApplication>
#include <propertyconfigurator.h>

using namespace std;

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger(__FILE__));
sgx_enclave_id_t eid;

int main(int argc, char *argv[]) {
  log4cxx::PropertyConfigurator::configure(LOGGING_CONF);

  if (0 != initialize_enclave(&eid)) {
    cerr << "failed to init enclave" << endl;
    exit(-1);
  }

  sgx_status_t st;
  int ret = 0;

  st = enclaveTest(eid, &ret);
  if (st != SGX_SUCCESS) {
    LOG4CXX_ERROR(logger, "ecall failed with return value " << st);
  }

  QApplication app(argc, argv);
  WalletForm wallet_ui;
  wallet_ui.show();
  wallet_ui.setWindowTitle("Paralysis-Proofs Wallet");
  app.exec();

  LOG4CXX_INFO(logger, "exiting...");

  // destroy the enclave last
  sgx_destroy_enclave(eid);
}