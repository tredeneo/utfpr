/*
Anderson Candido de Jesus da Silva - RA: 1986740
Daniel de Viveiros Inácio = RA: 1923820
*/

#include "ppos.h"
#include "ppos-core-globals.h"
#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

// #define DEBUG

#define INTERVAL 1000
struct sigaction action;
// estrutura de inicialização to timer
struct itimerval timer;

// ****************************************************************************
// Coloque aqui as suas modificações, p.ex. includes, defines variáveis,
// estruturas e funções

// ****************************************************************************
static const short QUANTUM_SIZE = 20;
static long long int global_timer = 0;

void tratador(int signum) {
  global_timer++;
  if (taskExec->id != taskDisp.id && taskExec != NULL && PPOS_IS_PREEMPT_ACTIVE) {
    taskExec->quantum--;
    if (taskExec->quantum == 0) {
      task_yield();
      return;
    }
    taskExec->timer++;
  }
}

void before_ppos_init() {
#ifdef DEBUG
  printf("\ninit - BEFORE");
#endif
}

void after_ppos_init() {
  PPOS_PREEMPT_ENABLE
  // PPOS_PREEMPT_DISABLE

  action.sa_handler = tratador;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  if (sigaction(SIGALRM, &action, 0) < 0) {
    perror("Erro em sigaction: ");
    exit(1);
  }

  // ajusta valores do temporizador
  timer.it_value.tv_usec = INTERVAL;     // primeiro disparo, em micro-segundos
  timer.it_value.tv_sec = 0;             // primeiro disparo, em segundos
  timer.it_interval.tv_usec = INTERVAL;  // disparos subsequentes, em micro-segundos
  timer.it_interval.tv_sec = 0;          // disparos subsequentes, em segundos

  // arma o temporizador ITIMER_REAL (vide man setitimer)
  if (setitimer(ITIMER_REAL, &timer, 0) < 0) {
    perror("Erro em setitimer: ");
    exit(1);
  }

#ifdef DEBUG
  printf("\ninit - AFTER");
#endif
}

void before_task_create(task_t* task) {
  task->activation = 0;
  task->timer = 0;
  task->start_time = global_timer;
  task->end_time = 0;
  task->priority = 0;
  task->priority_v = 0;
  task->quantum = QUANTUM_SIZE;
#ifdef DEBUG
  printf("\ntask_create - BEFORE - [%d]", task->id);
#endif
}

void after_task_create(task_t* task) {
  task->quantum = QUANTUM_SIZE;
#ifdef DEBUG
  printf("\ntask_create - AFTER - [%d]", task->id);
#endif
}

void before_task_exit() {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_exit - BEFORE - [%d]", taskExec->id);
#endif
}

void after_task_exit() {
  freeTask->end_time = global_timer;
  printf("Task %d exit: execution time %d ms, processor time %d ms, %d activations\n", freeTask->id, freeTask->end_time - freeTask->start_time, freeTask->timer,
         freeTask->activation);
#ifdef DEBUG
  printf("\ntask_exit - AFTER- [%d]", taskExec->id);
#endif
}

void before_task_switch(task_t* task) {
  task->quantum = QUANTUM_SIZE;
#ifdef DEBUG
  printf("\ntask_switch - BEFORE - [%d -> %d]", taskExec->id, task->id);
#endif
}

void after_task_switch(task_t* task) {
  task->quantum = QUANTUM_SIZE;
  task->activation++;
#ifdef DEBUG
  printf("\ntask_switch - AFTER - [%d -> %d]", taskExec->id, task->id);
#endif
}

void before_task_suspend(task_t* task) {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_suspend - BEFORE - [%d]", task->id);
#endif
}

void after_task_suspend(task_t* task) {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_suspend - AFTER - [%d]", task->id);
#endif
}

void before_task_resume(task_t* task) {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_resume - BEFORE - [%d]", task->id);
#endif
}

void after_task_resume(task_t* task) {
#ifdef DEBUG
  printf("\ntask_resume - AFTER - [%d]", task->id);
#endif
}

void before_task_sleep() {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_sleep - BEFORE - [%d]", taskExec->id);
#endif
}

void after_task_sleep() {
  // put your customization here
#ifdef DEBUG
  printf("\ntask_sleep - AFTER - [%d]", taskExec->id);
#endif
}

// retorna o relógio atual (em milisegundos)
unsigned int systime() {
  return global_timer;
}
