#ifndef PARALYSISPROOFS_BENCHMARK_H
#define PARALYSISPROOFS_BENCHMARK_H

#include <chrono>
#include <log4cxx/logger.h>
#include <string>
#include <vector>

#include "../common/message.h"
#include "Enclave_u.h"
#include "enclave-utils.h"

#include "external/json.hpp"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::string;
using json = nlohmann::json;

using std::vector;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;

extern sgx_enclave_id_t eid;

struct Case {
  size_t n;
  string wallet_tx;
  string fee_payment_tx;
};

struct Results {
  size_t size;
  vector<uint32_t> result;
  Results() = default;

  double mean() const {
    double sum = std::accumulate(std::begin(result), std::end(result), 0.0);
    return sum / result.size();
  }

  double std() const {
    double accum = 0.0;
    double m = mean();

    std::for_each(std::begin(result), std::end(result),
                  [&](const double d) { accum += (d - m) * (d - m); });

    return sqrt(accum / (result.size() - 1));
  }
};

void from_json(const json &j, Case &p);

class Benchmark {
  log4cxx::LoggerPtr logger;
  vector<Case> cases;
  vector<Results> results;
  high_resolution_clock::time_point tmp;
  size_t n_round;

public:
  explicit Benchmark(const string &test_datapath)
      : logger(log4cxx::Logger::getLogger(__FILE__)), n_round(50) {
    std::ifstream test_data_file;
    // register to throw exceptions on I/O failures
    test_data_file.exceptions(std::ifstream::badbit);
    test_data_file.open(test_datapath);

    json _test_data;
    test_data_file >> _test_data;
    cases = _test_data.get<vector<Case>>();

    LOG4CXX_INFO(logger, "going to run " << cases.size() << " test cases");
    results.resize(cases.size());
  }

  size_t getNumCases() const { return cases.size(); }

  const Case &getCase(size_t i) const { return cases.at(i); }
  void startCase(size_t i) { tmp = high_resolution_clock::now(); }

  void stopCase(size_t i) {
    auto now = high_resolution_clock::now();
    results[i].size = cases[i].n;
    results[i].result.push_back(duration_cast<microseconds>(now - tmp).count());
  }

  void run() {
    sgx_status_t st;
    int ret;
    auto result = accusation_result_init();

    for (size_t i = 0; i < cases.size(); i++) {
      for (int round = 0; round < n_round; round++) {
        const auto test_case = cases.at(i);
        startCase(i);
        st = _benchmark_accuse(eid, &ret, test_case.fee_payment_tx.c_str(),
                               test_case.wallet_tx.c_str(), test_case.n,
                               &result);

        stopCase(i);

        if (SGX_SUCCESS != st || ret != 0) {
          if (SGX_SUCCESS != st) {
            print_error_message(st);
          }
          LOG4CXX_ERROR(logger, "error return code " << ret);
          throw std::invalid_argument("error");
        }
      }

      LOG4CXX_INFO(logger, "benchmark " << i << " finished");
    }
  }

  void ToString() const {
    for (const auto &r : results) {
      std::cout << r.size << " " << r.mean() << " " << r.std() << std::endl;
    }
  }
};

#endif // PARALYSISPROOFS_BENCHMARK_H
