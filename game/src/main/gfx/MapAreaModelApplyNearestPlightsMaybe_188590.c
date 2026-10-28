/* rgp:protos */
#define RGP_SELF_MapAreaModelApplyNearestPlightsMaybe_188590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E188590 {
    u8  pad00[0x4C];
    void *f4C;
    u8  pad50[0x60 - 0x50];
    u8  m60[0x10];
    f32 f70;
    u8  pad74[0xB0 - 0x74];
} E188590;

typedef struct T188590 {
    u8  pad0000[0x1678];
    s32 f1678;
} T188590;

extern s8 D_00481234;
extern E188590 D_0049C900[];
extern u8 D_0049CE80[];
extern u8 D_004705B0[];
extern u8 D_00470560[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapAreaModelApplyNearestPlightsMaybe_188590(T188590 *self, s32 a1, s32 a2)
{
    E188590 *p;
    E188590 *e;
    s32 n;
    s32 i;
    f32 b[4] __attribute__((aligned(16)));
    f32 a[4] __attribute__((aligned(16)));

    if (D_00481234 == 0) {
        p = D_0049C900;
        do {
            p->f4C = D_004705B0;
            p->f4C = D_00470560;
            p++;
        } while (p < (E188590 *)D_0049CE80);
        D_00481234 = 1;
    }
    n = FuncDataTableFindNearestPlightsMaybe_190220((u8 *)self + 0x1664, a1, D_0049C900, 4, a2, 0);
    for (i = 0; i < n; i++) {
        e = &D_0049C900[i];
        VecScale_13be00(b, e->m60, LightFlickerScale_18e2c0(e, self->f1678));
        NodeGetTranslation_186650(e, a);
        LightStateSetPointLight_15ca80(3 - i, a, b, e->f70);
    }
    return n;
}
