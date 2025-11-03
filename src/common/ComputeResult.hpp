#pragma once

#include <cstddef>

/**
 * @brief Struct dati per i risultati di qualsiasi strategia.
 *
 * Viene restituita dal metodo 'execute' di IDeviceRunner e contiene tutte le metriche di
 * performance raccolte durante l'esecuzione, sia essa su CPU o su acceleratore. Trasporta
 * i dati grezzi dalla strategia al main.
 */
struct ComputeResult {

   long long elapsed_ns =
      0; // Tempo totale misurato dall'inizio alla fine dell'esecuzione dei task.
   size_t tasks_completed = 0; // Numero totale di task effettivamente completati

   // --- Metriche specifiche degli acceleratori (opzionali) ---
   long long computed_ns = 0;          // Tempo effettivo di calcolo del kernel
   long long total_InNode_time_ns = 0; // Tempo totale trascorso dai task dentro il nodo accelerato
   long long inter_completion_time_ns =
      0; // Tempo medio tra il completamento di due task consecutivi.
};