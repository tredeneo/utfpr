/*
Anderson Candido de Jesus da Silva - RA: 1986740
Daniel de Viveiros Inácio = RA: 1923820
*/

#include "ppos.h"
#include "ppos-core-globals.h"
#include <assert.h>

task_t* scheduler() {
  // FCFS scheduler
  if (readyQueue == NULL) {
    return readyQueue;
  }

  task_t* aux = readyQueue;
  task_t* high_priority = readyQueue;

  do {
    if (aux->priority_v < high_priority->priority_v) {
      high_priority = aux;
    } else if (aux->priority_v == high_priority->priority_v) {
      if (aux->priority < high_priority->priority) {
        high_priority = aux;
      }
    }
    aux = aux->next;
  } while (aux != readyQueue);

  aux = readyQueue;

  do {
    if (aux->priority_v >= -19) {
      aux->priority_v--;
    }
    aux = aux->next;
  } while (aux != readyQueue);

  high_priority->priority_v = high_priority->priority;

  return high_priority;
}

void task_setprio(task_t* task, int prio) {
  if (!(prio >= -20 && prio <= 20)) {
    printf("A prioridade deve ser entre -20 e 20. Prioriedade ajustada para 0\n");
    prio = 0;
  }
  if (task == NULL) {
    taskExec->priority = prio;
    taskExec->priority_v = prio;
    return;
  }
  task->priority = prio;
  task->priority_v = prio;
}

int task_getprio(task_t* task) {
  if (task == NULL) {
    return taskExec->priority;
  }

  return task->priority;
}