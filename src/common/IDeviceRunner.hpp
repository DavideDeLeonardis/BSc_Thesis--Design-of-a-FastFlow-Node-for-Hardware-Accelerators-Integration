#pragma once

#include "ComputeResult.hpp"
#include <cstddef>

/**
 * @brief Interfaccia per una strategia di esecuzione.
 *
 * Definisce un'unica operazione, 'execute', che il main può chiamare, non sapendo se sta
 * eseguendo su CPU o su acceleratore.
 */
class IDeviceRunner {
 public:
   virtual ~IDeviceRunner() = default;

   /**
    * @brief Esegue l'intero carico di lavoro. É implementata in modo differente dai diversi
    * runner (CPU, GPU con OpenCL, GPU con Metal, ecc.).
    *
    * @param N La dimensione dei dati per ogni singolo task.
    * @param NUM_TASKS Il numero totale di task da eseguire.
    * @return ComputeResult Una struct contenente tutte le metriche.
    */
   virtual ComputeResult execute(size_t N, size_t NUM_TASKS) = 0;
};