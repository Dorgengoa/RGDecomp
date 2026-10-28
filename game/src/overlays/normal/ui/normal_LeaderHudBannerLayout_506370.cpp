/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x00506370 -- lay out the 0x3C-family caption box.  Stages a cleared
 * 12-byte block plus two Vec3 copies from gp small data on the stack, fills
 * the 9 fields of the widget cell, then measures the string through a C++
 * VIRTUAL (`lw $25,0x470($25) / jalr $25`, vptr offset 0 so slot index
 * (0x470-8)/4 = 282) and converts the accumulated height back to an int.
 *
 * The byte-clear loop at sp+0x90 NULL-CHECKS the address of a local, which is
 * never hand-written C -- it is a block-scoped `= {0}` array initialiser
 * (levers.d/mwcc-array-initialiser-clear-loop).
 * The 4 far s16 globals are INCOMPLETE extern arrays so they take %hi/%lo;
 * the 6 Vec3 sources are separate f32 scalars so each stays under the
 * small-data threshold and comes out gp-relative.
 * m2c invented four arguments for func_1FEDE0 out of the argument registers
 * the preceding store sequence happened to leave live -- it takes none. */

typedef struct Vec3 { f32 x; f32 y; f32 z; } Vec3;

typedef struct Cell {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
    s16 f008;
    s16 f00A;
    s16 f00C;
    s16 f00E;
    f32 f010;
} Cell;

typedef struct Box {
    s16 f000;
    u8  pad002[2];
    s32 f004;
    u8  pad008[2];
    u8  f00A;
    u8  pad00B[1];
    s32 f00C;
} Box;

typedef struct Rec {
    u8    pad000[0x20];
    Cell *f020;
    u8    pad024[4];
    Box  *f028;
} Rec;

typedef struct Panel {
    u8  pad000[0xAC];
    s16 f0AC;
} Panel;

typedef struct Slots {
    u8  pad000[0x10];
    s32 f010[4];
} Slots;

typedef struct Ctx {
    u8    pad000[0x18];
    void *f018;
} Ctx;

struct Meas {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * fetch() { return VCM0(void *, 0x470); }
};

extern "C" s16 normal_D_00526478[];
extern "C" s16 normal_D_00526480[];
extern "C" s16 normal_D_00526488[];
extern "C" s16 normal_D_00526490[];

extern "C" f32 D_00480600;     /* gp - 0x4B70 */
extern "C" f32 D_00480604;     /* gp - 0x4B6C */
extern "C" f32 D_00480608;     /* gp - 0x4B68 */
extern "C" f32 D_00480610;     /* gp - 0x4B60 */
extern "C" f32 D_00480614;     /* gp - 0x4B5C */
extern "C" f32 D_00480618;     /* gp - 0x4B58 */

extern "C" void * UiPageGetLayout_289b60(void *);
extern "C" Rec  *UiFindWidget_290460(void *a, s32 id);
extern "C" Ctx  *GetGameData_1fede0(void);
extern "C" Meas *PartyGetLeaderChara_3c2820(void *a);
extern "C" s32   EquipSlotGetRecName_3a07a0(void *a);
extern "C" s32   strlen(s32 a);
extern "C" void  UiSetWidgetVisible_290010(void *a, s32 id, s32 c, s32 d);
extern "C" void  normal_LeaderHudSetBannerWidth_506ad0(Panel *a, s32 b);

extern "C" s32 normal_LeaderHudBannerLayout_506370(Panel *a0, s32 a1, s32 a2, Slots *a3);

s32 normal_LeaderHudBannerLayout_506370(Panel *a0, s32 a1, s32 a2, Slots *a3)
{
    void *own;
    Rec  *rec;
    Cell *cell;
    Ctx  *ctx;
    Meas *ms;
    Box  *bx;
    void *res;
    f32   y;
    s32   cnt;
    s32   i;
    s32   v;
    s32   ret;

    own = UiPageGetLayout_289b60((void *)a0);
    if (own == NULL) {
        return 0;
    }
    rec = UiFindWidget_290460(own, a1);
    if (rec == NULL) {
        return 0;
    }
    cell = rec->f020;
    if (cell == NULL) {
        return 0;
    }
    cnt = 0;
    for (i = 0; i < 4; i++) {
        if (a3->f010[i] == -1) {
            break;
        }
        cnt++;
    }
    if (cnt == 0) {
        return 0;
    }
    {
        Vec3 pad __attribute__((aligned(16))) = {0};
        Vec3 v1 __attribute__((aligned(16))) = *(Vec3 *)&D_00480600;
        Vec3 v2 __attribute__((aligned(16))) = *(Vec3 *)&D_00480610;

        pad.x = 0.0f;

        y = 0.0f;
        cell->f000 = (s16)y;
        cell->f002 = (s16)v1.x;
        cell->f004 = cell->f00C = normal_D_00526488[0];
        cell->f006 = cell->f00E = normal_D_00526490[0];
        cell->f008 = normal_D_00526478[0];
        cell->f00A = normal_D_00526480[0];
        cell->f010 = v2.x;
        y = y + (f32)cell->f004;
    }

    ctx = GetGameData_1fede0();
    if (ctx == NULL) {
        return (s32)y;
    }
    ms = PartyGetLeaderChara_3c2820(ctx->f018);
    if (ms == NULL) {
        return (s32)y;
    }
    res = ms->fetch();
    if (res == NULL) {
        return (s32)y;
    }
    bx = rec->f028;
    bx->f00A = 2;
    bx->f004 = EquipSlotGetRecName_3a07a0(res);
    bx->f00C = 0xFF404040;
    v = 0x14 - strlen(bx->f004);
    if (v < 0) {
        v = 0;
    }
    if (v > 4) {
        bx->f000 = 0x16;
        v = 4;
    } else {
        bx->f000 = 0xC;
    }
    a0->f0AC = v;
    y = (y - (f32)(v * 9 + 8)) - 8.0f;
    UiSetWidgetVisible_290010(own, a1, 1, -1);
    ret = (s32)y;
    normal_LeaderHudSetBannerWidth_506ad0(a0, ret);
    return ret;
}
