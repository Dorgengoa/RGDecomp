/* PARKED s17b: not attempted. SDK semaphore+thread bring-up fn (CreateSema x3,
   CreateThread, StartThread_1176e0, SoundThreadStart_1b6160) with a ~0x27-element zero-fill
   loop and several D_0049D55x flag stores. Similar shape to SoundQueueCmd_1b6d60 and
   src/s12p/SoundThreadStart_1b6160.c (already matched) -- start from that file's style
   for the extern signatures/types. Not attempted this lane, throughput
   budget spent elsewhere. */
/* s49m: MATCH */
#include "types.h"

typedef struct {
    s32 count;
    s32 max_count;
    s32 init_count;
    s32 wait_threads;
    u32 attr;
    u32 option;
} Sema;

typedef struct {
    s32 status;
    void *func;
    void *stack;
    s32 stack_size;
    void *gp_reg;
    s32 initial_priority;
    s32 current_priority;
    u32 attr;
    u32 option;
    s32 pad[3];
} Thread;

typedef struct {
    s32 priority;
    void *stack;
    u32 stack_size;
    u8 flag;
} Params;

extern s32 CreateSema(Sema *);
extern s32 DeleteSema(s32);
extern s32 CreateThread(Thread *);
extern s32 StartThread_1176e0(s32, s32 *);
extern void SoundThreadStart_1b6160(s32);
extern void SoundCmdWorkerThread_1b6c10(void);
extern s32 D_00481428;
extern s32 D_0048142C;
extern s32 D_00481430;
extern s32 D_00481434;
extern s32 D_00481438;
extern s32 D_0048143C;
extern s32 D_00481440;
extern s32 D_00481444;
extern s32 D_00481448;
extern s32 D_00485170;
extern u8 D_0049D540[];
extern u8 D_0049D552[];
extern u8 D_0049D55B[];
extern u8 D_0049D55C[];
extern u8 D_0049D55D[];
extern u8 D_0049D55E[];
extern u8 D_0049D55F[];
extern u8 D_0049D560[];

s32 SoundSysInit_1b6f70(Params *arg)
{
    Sema s;
    Thread t;
    s32 i;

    if (D_00481428 != 0) {
        return 0;
    }
    if (arg->stack == 0) {
        return 0;
    }
    if (arg->stack_size < 0x2000) {
        return 0;
    }
    for (i = 0; i < 0x27; i++) {
        D_0049D540[i] = 0;
    }
    if (arg->flag != 0) {
        D_0049D552[0] = 1;
        D_0049D55B[0] = 1;
        D_0049D55C[0] = 1;
        D_0049D560[0] = 1;
        D_0049D55D[0] = 1;
        D_0049D55E[0] = 1;
        D_0049D55F[0] = 1;
    }
    D_0048142C = -1;
    D_00481430 = -1;
    D_00481434 = -1;
    D_00481438 = -1;
    D_0048143C = -1;
    D_00481440 = 0;
    D_00481444 = 0;
    D_00481448 = 0;
    s.max_count = 1;
    s.init_count = 0;
    s.option = 0;
    D_0048142C = CreateSema(&s);
    D_00481434 = CreateSema(&s);
    s.init_count = 1;
    D_00481430 = CreateSema(&s);
    if (D_0048142C < 0 || D_00481434 < 0 || D_00481430 < 0) {
        if (D_0048142C >= 0) {
            DeleteSema(D_0048142C);
        }
        if (D_00481434 >= 0) {
            DeleteSema(D_00481434);
        }
        if (D_00481430 >= 0) {
            DeleteSema(D_00481430);
        }
        return 0;
    }
    t.stack_size = arg->stack_size;
    t.gp_reg = &D_00485170;
    t.func = SoundCmdWorkerThread_1b6c10;
    t.stack = arg->stack;
    t.initial_priority = arg->priority;
    D_0048143C = arg->priority;
    D_00481438 = CreateThread(&t);
    if (D_00481438 < 0) {
        return 0;
    }
    StartThread_1176e0(D_00481438, &D_0048142C);
    SoundThreadStart_1b6160(arg->priority - 1);
    D_00481428 = 1;
    return 1;
}
