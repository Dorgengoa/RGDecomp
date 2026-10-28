/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x004EC990 -- the gameplay party/roster scene builder.  2,520 bytes,
 * 630 instructions, 69 calls, 28 conditional branches (br/ins 0.044).
 *
 * Chosen off the CENSUS, not off the recorded next-target list: the recorded
 * ranking is `bytes / (1 + branches)`, which ranks this function #64 and hid
 * the whole large end of the productive band.  insmenu's measured predictor is
 * a THRESHOLD (br/ins < 0.055) with SIZE as the yield inside it.
 *
 * Relocation notes, per the overlay rules:
 *  - normal_D_00527000 / normal_D_005261B8 are OVERLAY data at 0x0052xxxx, far outside the
 *    gp window (_gp 0x00485170 +/- 0x8000).  Declared as INCOMPLETE arrays so
 *    they take %hi/%lo rather than %gp_rel -- an incomplete type is never small
 *    data.  The size is a RELOCATION control here, not a bound.
 *  - D_004843C8..D_004843E8 ARE inside the window and stay plain.  D_004843E8
 *    is declared [2] (8 bytes) so its base materialises as
 *    `addiu $2, $28, %gp_rel(...)`, which is what retail has.
 *
 * The `n > 8` clamp is written with `>` and not `>=`: a compare's destination
 * follows the branch's RELATIONAL OPERATOR TOKEN, and retail's `slti $1` says
 * the source wrote `> 8`.  `>= 9` is the same predicate, the same instruction
 * and a GPR destination. */

/* The virtual call at 0x004ED158 is `lw $25,0($2) / lw $25,0x444($25) /
 * jalr $25`.  A struct of function pointers gives `jalr $v0`; only a real
 * C++ `virtual` gives `jalr $t9`, so this unit is .cpp for that one call.
 * mwcc puts the first virtual at vtable slot +0x08, so slot 0x444 is index
 * (0x444-8)/4 = 271 -- 271 placeholders, then the real one.  The class is
 * never constructed here, so no vtable is emitted into the object. */
struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 measure(s32 a) { return VCM(s32, (void *, s32), 0x444, a); }
};

/* the 0x34-byte per-member record at arg0->f02C */
typedef struct Rec {
    s32 f000;
    s32 f004;
    s32 f008;
    s32 f00C;
    s32 f010;
    s32 f014;
    s16 f018;
    u8  pad01A[6];
    s32 f020;
    s32 f024;
    f32 f028;
    f32 f02C;
    f32 f030;
} Rec;

/* the source record func_3A2040 hands back */
typedef struct Src {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
    s32 f008;
    s32 f00C;
} Src;

/* the 12-byte per-member slot array at arg0->f030 */
typedef struct Slot {
    f32 f000;
    f32 f004;
    s16 f008;
    u8  pad00A[2];
} Slot;

typedef struct Scene {
    s32   f000;
    s32   f004;
    s32   f008;
    s32   f00C;
    u8    pad010[4];
    u8    f014[0x18];
    Rec  *f02C;
    Slot  f030[9];
    u8    f09C[0x10];
    u8    f0AC[0x40];
    void *f0EC;
    s8    f0F0[9];
    s8    f0F9[9];
    s16   f102;
    u8    pad104[2];
    s16   f106;
    void *f108;
    s16   f10C;
    s16   f10E;
    u8    pad110[1];
    u8    f111;
    u8    f112;
    u8    f113;
    u8    f114;
} Scene;

typedef struct Party {
    s16 f000;
    u8  pad002[6];
    s16 f008;
} Party;

typedef struct Node {
    u8   pad000[0x2C];
    s16  f02C;
    u8   pad02E[0x13A];
    u8   f168[4];
} Node;

typedef struct World {
    u8    pad000[0x1C8];
    Src  *f1C8;
} World;

typedef struct Stage {
    u8     pad000[0x238];
    Node  *f238;
} Stage;

typedef struct Scr { u8 pad000[0x30]; s16 f030; } Scr;

typedef struct Ctx {
    u8     pad000[0x14];
    void  *f014;
    Scr   *f018;
    u8     pad01C[4];
    Stage *f020;
} Ctx;

typedef struct Roster { u8 pad000[0xF6]; s16 f0F6; s16 f0F8; s16 f0FA; } Roster;

typedef struct Anchor { u8 pad000[0x100]; s16 f100; } Anchor;

typedef struct Handle { u8 pad000[0x20]; s16 *f020; s16 *f024; } Handle;

typedef struct Res { u8 pad000[0x20]; s16 f020; } Res;

extern "C" s32       normal_D_00527000[];
extern "C" s16 normal_D_005261B8[];

extern "C" void *D_004843C8;
extern "C" void *D_004843CC;
extern "C" void *D_004843D0;
extern "C" void *D_004843D4;
extern "C" Anchor *D_004843D8;
extern "C" Anchor *D_004843DC;
extern "C" void  *D_004843E8[2];
extern "C" f32    D_0047DADC;
extern "C" f32    D_0047D5D0;
extern "C" f32    D_0047D33C;

extern "C" Ctx   *GetGameData_1fede0(void);
extern "C" s32    PartyCountMembers_3c2010(void *a, s32 b, s32 c);
extern "C" s32    PartyCountReserve_3c1c20(void *a, s32 b, s32 c);
extern "C" void  *GetMenuResGroup_206a40(void);
extern "C" void   memset(void *dst, s32 v, s32 n);
extern "C" void   memcpy(void *dst, const void *src, s32 n);
extern "C" void  *ResGroupListFindValueById_42c3a0(void *a, s32 id);
extern "C" void  *ResGroupListFindValueById_42c140(void *a, s32 id);
extern "C" void   UiSetWidgetsVisibleById_291110(void *a, u16 id, s32 c, s32 d);
extern "C" Handle *UiFindWidget_290460(void *a, u16 id);
extern "C" void   UiSetWidgetPos_290f60(void *a, u16 id, s32 x, s32 y);
extern "C" void   UiSetWidgetAlpha_2907a0(void *a, u16 id, f32 v);
extern "C" void   UiFadeWidgetAlpha_290690(void *a, u16 id, f32 x, f32 y, f32 z);
extern "C" void   UiSetTextString_28f510(void *a, u16 id, void *p, s32 d);
extern "C" void   UiSetTextCenteredX_28f300(void *a, u16 id, s32 c, s32 d);
extern "C" s16   *UiGetWidgetText_28f620(void *a, u16 id, s32 c);
extern "C" void  *GetMapMgr_201a90(void);
extern "C" s32    MapSlotsFindBlockById_1e49b0(void *a, s16 b, s32 c);
extern "C" s32    MapDataIsNoDarken_1e7aa0(s32 a);
extern "C" Src   *CharaSysGetBattleResultMemberMaybe_3a2040(Stage *a, s32 i);
extern "C" Obj   *CharaMgrPoolFindById_3a8c60(void *a, s32 i);
extern "C" void   normal_MenuBattleEndMemberRowsRefreshMaybe_4ed370(Scene *a, s32 b);

extern "C" void normal_MenuBattleEndOpen_4ec990(Scene *o);

void normal_MenuBattleEndOpen_4ec990(Scene *o) {
    Ctx *ctx;
    void *res;
    void *pa;
    void *pb;
    void *pc;
    void *pd;
    Roster *ros;
    Handle *h;
    s16 *sa;
    s16 *sb;
    Rec *r;
    Src *src;
    Obj *ob;
    Node *nd;
    Party *pt;
    s16 *bar;
    Slot *sl;
    Res *rs;
    void *dv;
    s32 d;
    s32 t;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    s32 q;
    s32 m;
    s32 v;
    s32 lift;
    s32 wide;
    u8 sel;
    f32 fade;
    f32 lim;

    ctx = GetGameData_1fede0();
    o->f00C = PartyCountMembers_3c2010(ctx->f018, 1, 1);
    d = (s32)ctx->f018;
    t = PartyCountMembers_3c2010((void *)d, 1, 1);
    n = t + PartyCountReserve_3c1c20((void *)d, 1, 1);
    o->f008 = n;
    if (n > 8) {
        o->f008 = 8;
    }

    res = GetMenuResGroup_206a40();
    for (i = 0; i < 6; i = i + 1) {
        memset((u8 *)o->f0EC + (i * 0x10), 0, 0x10);
    }

    pa = ResGroupListFindValueById_42c3a0(res, 0x756C);
    pb = ResGroupListFindValueById_42c140(res, 0x7724);
    pc = ResGroupListFindValueById_42c140(res, 0x772E);
    pd = ResGroupListFindValueById_42c3a0(res, 0x7576);
    for (i = 0; i < o->f008; i = i + 1) {
        memcpy((u8 *)D_004843C8 + (i * 0x100), pa, 0x100);
        memcpy((u8 *)D_004843CC + (i * 0x80), pb, 0x80);
        memcpy((u8 *)D_004843D0 + (i * 0x40), pc, 0x40);
        memcpy((u8 *)D_004843D4 + (i * 0x40), pd, 0x40);
    }

    for (m = 0; m < 6; m = m + 1) {
        Res *rp = (Res *)ResGroupListFindValueById_42c3a0(res, m + 0x75C6);
        memset(rp, 0, 0x20);
        rp->f020 = -1;
    }

    UiSetWidgetsVisibleById_291110(o->f014, 2, 1, 1);
    UiSetWidgetPos_290f60(o->f014, 2, 0x212, 0xD0);
    UiSetWidgetAlpha_2907a0(o->f014, 2, 0.0f);

    for (i = 0; i < 4; i = i + 1) {
        k = i * 3;
        normal_D_00527000[i] = -1;
        normal_D_00527000[i + 4] = -1;
        pa = ResGroupListFindValueById_42c3a0(res, 0x7580);
        pb = ResGroupListFindValueById_42c3a0(res, 0x758A);
        memcpy((u8 *)D_004843D8 + (i * 0x40), pa, 0x20);
        memcpy((u8 *)D_004843DC + (i * 0x40), pb, 0x20);
        UiSetWidgetsVisibleById_291110(o->f014, k + 3, 0, 1);
        *(s16 *)((u8 *)o->f108 + (i * 0x20)) = -1;
        UiSetWidgetsVisibleById_291110(o->f014, k + 5, 0, 1);
        h = UiFindWidget_290460(o->f014, k + 4);
        if (h != 0) {
            sa = h->f020;
            if (sa != 0) {
                *sa = -1;
            }
            sb = h->f024;
            if (sb != 0) {
                *sb = -1;
            }
        }
    }

    nd = ctx->f020->f238;
    if (nd != 0) {
        ros = (Roster *)((World *)nd)->f1C8;
    } else {
        ros = 0;
    }
    if (ros != 0) {
        normal_D_00527000[0] = -0xFF;
        j = 1;
        for (k = 0; k < ros->f0F6; k = k + 1) {
            Roster *e = (Roster *)((u8 *)ros + (k * 4));
            normal_D_00527000[j] = e->f0F8;
            normal_D_00527000[j + 4] = e->f0FA;
            j = j + 1;
        }
    }
    D_004843D8->f100 = -1;
    D_004843DC->f100 = -1;

    if (o->f114 != 0) {
        UiSetWidgetsVisibleById_291110(o->f014, 0x47, 1, 1);
        UiSetWidgetPos_290f60(o->f014, 0x47, 0xF0, 0x19A);
        UiSetWidgetAlpha_2907a0(o->f014, 0x47, 0.0f);
    }
    UiSetWidgetPos_290f60(o->f014, 0xF, 0, 0x2D);
    UiSetWidgetPos_290f60(o->f014, 0x12, 0x200, 0x2D);
    UiSetWidgetAlpha_2907a0(o->f014, 0x10, 0.0f);
    UiSetWidgetAlpha_2907a0(o->f014, 0x13, 0.0f);
    UiSetWidgetAlpha_2907a0(o->f014, 0x11, 0.0f);
    bar = UiFindWidget_290460(o->f014, 0xF)->f020;
    bar[0] = 0;
    bar[2] = 0;
    bar = UiFindWidget_290460(o->f014, 0x12)->f020;
    bar[0] = 0;
    bar[2] = 0;
    UiSetWidgetsVisibleById_291110(o->f014, 0x14, 0, 1);
    UiSetWidgetPos_290f60(o->f014, 0x14, 0, ((o->f00C - 1) * 0x2A) + 0x69);
    bar = UiFindWidget_290460(o->f014, 0x14)->f020;
    lift = 0;
    bar[0] = 0;
    bar[2] = -1;
    for (i = 0; i < o->f008; i = i + 1) {
        k = (i * 3) + 0x15;
        UiSetWidgetsVisibleById_291110(o->f014, k, 1, 1);
        if (i >= o->f00C) {
            bar = UiFindWidget_290460(o->f014, k)->f020;
            lift = 6;
            bar[0x54] = 0x34;
        } else {
            bar = UiFindWidget_290460(o->f014, k)->f020;
            bar[0x54] = 0x2A;
        }
        UiSetWidgetPos_290f60(o->f014, k, ((1 - i) * 0x18) - 0x60,
                    lift + 0x42 + (i * 0x29));
        UiSetWidgetAlpha_2907a0(o->f014, k, 0.0f);
        UiSetWidgetsVisibleById_291110(o->f014, i + 0x3F, 0, 1);
    }

    for (i = 0; i < 3; i = i + 1) {
        q = (i * 4) + 0x2D;
        UiSetWidgetsVisibleById_291110(o->f014, q, 0, 1);
        UiSetWidgetAlpha_2907a0(o->f014, q, 0.0f);
        UiSetWidgetPos_290f60(o->f014, q, 0x11F, (i * 0x2A) + 0x3F);
    }
    UiSetWidgetsVisibleById_291110(o->f014, 1, 0, 1);
    UiSetWidgetPos_290f60(o->f014, 1, 0, 0);
    UiSetWidgetAlpha_2907a0(o->f014, 1, 0.0f);

    fade = 0.75f;
    v = MapSlotsFindBlockById_1e49b0(GetMapMgr_201a90(), ctx->f018->f030, 0);
    if (v != 0) {
        if (((unsigned char)MapDataIsNoDarken_1e7aa0(v)) == 0) {
            fade = D_0047D33C;
        }
    }
    UiFadeWidgetAlpha_290690(o->f014, 1, fade, D_0047DADC, -1.0f);

    for (i = 0; i < 9; i = i + 1) {
        o->f0F0[i] = -1;
        o->f0F9[i] = -1;
        sl = &o->f030[i];
        sl->f000 = 0.0f;
        sl->f004 = 4.0f;
        sl->f008 = 0;
        memset((u8 *)o->f02C + (i * 0x34), 0, 0x34);
    }
    for (i = 0; i < 4; i = i + 1) {
        memset(&o->f0AC[i * 0x10], 0, 0x10);
    }
    memset(&o->f09C[0], 0, 0x10);
    *(f32 *)&o->f09C[4] = -5.0f;
    *(f32 *)&o->f09C[0] = 0.0f;
    *(f32 *)&o->f09C[8] = -3.0f;
    *(s16 *)&o->f09C[0xC] = 0;

    for (i = 0; i < o->f008; i = i + 1) {
        src = CharaSysGetBattleResultMemberMaybe_3a2040(ctx->f020, i);
        if (src != 0) {
            r = &o->f02C[i];
            r->f000 = src->f000;
            r->f004 = src->f002;
            r->f008 = src->f004;
            r->f00C = src->f006;
            r->f010 = src->f008;
            r->f014 = src->f00C;
            r->f018 = (s16)(r->f00C - r->f008);
            r->f028 = (f32)r->f010;
            ob = CharaMgrPoolFindById_3a8c60(ctx->f014, r->f000);
            wide = ob->measure(r->f008);
            r->f020 = r->f008;
            r->f02C = (f32)wide;
            r->f030 = (f32)r->f004 / 32.0f;
            q = r->f004;
            lim = r->f02C;
            v = r->f010 + q;
            if ((f32)v >= lim) {
                r->f024 = (s32)lim;
            } else {
                r->f024 = v;
            }
        }
    }

    normal_MenuBattleEndMemberRowsRefreshMaybe_4ed370(o, 1);
    nd = ctx->f020->f238;
    if (nd != 0) {
        if (nd != 0) {
            pt = (Party *)&nd->f168[0];
        } else {
            pt = 0;
        }
        if (pt != 0) {
            if (nd->f02C == 0) {
                o->f000 = 0;
            } else {
                o->f102 = 0x4B;
                UiSetWidgetsVisibleById_291110(o->f014, 0x48, 1, 1);
                UiSetWidgetAlpha_2907a0(o->f014, 0x48, 0.0f);
                UiFadeWidgetAlpha_290690(o->f014, 0x48, 1.0f, D_0047D5D0, -1.0f);
                UiSetWidgetPos_290f60(o->f014, 0x48, 0x8C, 0xD0);
                sel = 1;
                if (pt->f008 == 1) {
                    sel = 0;
                }
                dv = D_004843E8[normal_D_005261B8[sel * 2]];
                UiSetTextString_28f510(o->f014, 0x48, dv, 0);
                UiSetTextCenteredX_28f300(o->f014, 0x48, 0x100, 0);
                sa = UiGetWidgetText_28f620(o->f014, 0x48, 0);
                if (sa != 0) {
                    *sa = *sa - 0x8C;
                }
                o->f000 = -2;
            }
            o->f004 = 0;
            o->f10C = 0;
            o->f111 = 1;
            o->f106 = 0;
            o->f112 = 0;
            o->f10E = 0;
            o->f113 = 0;
        }
    }
}
