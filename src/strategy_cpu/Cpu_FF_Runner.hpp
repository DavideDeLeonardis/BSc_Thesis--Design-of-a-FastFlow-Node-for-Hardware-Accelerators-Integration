#pragma once

#include "../../include/ff_includes.hpp"
#include "AbstractCpuRunner.hpp"
#include <string>

/**
 * @brief Strategia concreta che esegue il calcolo su CPU utilizzando il parallel_for di FastFlow.
 */
class Cpu_FF_Runner : public AbstractCpuRunner {
 public:
   explicit Cpu_FF_Runner(const std::string &kernel_name);
   virtual ~Cpu_FF_Runner() = default;

 protected:
   /**
    * @brief Implementa il loop parallelo usando ff::ParallelFor.
    */
   void execute_parallel_loop(long start, long end) override;

 private:
   ff::ParallelFor pf_;
};