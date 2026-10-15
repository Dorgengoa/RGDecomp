#include "types.h"

typedef struct E_0016f950 {
    s32 f0;
    u8 pad4[32];
} E_0016f950;

typedef struct P_0016f950 {
    s32 f0;
    E_0016f950 *f4;
} P_0016f950;

extern P_0016f950 *D_00481194;
extern E_0016f950 *D_00481198;
extern s32 D_004811A4;
extern void *D_0048118C;
extern void *SlotGetInt_15f720(void *);
extern s32 MemStackStrDup_14cff0(void *, void *);

s32 AmixerCfgClipCmd_16f950(void *arg)
{
    P_0016f950 *p;
    E_0016f950 *e;
    void *t;
    s32 i;
    p = D_00481194;
    if (p != 0) goto g1;
    return 0;
g1:
    i = D_004811A4;
    if (i < 0) goto zero;
    if (i < p->f0) goto ok;
zero:
    e = 0;
    goto out;
ok:
    e = &p->f4[i];
out:
    D_00481198 = e;
    if (e != 0) goto g2;
    return 0;
g2:
    t = SlotGetInt_15f720(arg);
    D_00481198->f0 = MemStackStrDup_14cff0(t, D_0048118C);
    D_004811A4 = D_004811A4 + 1;
    return 1;
}
