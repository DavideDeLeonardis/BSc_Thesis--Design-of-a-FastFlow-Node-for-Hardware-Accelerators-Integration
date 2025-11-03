#pragma once

#include "../common/IDeviceRunner.hpp"
#include <memory>
#include <string>

/**
 * @brief Funzione Factory che crea e restituisce la strategia di esecuzione
 * appropriata, ovvero un'istanza concreta di IDeviceRunner (es. Cpu_OMP_Runner)
 * in base al tipo di device specificato.
 *
 * @param device_type Il tipo di device (es. "cpu_omp", "gpu_opencl").
 * @param kernel_path Il percorso al file del kernel (per GPU/FPGA).
 * @param kernel_name Il nome della funzione kernel (per CPU e GPU/FPGA).
 * @return Un puntatore all'interfaccia IDeviceRunner o nullptr se
 * il device_type non è valido.
 */
std::unique_ptr<IDeviceRunner> create_runner_for_device(const std::string &device_type,
                                                        const std::string &kernel_path,
                                                        const std::string &kernel_name);