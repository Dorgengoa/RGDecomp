/* rgp:protos */
#define RGP_SELF_SoundStreamSlotQueueOpen_1be8a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void WaitSema(s32);
void SignalSema(s32);
void strcpy(s8 *, s8 *);
u32 strlen(s8 *);
struct Lock {
    volatile s32 *s;
};

struct Obj {
    u8 pad0[0xC];
    s32 sema;
    s8 *name;
    u8 val;
    u8 pad15[0x50 - 0x15];
    u8 flag;
    u8 pad51[3];
    u32 head;
    u32 tail;
    u8 slots[24];
};

u8 SoundStreamSlotQueueOpen_1be8a0(struct Obj *arg0, s8 *arg1, u8 arg2)
{
    u8 r;
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk __attribute__((aligned(16)));
    volatile struct Lock lk2 __attribute__((aligned(16)));

    if (strlen(arg1) >= 0x100) {
        return 0;
    }
    {
        t = &arg0->sema;
        v = *t;
        lk.s = t;
        if (v > 0) {
            WaitSema(*t);
        }
        if (*arg0->name != 0) {
            t = lk.s;
            if (*t > 0) {
                SignalSema(*t);
            }
            return 0;
        }
        strcpy(arg0->name, arg1);
        arg0->val = arg2;
        t = lk.s;
        if (*t > 0) {
            SignalSema(*t);
        }
    }
    {
        t = &arg0->sema;
        v = *t;
        lk2.s = t;
        if (v > 0) {
            WaitSema(*t);
        }
        if (arg0->flag == 0 && arg0->head == arg0->tail) {
            r = 0;
        } else {
            arg0->slots[arg0->tail] = 1;
            arg0->tail = (arg0->tail + 1) % 24;
            arg0->flag = 0;
            r = 1;
        }
        t = lk2.s;
        if (*t > 0) {
            SignalSema(*t);
        }
        return r;
    }
}
