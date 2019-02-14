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
#include "benchmark.h"
#include "config.h"
#include "enclave-utils.h"
#include "interrupt.h"

#include "ui.h"

#include <QApplication>
#include <propertyconfigurator.h>

using namespace std;

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger(__FILE__));
sgx_enclave_id_t eid;

int main(int argc, char *argv[]) {
  log4cxx::PropertyConfigurator::configure(LOGGING_CONF);

  Config config(argc, (const char **)argv);

  if (0 != initialize_enclave(&eid)) {
    cerr << "failed to init enclave" << endl;
    exit(-1);
  }

  //  st = enclaveTest(eid, &ret);
  //  if (st != SGX_SUCCESS) {
  //    LOG4CXX_ERROR(logger, "ecall failed with return value " << st);
  //  }

  if (!config.isRunBenchmark().empty()) {
    Benchmark benchmark(config.isRunBenchmark());
    benchmark.run();
    benchmark.ToString();

    std::exit(0);
  }

  if (config.isShowGui()) {
    Wallet psw;

    QApplication app(argc, argv);
    WalletForm wallet_ui(&psw);
    wallet_ui.show();
    wallet_ui.setWindowTitle("Paralysis-Proof Wallet");
    app.exec();
  } else {
    LOG4CXX_DEBUG(logger, "GUI disabled.");
  }

  LOG4CXX_INFO(logger, "exiting...");

  // destroy the enclave last
  sgx_destroy_enclave(eid);
}