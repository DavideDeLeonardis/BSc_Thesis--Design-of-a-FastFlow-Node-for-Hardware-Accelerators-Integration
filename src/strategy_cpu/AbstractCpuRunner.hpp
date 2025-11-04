#pragma once

#include "../common/ComputeResult.hpp"
#include "../common/IDeviceRunner.hpp"

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Classe base astratta per tutte le strategie di esecuzione su CPU.
 * Utilizza il "Template Method Pattern". Il metodo 'execute' contiene lo scheletro
 * dell'algoritmo, valido per tutte le CPU (validazione, init dati, timing, loop sui task).
 * Viene lasciato un buco (il metodo astratto 'execute_parallel_loop') che le sottoclassi
 * (CpuOmpRunner, CpuFfRunner) devono implementare con la loro logica di parallelizzazione
 * specifica.
 */
class AbstractCpuRunner : public IDeviceRunner {
 public:
   /**
    * @param kernel_name Nome del kernel da eseguire.
    * @param runner_tag Stringa per i log (es. "CPU OpenMP").
    */
   AbstractCpuRunner(const std::string &kernel_name, const std::string &runner_tag)
       : kernel_name_(kernel_name), runner_tag_(runner_tag) {}

   virtual ~AbstractCpuRunner() = default;

   /**
    * @brief Esegue l'intero carico di lavoro su CPU, orchestrando la logica comune a tutte le
    * strategie di esecuzione su CPU (OpenMP, FastFlow).
    */
   ComputeResult execute(size_t N, size_t NUM_TASKS) override {
      // Validazione del kernel.
      if (kernel_name_ != "vecAdd" && kernel_name_ != "polynomial_op" &&
          kernel_name_ != "heavy_compute_kernel") {

         std::cerr << "[ERROR] " << runner_tag_ << ": Unknown kernel name '" << kernel_name_
                   << "'.\n"
                   << "    --> Supported kernels are: 'vecAdd', 'polynomial_op', "
                      "'heavy_compute_kernel'.\n";
         exit(EXIT_FAILURE);
      }

      std::cout << "[" << runner_tag_ << "] Running tasks in PARALLEL on all CPU cores.\n\n";

      // Inizializzazione dei dati.
      a_.resize(N);
      b_.resize(N);
      c_.resize(N);
      for (size_t i = 0; i < N; ++i) {
         a_[i] = int(i);
         b_[i] = int(2 * i);
      }

      size_t tasks_completed = 0;
      auto t0 = std::chrono::steady_clock::now();

      // Esegue NUM_TASKS volte il calcolo parallelo in modo sequenziale.
      for (size_t task_num = 0; task_num < NUM_TASKS; ++task_num) {
         std::cerr << "[" << runner_tag_ << " - START] Processing task " << task_num + 1
                   << " with N=" << N << "...\n";

         // Chiamata al metodo che esegue il calcolo parallelo (definito nelle sottoclassi).
         execute_parallel_loop(0, N);

         std::cerr << "[" << runner_tag_ << " - END] Task " << task_num + 1 << " finished.\n";
         tasks_completed++;
      }

      // Calcolo del tempo totale e ritorno del risultato.
      ComputeResult res;
      auto t1 = std::chrono::steady_clock::now();
      res.elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
      res.tasks_completed = tasks_completed;
      return res;
   }

 protected:
   /**
    * @brief Metodo astratto definito dalle sottoclassi per eseguire il calcolo parallelo.
    */
   virtual void execute_parallel_loop(long start, long end) = 0;

   /**
    * @brief Logica di calcolo del kernel. Viene chiamato N volte nel loop parallelo dalle
    * sottoclassi.
    */
   void execute_kernel_work(long i) {
      if (kernel_name_ == "vecAdd") {
         // --------------------------------------------------------------
         // SOMMA VETTORIALE
         // --------------------------------------------------------------
         c_[i] = a_[i] + b_[i];

      } else if (kernel_name_ == "polynomial_op") {
         // --------------------------------------------------------------
         // OPERAZIONE POLINOMIALE (Calcolo 2a² + 3a³ - 4b² + 5b⁵)
         // --------------------------------------------------------------
         long long val_a = a_[i], val_b = b_[i];
         long long a2 = val_a * val_a, a3 = a2 * val_a;
         long long b2 = val_b * val_b, b4 = b2 * b2, b5 = b4 * val_b;

         c_[i] = (int)((2 * a2) + (3 * a3) - (4 * b2) + (5 * b5));

      } else if (kernel_name_ == "heavy_compute_kernel") {
         // --------------------------------------------------------------
         // COMPUTAZIONE MOLTO PESANTE (for interno e fz. trigonometriche)
         // --------------------------------------------------------------
         double val_a = (double)a_[i], val_b = (double)b_[i], result = 0.0;

         for (int j = 0; j < 5; ++j)
            result += std::sin(val_a + j) * std::cos(val_b - j);

         c_[i] = (int)result;
      }
   }

 protected:
   std::vector<int> a_, b_, c_; // Vettori di dati input/output
   std::string kernel_name_;
   std::string runner_tag_; // Device name per i log
};