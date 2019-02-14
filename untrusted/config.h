#ifndef PARALYSIS_PROOF_CONFIG_H
#define PARALYSIS_PROOF_CONFIG_H

#include <boost/algorithm/hex.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "Enclave_u.h"
#include "enclave-utils.h"

#include "interrupt.h"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

using namespace std;

class Config {
private:
  bool no_gui;
  string run_benchmark;

public:
  Config(int argc, const char *argv[]) : no_gui(false), run_benchmark("") {
    try {
      po::options_description desc("Paralysis Proofs Wallet");
      desc.add_options()("help,h", "print this message")(
          "no-gui", po::bool_switch(&no_gui)->default_value(false),
          "disable GUI (default: false).")(
          "benchmark", po::value<string>(&run_benchmark), "run benchmark.");

      po::variables_map vm;
      po::store(po::parse_command_line(argc, argv, desc), vm);

      if (vm.count("help")) {
        cerr << desc << endl;
        exit(0);
      }
      po::notify(vm);
    } catch (po::required_option &e) {
      cerr << e.what() << endl;
      exit(-1);
    } catch (std::exception &e) {
      cerr << e.what() << endl;
      exit(-1);
    } catch (...) {
      cerr << "Unknown error!" << endl;
      exit(-1);
    }
  }
  bool isShowGui() const { return !no_gui; }
  string isRunBenchmark() const { return run_benchmark; }
};

#endif // PARALYSIS_PROOF_CONFIG_H
