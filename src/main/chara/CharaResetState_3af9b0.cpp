#include "types.h"

class Obj3af9b0 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    u8 pad04[0x24];
};

struct T3af9b0 {
    u8 pad000[0x1D4];
    s16 f1D4;           /* 0x1D4 */
    s16 f1D6;
    u8 pad1D8[0x234 - 0x1D8];
    u8 a0 : 1;          /* 0x234 */
    u8 a1 : 1;
    u8 a2 : 1;
    u8 a3 : 1;
    u8 a4 : 1;
    u8 pad235[3];
    s32 f238;           /* 0x238 */
    u8 c0 : 1;          /* 0x23C */
    u8 pad23D[1];
    s16 f23E;           /* 0x23E */
    s16 f240;
    s16 f242;
    s16 f244;
    s16 f246;
    s16 x248[2][2];     /* 0x248 */
    s32 x250[2][2];     /* 0x250 */
    s32 x260[2][2];
    s32 x270[2][2];
    s32 x280[2][2];
    u8 pad290[0x2E0 - 0x290];
    s64 x2E0[2];        /* 0x2E0 */
    u8 f2F0[0x308 - 0x2F0];
    Obj3af9b0 objs[10]; /* 0x308 */
    s32 f498;           /* 0x498 */
    s16 f49C;
    s16 f49E;
    u8 pad4A0[0x4AC - 0x4A0];
    u8 f4AC;            /* 0x4AC */
    u8 pad4AD[0x4B4 - 0x4AD];
    u8 b0 : 1;          /* 0x4B4 */
    u8 b1 : 1;
    u8 pad4B5[3];
    s32 f4B8;           /* 0x4B8 */
    u8 pad4BC[1];
    u8 f4BD;            /* 0x4BD */
    u8 f4BE;
    u8 f4BF;
};

extern "C" u8 UnitBaseResetState_3b8740(void);
extern "C" void Fill3U64Default_3b0960(void *);

extern "C" s32 CharaResetState_3af9b0(T3af9b0 *p)
{
    s32 i;
    s32 j;
    s32 k;
    s32 m;

    if (UnitBaseResetState_3b8740() == 0) {
        return 0;
    }
    p->a0 = 0;
    p->a1 = 0;
    p->a2 = 0;
    p->b0 = 0;
    p->b1 = 0;
    p->a3 = 0;
    p->a4 = 0;
    p->f238 = 0x54;
    p->c0 = 0;
    p->f23E = -1;
    p->f240 = -1;
    p->f242 = -1;
    p->f244 = -1;
    p->f246 = 0;
    p->f4B8 = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            p->x248[i][j] = 0;
            p->x250[i][j] = 0;
            p->x260[i][j] = 0;
            p->x270[i][j] = 0;
            p->x280[i][j] = 0;
        }
    }
    for (m = 0; m < 10; m++) {
        p->objs[m].v5();
    }
    for (k = 0; k < 2; k++) {
        p->x2E0[k] = 0;
    }
    Fill3U64Default_3b0960(&p->f2F0);
    p->f498 = 0;
    p->f49C = 0;
    p->f49E = -1;
    p->f1D6 = 0;
    p->f1D4 = 0;
    p->f4AC = 0;
    p->f4BD = 0;
    p->f4BE = 0;
    p->f4BF = 0;
    return 1;
}
