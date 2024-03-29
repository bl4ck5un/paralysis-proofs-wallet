#include "interrupt.h"
#include <csignal>

std::atomic<bool> exch::interrupt::quit(false);

void exch::interrupt::set_quite_flag(int n) {
  (void)n;
  quit.store(true);
}

void exch::interrupt::init_signal_handler() {
  std::signal(SIGINT, set_quite_flag);
}
