#include "Cpu_FF_Runner.hpp"

Cpu_FF_Runner::Cpu_FF_Runner(const std::string &kernel_name)
    : AbstractCpuRunner(kernel_name, "CPU Parallel FF") {}

/**
 * @brief Implementazione del loop parallelo con FastFlow. Questa funzione viene chiamata dal
 * metodo execute() della classe base AbstractCpuRunner.
 */
void Cpu_FF_Runner::execute_parallel_loop(long start, long end) {
   // Parallelizza il calcolo usando ff_parallel_for che gestisce il parallelismo a dati su
   // CPU distribuendo le iterazioni del loop sui core disponibili.
   pf_.parallel_for(start, end, 1, 0, [&](const long i) {
      // Chiama l'helper della classe base che contiene la logica di calcolo del kernel.
      this->execute_kernel_work(i);
   });
}