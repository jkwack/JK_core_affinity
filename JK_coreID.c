#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
/* Borrowed from util-linux-2.13-pre7/schedutils/taskset.c */
static char *cpuset_to_cstr(cpu_set_t *mask, char *str)
{
 char *ptr = str;
 int i, j, entry_made = 0;
 for (i = 0; i < CPU_SETSIZE; i++) {
 if (CPU_ISSET(i, mask)) {
 int run = 0;
 entry_made = 1;
 for (j = i + 1; j < CPU_SETSIZE; j++) {
 if (CPU_ISSET(j, mask)) run++;
 else break;
 }
 if (!run)
 sprintf(ptr, "%d,", i);
 else if (run == 1) {
 sprintf(ptr, "%d,%d,", i, i + 1);
 i++;
 } else {
 sprintf(ptr, "%d-%d,", i, i + run);
 i += run;
 }
 while (*ptr != 0) ptr++;
 }
 }
 ptr -= entry_made;
 *ptr = 0;
 return(str);
}

/* Based on Cray's original xthi.c */
void core_affinity_(char *clbuf)
{
 cpu_set_t coremask;
// n_clbuf = 7 * CPU_SETSIZE;
// printf("%d\n",n_clbuf);
 memset(clbuf, 0, sizeof(clbuf));
// memset(clbuf, 0, n_clbuf);
 (void)sched_getaffinity(0, sizeof(coremask), &coremask);
 cpuset_to_cstr(&coremask, clbuf);
}

