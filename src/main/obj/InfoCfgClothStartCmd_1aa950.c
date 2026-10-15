#include "types.h"

typedef struct A_001aa950 {
    u8 pad0[0x204];
    s32 f204;
    s32 f208;
} A_001aa950;

extern struct { A_001aa950 *v; s32 pad[3]; } D_0049D418;
extern struct { void *v; s32 pad[3]; } D_0049D398;
extern struct { s32 v; s32 pad[3]; } D_0049D434;
extern s32 VariantGetInt_15f780(void *);
extern void *MemStackNew_14e1b0(s32, void *);
extern s32 ConstructNewArray_100710(void *, void *, s32, s32, s32);
extern void DynClothDefCtor_1aaa60(void);

s32 InfoCfgClothStartCmd_1aa950(void *arg)
{
    A_001aa950 *a;
    void *b;
    s32 n;
    s32 ok;
    s32 v;
    void *p;
    s32 r;
    a = D_0049D418.v;
    b = D_0049D398.v;
    if (a == 0) goto zero;
    if (b != 0) goto g1;
zero:
    return 0;
g1:
    n = VariantGetInt_15f780(arg);
    if (n > 0) goto g2;
    return 0;
g2:
    if (n == 0) goto chk;
    p = MemStackNew_14e1b0(368 * n + 0x10, b);
    r = ConstructNewArray_100710(p, DynClothDefCtor_1aaa60, 0, 0x170, n);
    a->f208 = r;
    if (r == 0) {
        a->f204 = 0;
    } else {
        a->f204 = n;
    }
chk:
    ok = a->f208;
    if (ok == 0) goto zok1;
    v = a->f204;
    if (v != 0) goto g3;
zok1:
    ok = 0;
    goto done;
g3:
    if (v > 0) goto done;
    ok = 0;
done:
    if (ok != 0) goto g4;
    return 0;
g4:
    D_0049D434.v = 0;
    return 1;
}
