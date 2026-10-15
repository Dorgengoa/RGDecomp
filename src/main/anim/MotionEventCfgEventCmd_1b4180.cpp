#include "types.h"

extern "C" {
#define F(expr, type, off) (*(type *)((s8 *)(expr) + (off)))

extern char *SlotGetInt_15f720(void *);
extern f32 VariantGetFloat_15f740(void *);
extern s8 *MemStackNew_14e230(s32, s32);
extern s32 NamedRecFindIndex_173a00(s8 *, char *);
extern s32 NamedRecGet_173ab0(s8 *, s32);
extern void MotionEventBaseCtor_1b1d70(s8 *);
extern void MotionEventSetEndRatio_1b1c20(s8 *, f32);
extern void MotionEventSetStartRatio_1b1cc0(s8 *, f32);
extern void MotionEventBlockAppendEvent_1b2370(s32, s32, s8 *);
extern int strcmp(const char *, const char *);
extern char D_0045AB20[];
extern char D_0045AB48[];
extern char D_0045AB58[];
extern char D_0045AB60[];
extern char D_0045AB68[];
extern u8 D_00471030[0x400];
extern u8 D_00471080[0x400];
extern u8 D_004710A0[0x400];
extern u8 D_004710C0[0x400];

typedef struct Self {
    u8 pad0[0x30];
    s32 heap;
    u8 pad34[4];
    s8 *tbl;
    s32 unk3C;
    s8 *cur;
    s8 *a;
    s8 *b;
    s8 *c;
    s8 *d;
} Self;
s32 MotionEventCfgEventCmd_1b4180(s8 *arg0, s32 arg1, Self **arg2) {
    Self *self;
    s32 heap;
    char *type;
    char *name;
    s8 *p;
    bool flag;
    s32 id;

    self = *arg2;
    heap = self->heap;
    self->cur = 0;
    self->a = 0;
    self->b = 0;
    self->c = 0;
    self->d = 0;
    type = SlotGetInt_15f720(arg0);
    name = SlotGetInt_15f720(arg0 + 8);
    if (type == 0 || name == 0) {
        return 0;
    }
    flag = false;
    id = 0;
    if (strcmp(name, D_0045AB48) == 0) {
        flag = true;
    } else {
        s8 *tbl = self->tbl;
        if ((id = NamedRecGet_173ab0(tbl, NamedRecFindIndex_173a00(tbl, name))) == 0) {
            return -1;
        }
    }
    if (strcmp(type, D_0045AB20) == 0) {
        p = MemStackNew_14e230(0x38, heap);
        if (p != 0) {
            MotionEventBaseCtor_1b1d70(p);
            F(p, void *, 0x24) = (void *)D_004710C0;
            F(p, s32, 0x28) = 0;
            F(p, s8, 0x30) = 0;
            F(p, s32, 0x2C) = -1;
        }
        self->a = p;
        self->cur = p;
    } else if (strcmp(type, D_0045AB58) == 0) {
        p = MemStackNew_14e230(0x30, heap);
        if (p != 0) {
            MotionEventBaseCtor_1b1d70(p);
            F(p, void *, 0x24) = (void *)D_004710A0;
            F(p, s32, 0x28) = 0;
            F(p, s32, 0x2C) = -1;
        }
        self->b = p;
        self->cur = p;
    } else if (strcmp(type, D_0045AB60) == 0) {
        p = MemStackNew_14e230(0x34, heap);
        if (p != 0) {
            MotionEventBaseCtor_1b1d70(p);
            F(p, void *, 0x24) = (void *)D_00471080;
            F(p, s32, 0x28) = 0;
            F(p, s32, 0x30) = F(p, s32, 0x2C) = 1;
        }
        self->c = p;
        self->cur = p;
    } else if (strcmp(type, D_0045AB68) == 0) {
        p = MemStackNew_14e230(0x38, heap);
        if (p != 0) {
            MotionEventBaseCtor_1b1d70(p);
            F(p, void *, 0x24) = (void *)D_00471030;
            F(p, s32, 0x30) = 0;
            F(p, s32, 0x28) = 0;
            F(p, s32, 0x2C) = 0;
            F(p, s32, 0x30) = 0;
            F(p, s8, 0x35) = 0;
            F(p, s8, 0x34) = 0;
        }
        self->d = p;
        self->cur = p;
    } else {
        return 0;
    }
    p = self->cur;
    if (p == 0) {
        return -1;
    }
    MotionEventBlockAppendEvent_1b2370(self->unk3C, heap, p);
    F(self->cur, s8, 0x10) = flag;
    F(self->cur, s32, 0x14) = id;
    MotionEventSetStartRatio_1b1cc0(self->cur, VariantGetFloat_15f740(arg0 + 0x10));
    if (arg1 >= 4) {
        MotionEventSetEndRatio_1b1c20(self->cur, VariantGetFloat_15f740(arg0 + 0x18));
    }
    return 1;
}
}
