#pragma once

#include "AbstractCpuRunner.hpp"
#include <string>

/**
 * @brief Strategia concreta che esegue il calcolo del kernel su CPU utilizzando le direttive
 * OpenMP.
 */
class Cpu_OMP_Runner : public AbstractCpuRunner {
 public:
   explicit Cpu_OMP_Runner(const std::string &kernel_name);
   virtual ~Cpu_OMP_Runner() = default;

 protected:
   /**
    * @brief Implementa il loop parallelo usando la direttiva #pragma omp.
    */
   void execute_parallel_loop(long start, long end) override;
};