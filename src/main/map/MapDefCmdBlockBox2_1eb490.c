#include "types.h"

typedef struct P1 {
    u8 pad0[0x3A];
    s16 n;          /* 0x3A */
    u8 pad3C[8];
    u8 *tbl;        /* 0x44 */
} P1;

typedef struct P2 {
    u8 pad0[0xC];
    u8 *tbl;        /* 0x0C */
    u8 pad10[2];
    s16 n;          /* 0x12 */
} P2;

extern P1 *MapAreaDefGetRecTable_1dcf20(s32);
extern P2 *MapBlockGetInfo_1e00b0(u8 *);
extern void AreaBoxCalc_1e9650(u8 *);
extern void AreaBoxSetCorner1_1e9790(u8 *, f32, f32, f32);
extern void AreaBoxSetCorner0_1e97a0(u8 *, f32, f32, f32);
extern f32 ScriptArgGetFloat_1ecba0(u8 *);
extern f32 D_0045B080[];
extern s32 D_004818F8;
extern s32 D_004818FC;
extern s16 D_00481904;
extern s16 D_0048190C;

s32 MapDefCmdBlockBox2_1eb490(u8 *arg0, s32 arg1)
{
    P1 *p1;
    P2 *p2;
    u8 *t;
    f32 s;
    f32 a;
    f32 b;

    if (arg1 != 6) {
        return 1;
    }
    if (D_004818FC == 0 || D_004818F8 == 0) {
        return 1;
    }
    p1 = MapAreaDefGetRecTable_1dcf20(D_004818FC);
    if (p1->tbl == 0 || p1->n <= D_00481904) {
        return 1;
    }
    p2 = MapBlockGetInfo_1e00b0(p1->tbl + D_00481904 * 0xCC);
    if (p2->tbl == 0 || p2->n <= D_0048190C) {
        return 1;
    }
    t = p2->tbl + D_0048190C * 0x4C;
    s = D_0045B080[0];
    a = s * ScriptArgGetFloat_1ecba0(arg0);
    b = s * ScriptArgGetFloat_1ecba0(arg0 + 8);
    AreaBoxSetCorner0_1e97a0(t, a, b, s * ScriptArgGetFloat_1ecba0(arg0 + 0x10));
    a = s * ScriptArgGetFloat_1ecba0(arg0 + 0x18);
    b = s * ScriptArgGetFloat_1ecba0(arg0 + 0x20);
    AreaBoxSetCorner1_1e9790(t, a, b, s * ScriptArgGetFloat_1ecba0(arg0 + 0x28));
    AreaBoxCalc_1e9650(t);
    D_0048190C++;
    return 1;
}
