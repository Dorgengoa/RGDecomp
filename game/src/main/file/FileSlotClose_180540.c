/* rgp:protos */
#define RGP_SELF_FileSlotClose_180540 1
#define RGP_SELF_get 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 m0;
    u8 m1;
    u8 m2;
    u8 m3;
    s32 m4;
    u8 pad8[0x64];
    s32 m6C;
    s32 m70;
    u8 pad74[4];
    u8 m78;
    u8 pad79[3];
} Ent;

extern s32 sceClose_11bbb8(s32);
extern void SignalSema(s32);
extern void WaitSema(s32);
extern s32 D_0047E028;
extern s32 D_0047E02C;
extern s32 D_004811C4;
extern Ent D_0049B100[12];

static inline Ent *get(s32 i)
{
    if (i < 0 || i >= 12) {
        return NULL;
    }
    if (D_0049B100[i].m0 == 0) {
        return NULL;
    }
    if (D_0049B100[i].m78 != 0) {
        return NULL;
    }
    return &D_0049B100[i];
}

s32 FileSlotClose_180540(s32 arg0)
{
    Ent *p;
    s32 r;
    s32 u;

    p = get(arg0);
    if (p == NULL) {
        u = -1;
    } else {
        switch (p->m1) {
        case 0:
            if (D_0047E028 >= 0) {
                WaitSema(D_0047E028);
            }
            D_004811C4++;
            r = sceClose_11bbb8(p->m4);
            if (D_0047E028 >= 0) {
                SignalSema(D_0047E028);
            }
            D_004811C4--;
            break;
        case 2:
        case 4:
        case 1:
            r = 0;
            break;
        default:
            r = -1;
            break;
        }
        u = r;
    }
    if (D_0047E02C >= 0) {
        WaitSema(D_0047E02C);
    }
    p = get(arg0);
    if (p != NULL) {
        p->m3 = 0;
        p->m2 = 0;
        p->m1 = 0;
        p->m0 = 0;
        p->m6C = 0;
        p->m70 = 1;
        p->m78 = 0;
    }
    if (D_0047E02C >= 0) {
        SignalSema(D_0047E02C);
    }
    return u;
}
