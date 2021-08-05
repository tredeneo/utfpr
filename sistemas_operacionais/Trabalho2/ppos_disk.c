/*
Alunos:
Daniel de Viveiros Inácio
Anderson Candido de Jesus da Silva
*/

#include "ppos_disk.h"
#include "disk.h"
#include "ppos-core-globals.h"
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


disk_t *diskRequestQueue = NULL; // Ponteiro para a fila de tarefas dormindo
task_t *diskSleepQueue = NULL;   // Ponteiro para a fila de tarefas dormindo
task_t *diskTask = NULL;
semaphore_t disk_sem;

#define FCFS 1
#define SSTF 2
#define CSCAN 3

#define DISK_ALGORITHM FCFS

unsigned int tempo_exec = 0;
unsigned int init = 0;
// maneira burra
int last_block = 0;

// fim da maneira burra

static int ME_ACORDA_AI = 0;
unsigned int blocos_percorridos = 0;

void diskDriverBody(void *args) {
  
  while (1) {
    sem_down(&disk_sem);
    if (countTasks == 1) {
      
      printf("Percorreu:%d\n", blocos_percorridos);
      printf("Tempo exec:%d\n", tempo_exec);
      task_exit(0);
    }

    if (ME_ACORDA_AI) {
      // queue_remove((queue_t **)&sleepQueue, (queue_t *)sleepQueue);
      ME_ACORDA_AI = 0;
      task_resume(queue_remove(&diskSleepQueue, diskSleepQueue));
    }

    if (disk_cmd(DISK_CMD_STATUS, 0, 0) == 1 && (diskRequestQueue != NULL)) {
      init = systime();
      disk_t* request_to_be_removed = NULL;
      switch (DISK_ALGORITHM) {
      case FCFS:
        request_to_be_removed = fcfs();
        break;
      case SSTF:
        request_to_be_removed = sstf();
        break;
      case CSCAN:
        request_to_be_removed = cscan();
        break;
      default:
        break;
      }
      if(request_to_be_removed != NULL)
        free(request_to_be_removed);
      tempo_exec = tempo_exec + (systime()-init);
    }


    sem_up(&disk_sem);
    task_yield();
  }
}

disk_t* fcfs() {
  blocos_percorridos += abs(last_block - diskRequestQueue->block);
  last_block = diskRequestQueue->block;
  disk_cmd(diskRequestQueue->operacao, diskRequestQueue->block,
           diskRequestQueue->buffer);
  return queue_remove(&diskRequestQueue, diskRequestQueue);
}

disk_t* sstf() {
  disk_t *aux = diskRequestQueue;

  int diff = abs(last_block - aux->block);
  disk_t *a_escolhida = aux;
  do {
    if (abs(last_block - aux->block) < diff) {
      diff = abs(last_block - aux->block);
      a_escolhida = aux;
    }
    aux = aux->next;
  } while (aux != diskRequestQueue);

  last_block = a_escolhida->block;
  blocos_percorridos += diff;
  disk_cmd(a_escolhida->operacao, a_escolhida->block, a_escolhida->buffer);
  return queue_remove(&diskRequestQueue, a_escolhida);
}

disk_t* cscan() {
  disk_t *aux = diskRequestQueue;
  disk_t *a_escolhida = aux;
  disk_t *a_escolhida_menor = aux;

  int menor_diferenca = INT_MAX;
  int menor_bloco = INT_MAX;

  do {
    int diff = aux->block - last_block;

    if (diff > 0) {
      if (diff < menor_diferenca) {
        menor_diferenca = diff;
        a_escolhida = aux;
      }
    }

    if (aux->block < menor_bloco) {
      menor_bloco = aux->block;
      a_escolhida_menor = aux;
    }

    aux = aux->next;
  } while (aux != diskRequestQueue);

  disk_t *v;
  if (menor_diferenca != INT_MAX) {
    last_block = a_escolhida->block;
    blocos_percorridos += menor_diferenca;
    v = a_escolhida;
  } else {
    last_block = a_escolhida_menor->block;
    blocos_percorridos += abs(last_block - a_escolhida_menor->block);
    v = a_escolhida_menor;
  }

  disk_cmd(v->operacao, v->block, v->buffer);
  return queue_remove(&diskRequestQueue, v);
}

void sig_handler(int signum) { ME_ACORDA_AI = 1; }

int disk_mgr_init(int *numBlocks, int *blockSize) {
  
  diskTask = (task_t *)malloc(sizeof(task_t));
  sem_create(&disk_sem, 1);
  signal(SIGUSR1, sig_handler);
  int resultado = disk_cmd(DISK_CMD_INIT, 0, 0);
  if (resultado == 0) {
    resultado = disk_cmd(DISK_CMD_BLOCKSIZE, 0, 0);
    if (resultado < 0){
      return -1;
    }
    *blockSize = resultado;
    resultado = disk_cmd(DISK_CMD_DISKSIZE, 0, 0);
    if(resultado < 0){
      return -1;
    }
    *numBlocks = resultado;
    task_create(diskTask, diskDriverBody, 0);
    return 0;
  } else if (resultado < 0) {
    return -1;
  }
}

int disk_block_read(int block, void *buffer) {
  if(sem_down(&disk_sem) != 0) {
    return -1;
  }

  disk_t *request = (disk_t *)malloc(sizeof(disk_t));
  request->block = block;
  request->buffer = buffer;
  request->task = taskExec;
  request->operacao = DISK_CMD_READ;
  request->next = NULL;
  request->prev = NULL;
  queue_append((queue_t **)&diskRequestQueue, (queue_t *)request);

  if (diskTask->state == 'S') {
    task_resume(diskTask);
  }

  if(sem_up(&disk_sem) != 0){
    return -1;
  }
  // task_sleep(disk_cmd(DISK_CMD_DELAYMAX, 0, 0));
  task_suspend(taskExec, &diskSleepQueue);
  task_yield();

  return 0;
}

int disk_block_write(int block, void *buffer) {
  if(sem_down(&disk_sem) != 0) {
    return -1;
  }

  disk_t *request = (disk_t *)malloc(sizeof(disk_t));
  request->block = block;
  request->buffer = buffer;
  request->task = taskExec;
  request->operacao = DISK_CMD_WRITE;
  request->next = NULL;
  request->prev = NULL;
  queue_append((queue_t **)&diskRequestQueue, (queue_t *)request);

  if (diskTask->state == 'S') {
    task_resume(diskTask);
  }

  if (sem_up(&disk_sem) != 0) {
    return -1;
  }

  task_suspend(taskExec, &diskSleepQueue);
  // task_sleep(disk_cmd(DISK_CMD_DELAYMAX, 0, 0));
  task_yield();

  return 0;
}