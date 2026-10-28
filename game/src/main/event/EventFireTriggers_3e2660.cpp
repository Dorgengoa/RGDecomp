/* rgp:protos */
#line 1
#include "types.h"

extern "C" {
typedef struct Elem { u8 pad[0x38]; } Elem;
typedef struct Query { s32 a; s32 b; Elem arr[64]; } Query;
typedef struct Iter { s32 a; s32 b; } Iter;
typedef struct Tmp { s32 a; s32 b; s32 c; s32 d; } Tmp;
typedef struct Node {
    u8 pad0[2];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 fpad : 5;
    u8 pad3;
    s16 h4;
    s16 h6;
    u8 pad8[2];
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[4];
    s32 w14;
    s32 w18;
    s32 w1C;
} Node;
typedef struct Ev {
    s16 h0;
    u8 b2;
    u8 b3;
    u8 pad4[0x10];
    s16 h14;
} Ev;
typedef struct Cam { u8 pad[4]; s16 h4; u8 pad6[6]; s16 hC; } Cam;
typedef struct Own { u8 pad[0x24C]; u8 busy : 1; } Own;
typedef struct Sys { u8 pad[0x18]; Cam *cam; u8 pad1C[4]; Own *own; } Sys;

extern s32 GetGameMode_1f59c0(void);
extern s32 VariantIsZero_36ed10(s32);
extern void VariantInit_36ff00(Elem *);
extern Node *IterNext_370040(Iter *);
extern void IterInit_370170(Iter *, Tmp *, int, int);
extern s32 ScriptExecOpStream_3dffa0(Query *, s16, s32, Ev *);
extern void VariantPoolReset_3e01f0(Query *);
extern void RowRangeIterCtor_4288a0(Tmp *, Sys *, s32, u8 *);
extern void EventPendingPacketSet_3e2610(Node *, Ev *);
extern s32 ActionPacketClear_3e3e90(void *);
extern s32 D_004801F4;
extern u8 D_0048396C;
extern Sys *D_00483990;
extern u8 D_00483998;
extern Node *D_0048399C;
extern u8 D_004E9740[];
}

extern "C" s32 EventFireTriggers_3e2660(Ev *ev, u8 *flag)
{
    Tmp tmp __attribute__((aligned(16)));
    Iter it[2] __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Query)) + (0xe0d)];
    s32 kind;
    bool want;
    u8 alt;
    s32 x;
    s32 y;
    s32 n;
    Node *o;
    Elem *p;
    s32 r;

    if (D_00483990 == 0) return 0;
    if (ev->h0 <= 0) return 0;
    if (ev->b2 == 0xFF) return 0;
    if (D_00483998 == 0) return 0;
    kind = GetGameMode_1f59c0();
    want = true;
    if (ev->b2 == 2 && ev->b3 == 0x16) want = false;
    if (ev->b2 == 4 && ev->b3 == 0x18) {
        switch (kind) {
        case 0x14:
        case 0x13:
        case 0x11:
        case 7:
        case 6:
            break;
        default:
            return 0;
        }
        if (D_004801F4 == ev->h14) return 0;
        D_004801F4 = ev->h14;
    } else {
        D_004801F4 = -1;
    }
    x = D_00483990->cam->h4;
    y = D_00483990->cam->hC;
    alt = D_00483990->own->busy;
    if (kind == 7 || kind == 0x11) alt = 1;
    if (ev->b2 == 0x12) alt = 0;
    if (ev->b2 == 3 && ev->b3 == 0x3C) alt = 0;
    p = (*(Query *)(rgp_blk1 + 0x0)).arr;
    do {
        VariantInit_36ff00(p);
        p++;
    } while (p < (*(Query *)(rgp_blk1 + 0x0)).arr + 64);
    VariantPoolReset_3e01f0(&(*(Query *)(rgp_blk1 + 0x0)));
    if (flag != 0) *flag = 0;
    n = 0;
    RowRangeIterCtor_4288a0(&tmp, D_00483990, ev->h0, &ev->b2);
    IterInit_370170(&it[1], &tmp, 0, 0);
    while (o = IterNext_370040(&it[1]), o != 0) {
        if (o->h4 > 0 && o->h4 != x) continue;
        if (o->h6 > 0 && o->h6 != y) continue;
        if (want) {
            if (!alt) {
                if (!o->f0) continue;
            } else {
                if (!o->f1 && !o->f2) continue;
                if (o->f2 && D_0048399C != 0) continue;
            }
        }
        if (o->hA > 0 && o->w14 != 0) {
            r = ScriptExecOpStream_3dffa0(&(*(Query *)(rgp_blk1 + 0x0)), o->hA, o->w14, ev);
            if (r == 0 || VariantIsZero_36ed10(r) != 0) continue;
        }
        if (o->hC > 0 && o->w18 != 0) {
            r = ScriptExecOpStream_3dffa0(&(*(Query *)(rgp_blk1 + 0x0)), o->hC, o->w18, ev);
            if (r == 0 || VariantIsZero_36ed10(r) != 0) continue;
        }
        if (want && alt && o->f2) {
            EventPendingPacketSet_3e2610(o, ev);
            continue;
        }
        if (o->hE > 0 && o->w1C != 0) {
            ScriptExecOpStream_3dffa0(&(*(Query *)(rgp_blk1 + 0x0)), o->hE, o->w1C, ev);
            if (D_0048396C != 0 && flag != 0) *flag = 1;
            if (D_0048399C == o) {
                D_0048399C = 0;
                ActionPacketClear_3e3e90(D_004E9740);
            }
        }
        n++;
    }
    return n;
}
