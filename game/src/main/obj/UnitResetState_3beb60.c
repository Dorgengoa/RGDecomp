/* rgp:protos */
#define RGP_SELF_UnitResetState_3beb60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T3beb60 {
    u8 pad000[0x238];
    u8 f238;        /* 0x238 */
    u8 pad239[1];
    s16 f23A;       /* 0x23A */
    s16 f23C[2];    /* 0x23C */
    s32 f240[2];    /* 0x240 */
    s32 f248[2];
    s32 f250[2];
    s32 f258[2];
    u8 pad260[4];
    s16 f264[5][2]; /* 0x264 */
    u8 pad278[0x3E0 - 0x278];
    s32 f3E0;       /* 0x3E0 */
    s16 f3E4;
    s16 f3E6;
    s32 f3E8[8];    /* 0x3E8 */
    u8 a0 : 1;      /* 0x408 */
    u8 a1 : 1;
    u8 a2 : 1;
    u8 a3 : 1;
    u8 a4 : 1;
    u8 a5 : 1;
    u8 a6 : 1;
    u8 a7 : 1;
    u8 b0 : 1;      /* 0x409 */
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
    u8 b6 : 1;
    s16 f40A;       /* 0x40A */
    s32 f40C;       /* 0x40C */
} T3beb60;

/*rgp*/

s32 UnitResetState_3beb60(T3beb60 *p)
{
    s32 i;
    s32 j;
    s32 k;

    if (UnitBaseResetState_3b8740() == 0) {
        return 0;
    }
    p->f238 = 0;
    p->f23A = -1;
    for (i = 0; i < 2; i++) {
        p->f23C[i] = 0;
        p->f240[i] = 0;
        p->f248[i] = 0;
        p->f250[i] = 0;
        p->f258[i] = 0;
        for (j = 0; j < 5; j++) {
            p->f264[j][i] = 0;
        }
    }
    p->f3E0 = 0;
    p->f3E4 = 0;
    p->f3E6 = 0;
    for (k = 0; k < 8; k++) {
        p->f3E8[k] = 0;
    }
    p->a0 = 1;
    p->a1 = 0;
    p->a2 = 0;
    p->a3 = 0;
    p->a4 = 0;
    p->a5 = 0;
    p->b0 = 0;
    p->a6 = 0;
    p->b2 = 0;
    p->b3 = 0;
    p->b4 = 0;
    p->a7 = 0;
    p->b5 = 0;
    p->b6 = 0;
    p->f40C = 0;
    p->f40A = 1;
return 1;
}
