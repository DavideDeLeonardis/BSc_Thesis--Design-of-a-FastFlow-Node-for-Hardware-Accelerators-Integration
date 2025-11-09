#pragma once

#include "../common/ComputeResult.hpp"
#include "../common/PerformanceData.hpp"
#include <cstddef>
#include <string>

/**
 * Helper per il parsing degli argomenti della riga di comando.
 */
void parse_args(int argc, char *argv[], size_t &N, size_t &NUM_TASKS, std::string &device_type,
                std::string &kernel_path, std::string &kernel_name);

/**
 * Stampa la configurazione attuale della computazione.
 */
void print_configuration(size_t N, size_t NUM_TASKS, const std::string &device_type,
                         const std::string &kernel_path, const std::string &kernel_name);

/**
 * Stampa le istruzioni d'uso.
 */
void print_usage(const char *prog_name);

/**
 * @brief Calcola le metriche di performance finali a partire dai dati grezzi.
 */
PerformanceData calculate_metrics(const ComputeResult &results);

/**
 * Stampa le statistiche finali del benchmark in un formato leggibile,
 * adattando l'output per CPU o acceleratori.
 */
void print_metrics(size_t N, size_t NUM_TASKS, const std::string &device_type,
                   const std::string &kernel_name, const PerformanceData &metrics,
                   size_t final_count);