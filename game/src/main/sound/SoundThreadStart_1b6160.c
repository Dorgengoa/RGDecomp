/* rgp:spin */ extern void rg_spin_hint(unsigned int); extern void rg_spin_halt(unsigned int);
#line 1
/* rgp:protos */
#define RGP_SELF_SoundThreadStart_1b6160 1
#include "port/game_protos.h"
#line 1
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

s32 CreateSema(Sema *);
s32 CreateThread(Thread *);
s32 StartThread_1176e0(s32, s32);
extern s32 D_0047E1F4;
extern s32 D_0048144C;
extern s32 D_00481450;
extern s32 D_00481454;
extern s8 D_00481458;
extern s32 D_00485170;
extern u8 D_0049D570[];
extern s8 D_0049DD70[];
extern s32 D_0049DD74[];
extern s32 D_0049DD78[];
/*rgp*/

void SoundThreadStart_1b6160(s32 arg0)
{
    Sema s __attribute__((aligned(16)));
    Thread t __attribute__((aligned(16)));

    D_0048144C = -1;
    D_00481450 = -1;
    D_0049DD70[0] = 1;
    D_0049DD74[0] = 0;
    D_00481458 = 1;
    D_0049DD78[0] = 0;
    s.max_count = 1;
    s.init_count = 0;
    s.option = 0;
    D_00481450 = CreateSema(&s);
    s.init_count = 1;
    D_0048144C = CreateSema(&s);
    t.stack_size = 0x800;
    t.gp_reg = &D_00485170;
    t.initial_priority = arg0;
    t.func = SoundThreadMain_1b6260;
    t.stack = D_0049D570;
    D_00481454 = CreateThread(&t);
    StartThread_1176e0(D_00481454, 0);
    if ((D_0048144C < 0) || (D_0048144C < 0) || (D_00481454 < 0)) {
        do {
        } while ((D_0047E1F4 != 0) && (rg_spin_halt(0x001B6230), 1));
    }
}
