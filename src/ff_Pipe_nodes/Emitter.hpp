#pragma once

#include "../../include/ff_includes.hpp"
#include "../common/Task.hpp"

/**
 * @brief Nodo sorgente della pipeline FastFlow.
 *
 * Il nodo Emitter genera i Task da far processare al nodo ff_node_acc_t.
 * Inizializza i dati di input una sola volta, poi crea dinamicamente un nuovo
 * oggetto Task per ogni richiesta dalla pipeline.
 */
class Emitter : public ff_node {
 public:
   /**
    * @param n Dimensione dei vettori da processare.
    * @param num_tasks Il numero totale di task da generare.
    */
   explicit Emitter(size_t n, size_t num_tasks) : tasks_to_send(num_tasks), tasks_sent(0) {
      // Init dei vettori con i dati di input.
      a.resize(n);
      b.resize(n);
      c.resize(n);
      // ? Usiamo 2 vettori con dati diversi cosi un compilatore estremamente intelligente non
      // ? bara e non trasforma la somma in una moltiplicazione (2 * a[i]).
      for (size_t i = 0; i < n; ++i) {
         a[i] = int(i);
         b[i] = int(2 * i);
      }

      a_ptr_ = a.data();
      b_ptr_ = b.data();
      c_ptr_ = c.data();
      n_ = n;
   }

   /**
    * @brief Genera un nuovo Task fino al raggiungimento del numero totale.
    * @return Un puntatore a un nuovo Task, o FF_EOS al termine.
    */
   void *svc(void *) override {
      if (tasks_sent < tasks_to_send) {
         tasks_sent++;
         return new Task{a_ptr_, b_ptr_, c_ptr_, n_, tasks_sent};
      }

      return FF_EOS; // Tutti i task inviati -> fine stream
   }

 private:
   size_t tasks_to_send;          // Numero totale di task da inviare
   size_t tasks_sent;             // Numero di task già inviati
   std::vector<int> a, b, c;      // Vettori di input/output
   int *a_ptr_, *b_ptr_, *c_ptr_; // Puntatori ai dati di input/output
   size_t n_;                     // Dimensione dei vettori
};