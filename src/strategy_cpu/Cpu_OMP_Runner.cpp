#include "Cpu_OMP_Runner.hpp"

#include <omp.h>

Cpu_OMP_Runner::Cpu_OMP_Runner(const std::string &kernel_name)
    : AbstractCpuRunner(kernel_name, "CPU OpenMP") {}

/**
 * @brief Implementazione del loop parallelo con OpenMP. Questa funzione viene chiamata dal
 * metodo execute() della classe base AbstractCpuRunner.
 */
void Cpu_OMP_Runner::execute_parallel_loop(long start, long end) {
// Dice al compilatore di parallelizzare il ciclo for distribuendolo tra i thread disponibili.
#pragma omp parallel for
   for (long i = start; i < end; ++i) {
      // Chiama l'helper della classe base che contiene la logica del kernel
      this->execute_kernel_work(i);
   }
}