#ifndef PARALYSIS_PROOF_INTERRUPT_H
#define PARALYSIS_PROOF_INTERRUPT_H

#include <atomic>

// this file deals with signals, esp. Ctrl-C

namespace exch {
namespace interrupt {

extern std::atomic<bool> quit;
void set_quite_flag(int n);
void init_signal_handler();

} // namespace interrupt
} // namespace exch

#endif // PARALYSIS_PROOF_INTERRUPT_H
