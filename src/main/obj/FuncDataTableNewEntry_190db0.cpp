#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
struct N190db0 {
    struct N190db0 *next;
    struct N190db0 *prev;
    s32 w8;
    s32 wC;
    struct O190db0 *obj;
    virtual void v08();
};

struct O190db0 {
    u8 pad0[0x40];
    s32 w40;
    u8 pad44[8];
    virtual void v08();
    virtual void v0C();
    virtual void v10();
};

extern "C" s32 MemStackNew_14e1b0(s32, s32);
extern "C" u8 *MemStackNew_14e230(s32, s32);

extern void *D_00470560[];
extern void *D_00470580[];
extern void *D_00470598[];
extern void *D_004705B0[];

static inline u8 *last(u8 *cur) {
    u8 *nx;
    while (cur != 0) {
        nx = *(u8 **)cur;
        if (nx == 0) {
            break;
        }
        cur = nx;
    }
    return cur;
}
extern "C" u8 *FuncDataTableNewEntry_190db0(u8 *arg0, s32 arg1, s32 arg2)
{
    u8 *p;
    u8 *obj;
    u8 *cur;
    u8 *node;
    u8 **slot;
    u8 *nx;
    void **vt;
    s32 i;
    u8 **tab;

    node = MemStackNew_14e230(0x18, arg2);
    if (node != 0) {
        *(void ***)(node + 0x14) = D_00470598;
        ((N190db0 *)node)->v08();
    }
    obj = 0;
    if (arg1 < 11) {
        p = MemStackNew_14e230(0xB0, arg2);
        if (p != 0) {
            *(void ***)(p + 0x4C) = D_004705B0;
            *(void ***)(p + 0x4C) = D_00470560;
        }
        obj = p;
    } else {
        switch (arg1) {
        case 11:
        case 12:
            p = MemStackNew_14e230(0x58, arg2);
            if (p != 0) {
                *(void ***)(p + 0x4C) = D_004705B0;
                *(void ***)(p + 0x4C) = D_00470580;
            }
            obj = p;
            break;
        }
    }
    if (obj == 0 && node == 0) {
        return 0;
    }
    ((O190db0 *)obj)->v10();
    *(u8 **)(node + 0x10) = obj;
    if (*(s32 *)(arg0 + 4) == 0) {
        *(s32 *)(arg0 + 4) = MemStackNew_14e1b0(0x34, arg2);
        if (*(s32 *)(arg0 + 4) != 0) {
            for (i = 0; i < 13; i++) {
                (*(s32 **)(arg0 + 4))[i] = 0;
            }
        }
    }
    tab = *(u8 ***)(arg0 + 4);
    if (tab == 0) {
        return 0;
    }
    if (node == 0) {
        return 0;
    }
    if (arg1 < 0 || arg1 >= 13) {
        return 0;
    }
    slot = &tab[arg1];
    cur = *slot;
    if (cur == 0) {
        *slot = node;
    } else {
        cur = last(cur);
        *(u8 **)cur = node;
        if (node != 0) {
            *(u8 **)(node + 4) = cur;
        }
    }
    p = *(u8 **)(node + 0x10);
    *(s32 *)(p + 0x40) = arg1;
    return p;
}
