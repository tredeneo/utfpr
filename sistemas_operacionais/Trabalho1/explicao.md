```
void tratador(int signum) {
  if (taskExec->id != taskDisp.id && taskExec != NULL) {
    if (taskExec->quantum == 0) {
      task_yield();
    }
    taskExec->quantum--;
    taskExec->timer++;
  }
  global_timer++;
}
```

```taskExec->id != taskDisp.id && taskExec != NULL```
se tiver terefa e não for o dispacher

