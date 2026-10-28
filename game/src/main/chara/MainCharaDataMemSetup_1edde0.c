/* rgp:protos */
#define RGP_SELF_MainCharaDataMemSetup_1edde0 1
#define RGP_SELF_reset 1
#define RGP_SELF_setup 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s8 *strcpy(s8 *, const s8 *);
extern u32 strlen(const s8 *);
extern s8 D_0045B6F0[];

typedef struct { u8 d[0x58]; } E001edde0;
typedef struct {
    u8 pad0[0xE80];
    E001edde0 e[3];
    s16 hF88[3];
    u8 padF8E[0xF94 - 0xF8E];
    s32 wF94;
} O001edde0;

static inline void setup(E001edde0 *e, s32 a, s32 n)
{
    MemStackInit_14d810((s8 *)e, a, n);
    if (strlen(D_0045B6F0) < 16) {
        strcpy((s8 *)e, D_0045B6F0);
    }
}

static inline void reset(E001edde0 *e)
{
    MemStackReset_14d830((s8 *)e);
    MemStackAlign64_14d8e0((s8 *)e);
}

void MainCharaDataMemSetup_1edde0(O001edde0 *o, s32 arg1, s32 arg2, s32 arg3)
{
    s32 sz[3];
    s32 i;
    s32 n;
    s32 t;
    s32 *q;

    switch (arg1) {
    case 0:
        sz[0] = 0x11300;
        for (i = 1; i < 3; i++) {
            sz[i] = (arg3 - sz[0]) / 2;
        }
        for (i = 0; i < 3; i++) {
            setup(&o->e[i], MemStackAllocAligned64_14da10(arg2, sz[i]), sz[i]);
            reset(&o->e[i]);
            o->hF88[i] = -1;
        }
        break;
    case 1:
        o->wF94 = arg2;
        break;
    }
}
