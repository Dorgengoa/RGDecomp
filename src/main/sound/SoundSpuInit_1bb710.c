#include "types.h"

typedef struct SemaParam {
    s32 currentCount;
    s32 maxCount;
    s32 initCount;
    s32 numWaitThreads;
    u32 attr;
    u32 option;
} SemaParam;

typedef struct Ent {
    u8 busy;
    u8 pad1[3];
    s32 dir;
    s32 size;
    u8 pad0C[8];
    u8 f14;
    u8 f15;
    u8 pad16[2];
    s32 addr;
    s32 a1c;
    s32 a20;
} Ent;

typedef struct Tab {
    s32 limit;
    u8 flag;
    u8 pad5[3];
    Ent ent[16];
    s32 order[16];
} Tab;

typedef struct Sub {
    u8 pad[0x38];
} Sub;

typedef struct Slot {
    s32 f0;
    s32 f4;
    s32 f8;
    u8 bC;
    u8 bD;
    u8 padE[2];
    s32 f10;
    s32 f14;
    Sub sub[5];
    s32 f130;
    s32 f134;
    u8 pad138[0x14];
    s32 f14C;
    s32 f150;
    s32 f154;
    s32 f158;
    s32 f15C;
    u8 pad160[0x80];
} Slot;

s32 CreateSema(SemaParam *);
s32 DeleteSema(s32);
void SoundSendCmd_1b6cc0();
void SoundBankFree_1b9c00(s32);
void SoundBankPartInit_1b9e90(Sub *);
void SoundBankClearIds_1b9ed0(Slot *);
void SoundSetCategoryVolume_1bb230(s32, f32);
void SoundCategoryTableInitMaybe_1bbbb0(s32);
s32 BlockHeapAllocTopAddr_1c2400(void *, s32, s32);
s32 BlockHeapAllocBottomAddr_1c2430(void *, s32, s32);
void BlockHeapInit_1c26c0(void *, s32, s32);
void BlockHeapPoolInit_1c2700(void *, void *, s32);
void BlockHeapReset_1c2770(void *);

extern s32 D_0047E1FC;
extern f32 D_0047E200;
extern s32 D_0048145C;
extern s32 D_00481460;
extern s32 D_00481464;
extern s32 D_00481470;
extern s32 D_004814A0;
extern s32 D_004814A4;
extern s32 D_004814A8;
extern s32 D_004814AC;
extern s32 D_004814B0;
extern Tab D_0049E880;
extern Slot D_0049EB10[16];
extern f32 D_004A1B50[16];
extern u8 D_004A1B90[0x30];
extern u8 D_004A1BC0[16][0x28];
extern u8 D_004A1E80[6][0x50];
extern u8 D_004A2060[0x500];

static inline void close_sema(void) {
    if (D_00481470 != 0) {
        if (D_0047E1FC != 0) DeleteSema(D_0047E1FC);
        D_00481470 = 0;
    }
}

static inline void set_vol(s32 n, f32 v) {
    if (n >= 0 && n < 16) D_004A1B50[n] = v;
}

void SoundSpuInit_1bb710(s32 arg0) {
    SemaParam sp;
    s32 i;
    s32 n3;
    s32 n;
    s32 k;
    s32 q;
    Ent *e;
    s32 size;
    s32 c;
    Slot *s;
    s32 v;
    s32 dir;


    if (D_00481470 != 0) {
        close_sema();
        for (i = 0; i < 16; i++) SoundBankFree_1b9c00(i);
    }
    if (D_00481470 == 0) {
        sp.maxCount = sp.initCount = 1;
        D_0047E1FC = CreateSema(&sp);
    }
    BlockHeapReset_1c2770(D_004A1B90);
    BlockHeapPoolInit_1c2700(D_004A1B90, D_004A2060, 0x500);
    BlockHeapInit_1c26c0(D_004A1B90, 0x5010, 0x1FAFF0);
    SoundSendCmd_1b6cc0(0x21, 2, 0, 0);
    D_004814AC = D_004814A8 = 0x7000;
    D_004814A0 = BlockHeapAllocTopAddr_1c2400(D_004A1B90, D_004814A8, 0x20000);
    D_004814A4 = BlockHeapAllocTopAddr_1c2400(D_004A1B90, D_004814AC, 0x20000);
    SoundSendCmd_1b6cc0(0x24, 3, 0, D_004814A0, D_004814A0 + D_004814A8 - 1);
    SoundSendCmd_1b6cc0(0x24, 3, 1, D_004814A4, D_004814A4 + D_004814AC - 1);
    SoundSendCmd_1b6cc0(0x21, 2, 1, 0);
    SoundSendCmd_1b6cc0(0x22, 2, 0, 4);
    SoundSendCmd_1b6cc0(0x23, 2, 0, 0x28);
    SoundSendCmd_1b6cc0(0x22, 2, 1, 0);
    SoundSendCmd_1b6cc0(0x23, 2, 1, 0);
    D_00481460 = 0;
    D_00481464 = 0;
    SoundSendCmd_1b6cc0(0xC, 2, 0x3FFF, 0x3FFF);
    D_0047E200 = 1.0f;
    v = (s32)(0x3FFF * D_0047E200);
    SoundSendCmd_1b6cc0(0xC, 2, v, v);
    D_004814B0 = 0;
    SoundCategoryTableInitMaybe_1bbbb0(arg0);

    n = 0;
    for (q = 0; q < 16; q++) {
        k = D_0049E880.order[q];
        e = &D_0049E880.ent[k];
        if (e->busy) continue;
        size = e->size;
        dir = e->dir;
        if (size < D_0049E880.limit) {
            e->size = 0;
            continue;
        }
        if (n >= 6) break;
        if (dir > 0) {
            e->addr = BlockHeapAllocBottomAddr_1c2430(D_004A1B90, size, D_0049E880.limit);
        } else if (dir < 0) {
            e->addr = BlockHeapAllocTopAddr_1c2400(D_004A1B90, size, D_0049E880.limit);
        }
        BlockHeapPoolInit_1c2700(D_004A1BC0[k], D_004A1E80[n], 0x50);
        BlockHeapInit_1c26c0(D_004A1BC0[k], e->addr, size);
        n++;
    }
    if (D_0049E880.flag) {
        c = 0;
        for (i = 0; i < 16; i++) {
            e = &D_0049E880.ent[D_0049E880.order[i]];
            if (e->busy) continue;
            if (e->f15) {
                e->a1c = c;
                e->a20 = c;
                c++;
            }
            if (e->f14) {
                e->a1c = c;
                c++;
            }
        }
    }
    for (n3 = 0; n3 < 16; n3++) {
        s = &D_0049EB10[n3];
        s->f0 = 0;
        s->f10 = 0x7F;
        s->f14 = 0;
        s->f4 = -1;
        s->f8 = -1;
        s->bC = 0;
        s->bD = 0;
        s->f14C = -1;
        s->f150 = -1;
        s->f154 = 0;
        s->f158 = 0;
        s->f15C = -1;
        SoundBankClearIds_1b9ed0(s);
        s->f134 = 0;
        s->f130 = 0;
        for (i = 0; i < 5; i++) SoundBankPartInit_1b9e90(&s->sub[i]);
        set_vol(n3, 1.0f);
        SoundSetCategoryVolume_1bb230(n3, 1.0f);
    }
    D_0048145C = 0;
    D_00481470 = 1;
}
