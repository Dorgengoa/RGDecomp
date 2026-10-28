/* SPDX-License-Identifier: CC0-1.0 */
/* Game-side view of the native threads service (src/native/threads/rg_threads.h,
 * docs/NATIVE-THREADS.md), for the overrides of thread/timing game functions.  Plain C
 * types only, so it can be included next to the game's types.h. */
#ifndef RG_PORT_NATIVE_THREADS_H
#define RG_PORT_NATIVE_THREADS_H

#ifdef __cplusplus
extern "C" {
#endif

#define RG_THREADS_HLE     0
#define RG_THREADS_NATIVE  1
#define RG_THREADS_SERVICE 2
#define RG_THREADS_FRAME   3

int rg_threads_mode(void);
int rg_threads_service(int tid, int (*wait)(void *arg), void (*step)(void *arg), int allowed,
                       const char *name);

/* convertible thread (see rg_threads.h): registered from a constructor in the
 * override of the thread's entry */
typedef struct rg_thread_conv {
    void       *entry;
    const char *name;
    int  (*wait)(void *arg);
    void (*step)(void *arg);
    void (*exit_tail)(void *arg);
    int   exit_delete;
    int  (*allowed)(void);
    int   order;
    int   sync;
    void (*point)(void *arg);
    void (*drain)(void);
    void (*prologue)(void *arg);
    int   anywhere;
} rg_thread_conv;
void rg_threads_convertible(const rg_thread_conv *c);
#define RG_CONV_READY 0x7FFFFFFF /* wait(): runnable now, no semaphore to wait on */
void rg_threads_flow(void *entry, const char *name); /* stays a game coroutine (native mode) */

/* frame driver */
int  rg_frame_native(void);            /* the frame driver is on (RG_THREADS=native or frame) */
int  rg_threads_kernel_native(void);   /* RG_THREADS=native (no EE scheduler) */
void rg_frame_point(void);
int  rg_frame_is_driven(void *entry);  /* a thread with this entry is parked for the driver */
int  rg_frame_delay(unsigned int usec);
void rg_frame_wait_cond(int (*cond)(void *arg), void *arg, const char *what);
void rg_frame_frame_wait(void);        /* a flow's frame wait (main: one logic tick, paced mode) */

#ifdef __cplusplus
}
#endif
#endif
