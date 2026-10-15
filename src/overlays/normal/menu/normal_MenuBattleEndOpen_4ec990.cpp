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
 *  - D_00527000 / D_005261B8 are OVERLAY data at 0x0052xxxx, far outside the
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
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual void s045();
    virtual void s046();
    virtual void s047();
    virtual void s048();
    virtual void s049();
    virtual void s050();
    virtual void s051();
    virtual void s052();
    virtual void s053();
    virtual void s054();
    virtual void s055();
    virtual void s056();
    virtual void s057();
    virtual void s058();
    virtual void s059();
    virtual void s060();
    virtual void s061();
    virtual void s062();
    virtual void s063();
    virtual void s064();
    virtual void s065();
    virtual void s066();
    virtual void s067();
    virtual void s068();
    virtual void s069();
    virtual void s070();
    virtual void s071();
    virtual void s072();
    virtual void s073();
    virtual void s074();
    virtual void s075();
    virtual void s076();
    virtual void s077();
    virtual void s078();
    virtual void s079();
    virtual void s080();
    virtual void s081();
    virtual void s082();
    virtual void s083();
    virtual void s084();
    virtual void s085();
    virtual void s086();
    virtual void s087();
    virtual void s088();
    virtual void s089();
    virtual void s090();
    virtual void s091();
    virtual void s092();
    virtual void s093();
    virtual void s094();
    virtual void s095();
    virtual void s096();
    virtual void s097();
    virtual void s098();
    virtual void s099();
    virtual void s100();
    virtual void s101();
    virtual void s102();
    virtual void s103();
    virtual void s104();
    virtual void s105();
    virtual void s106();
    virtual void s107();
    virtual void s108();
    virtual void s109();
    virtual void s110();
    virtual void s111();
    virtual void s112();
    virtual void s113();
    virtual void s114();
    virtual void s115();
    virtual void s116();
    virtual void s117();
    virtual void s118();
    virtual void s119();
    virtual void s120();
    virtual void s121();
    virtual void s122();
    virtual void s123();
    virtual void s124();
    virtual void s125();
    virtual void s126();
    virtual void s127();
    virtual void s128();
    virtual void s129();
    virtual void s130();
    virtual void s131();
    virtual void s132();
    virtual void s133();
    virtual void s134();
    virtual void s135();
    virtual void s136();
    virtual void s137();
    virtual void s138();
    virtual void s139();
    virtual void s140();
    virtual void s141();
    virtual void s142();
    virtual void s143();
    virtual void s144();
    virtual void s145();
    virtual void s146();
    virtual void s147();
    virtual void s148();
    virtual void s149();
    virtual void s150();
    virtual void s151();
    virtual void s152();
    virtual void s153();
    virtual void s154();
    virtual void s155();
    virtual void s156();
    virtual void s157();
    virtual void s158();
    virtual void s159();
    virtual void s160();
    virtual void s161();
    virtual void s162();
    virtual void s163();
    virtual void s164();
    virtual void s165();
    virtual void s166();
    virtual void s167();
    virtual void s168();
    virtual void s169();
    virtual void s170();
    virtual void s171();
    virtual void s172();
    virtual void s173();
    virtual void s174();
    virtual void s175();
    virtual void s176();
    virtual void s177();
    virtual void s178();
    virtual void s179();
    virtual void s180();
    virtual void s181();
    virtual void s182();
    virtual void s183();
    virtual void s184();
    virtual void s185();
    virtual void s186();
    virtual void s187();
    virtual void s188();
    virtual void s189();
    virtual void s190();
    virtual void s191();
    virtual void s192();
    virtual void s193();
    virtual void s194();
    virtual void s195();
    virtual void s196();
    virtual void s197();
    virtual void s198();
    virtual void s199();
    virtual void s200();
    virtual void s201();
    virtual void s202();
    virtual void s203();
    virtual void s204();
    virtual void s205();
    virtual void s206();
    virtual void s207();
    virtual void s208();
    virtual void s209();
    virtual void s210();
    virtual void s211();
    virtual void s212();
    virtual void s213();
    virtual void s214();
    virtual void s215();
    virtual void s216();
    virtual void s217();
    virtual void s218();
    virtual void s219();
    virtual void s220();
    virtual void s221();
    virtual void s222();
    virtual void s223();
    virtual void s224();
    virtual void s225();
    virtual void s226();
    virtual void s227();
    virtual void s228();
    virtual void s229();
    virtual void s230();
    virtual void s231();
    virtual void s232();
    virtual void s233();
    virtual void s234();
    virtual void s235();
    virtual void s236();
    virtual void s237();
    virtual void s238();
    virtual void s239();
    virtual void s240();
    virtual void s241();
    virtual void s242();
    virtual void s243();
    virtual void s244();
    virtual void s245();
    virtual void s246();
    virtual void s247();
    virtual void s248();
    virtual void s249();
    virtual void s250();
    virtual void s251();
    virtual void s252();
    virtual void s253();
    virtual void s254();
    virtual void s255();
    virtual void s256();
    virtual void s257();
    virtual void s258();
    virtual void s259();
    virtual void s260();
    virtual void s261();
    virtual void s262();
    virtual void s263();
    virtual void s264();
    virtual void s265();
    virtual void s266();
    virtual void s267();
    virtual void s268();
    virtual void s269();
    virtual void s270();
    virtual s32 measure(s32 a);
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

extern "C" s32       D_00527000[];
extern "C" const s16 D_005261B8[];

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

extern "C" Ctx   *func_1FEDE0(void);
extern "C" s32    func_3C2010(void *a, s32 b, s32 c);
extern "C" s32    func_3C1C20(void *a, s32 b, s32 c);
extern "C" void  *func_206A40(void);
extern "C" void   func_131B60(void *dst, s32 v, s32 n);
extern "C" void   func_1319A8(void *dst, const void *src, s32 n);
extern "C" void  *func_42C3A0(void *a, s32 id);
extern "C" void  *func_42C140(void *a, s32 id);
extern "C" void   func_291110(void *a, u16 id, s32 c, s32 d);
extern "C" Handle *func_290460(void *a, u16 id);
extern "C" void   func_290F60(void *a, u16 id, s32 x, s32 y);
extern "C" void   func_2907A0(void *a, u16 id, f32 v);
extern "C" void   func_290690(void *a, u16 id, f32 x, f32 y, f32 z);
extern "C" void   func_28F510(void *a, u16 id, void *p, s32 d);
extern "C" void   func_28F300(void *a, u16 id, s32 c, s32 d);
extern "C" s16   *func_28F620(void *a, u16 id, s32 c);
extern "C" void  *func_201A90(void);
extern "C" s32    func_1E49B0(void *a, s16 b, s32 c);
extern "C" s32    func_1E7AA0(s32 a);
extern "C" Src   *func_3A2040(Stage *a, s32 i);
extern "C" Obj   *func_3A8C60(void *a, s32 i);
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

    ctx = func_1FEDE0();
    o->f00C = func_3C2010(ctx->f018, 1, 1);
    d = (s32)ctx->f018;
    t = func_3C2010((void *)d, 1, 1);
    n = t + func_3C1C20((void *)d, 1, 1);
    o->f008 = n;
    if (n > 8) {
        o->f008 = 8;
    }

    res = func_206A40();
    for (i = 0; i < 6; i = i + 1) {
        func_131B60((u8 *)o->f0EC + (i * 0x10), 0, 0x10);
    }

    pa = func_42C3A0(res, 0x756C);
    pb = func_42C140(res, 0x7724);
    pc = func_42C140(res, 0x772E);
    pd = func_42C3A0(res, 0x7576);
    for (i = 0; i < o->f008; i = i + 1) {
        func_1319A8((u8 *)D_004843C8 + (i * 0x100), pa, 0x100);
        func_1319A8((u8 *)D_004843CC + (i * 0x80), pb, 0x80);
        func_1319A8((u8 *)D_004843D0 + (i * 0x40), pc, 0x40);
        func_1319A8((u8 *)D_004843D4 + (i * 0x40), pd, 0x40);
    }

    for (m = 0; m < 6; m = m + 1) {
        Res *rp = (Res *)func_42C3A0(res, m + 0x75C6);
        func_131B60(rp, 0, 0x20);
        rp->f020 = -1;
    }

    func_291110(o->f014, 2, 1, 1);
    func_290F60(o->f014, 2, 0x212, 0xD0);
    func_2907A0(o->f014, 2, 0.0f);

    for (i = 0; i < 4; i = i + 1) {
        k = i * 3;
        D_00527000[i] = -1;
        D_00527000[i + 4] = -1;
        pa = func_42C3A0(res, 0x7580);
        pb = func_42C3A0(res, 0x758A);
        func_1319A8((u8 *)D_004843D8 + (i * 0x40), pa, 0x20);
        func_1319A8((u8 *)D_004843DC + (i * 0x40), pb, 0x20);
        func_291110(o->f014, k + 3, 0, 1);
        *(s16 *)((u8 *)o->f108 + (i * 0x20)) = -1;
        func_291110(o->f014, k + 5, 0, 1);
        h = func_290460(o->f014, k + 4);
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
        D_00527000[0] = -0xFF;
        j = 1;
        for (k = 0; k < ros->f0F6; k = k + 1) {
            Roster *e = (Roster *)((u8 *)ros + (k * 4));
            D_00527000[j] = e->f0F8;
            D_00527000[j + 4] = e->f0FA;
            j = j + 1;
        }
    }
    D_004843D8->f100 = -1;
    D_004843DC->f100 = -1;

    if (o->f114 != 0) {
        func_291110(o->f014, 0x47, 1, 1);
        func_290F60(o->f014, 0x47, 0xF0, 0x19A);
        func_2907A0(o->f014, 0x47, 0.0f);
    }
    func_290F60(o->f014, 0xF, 0, 0x2D);
    func_290F60(o->f014, 0x12, 0x200, 0x2D);
    func_2907A0(o->f014, 0x10, 0.0f);
    func_2907A0(o->f014, 0x13, 0.0f);
    func_2907A0(o->f014, 0x11, 0.0f);
    bar = func_290460(o->f014, 0xF)->f020;
    bar[0] = 0;
    bar[2] = 0;
    bar = func_290460(o->f014, 0x12)->f020;
    bar[0] = 0;
    bar[2] = 0;
    func_291110(o->f014, 0x14, 0, 1);
    func_290F60(o->f014, 0x14, 0, ((o->f00C - 1) * 0x2A) + 0x69);
    bar = func_290460(o->f014, 0x14)->f020;
    lift = 0;
    bar[0] = 0;
    bar[2] = -1;
    for (i = 0; i < o->f008; i = i + 1) {
        k = (i * 3) + 0x15;
        func_291110(o->f014, k, 1, 1);
        if (i >= o->f00C) {
            bar = func_290460(o->f014, k)->f020;
            lift = 6;
            bar[0x54] = 0x34;
        } else {
            bar = func_290460(o->f014, k)->f020;
            bar[0x54] = 0x2A;
        }
        func_290F60(o->f014, k, ((1 - i) * 0x18) - 0x60,
                    lift + 0x42 + (i * 0x29));
        func_2907A0(o->f014, k, 0.0f);
        func_291110(o->f014, i + 0x3F, 0, 1);
    }

    for (i = 0; i < 3; i = i + 1) {
        q = (i * 4) + 0x2D;
        func_291110(o->f014, q, 0, 1);
        func_2907A0(o->f014, q, 0.0f);
        func_290F60(o->f014, q, 0x11F, (i * 0x2A) + 0x3F);
    }
    func_291110(o->f014, 1, 0, 1);
    func_290F60(o->f014, 1, 0, 0);
    func_2907A0(o->f014, 1, 0.0f);

    fade = 0.75f;
    v = func_1E49B0(func_201A90(), ctx->f018->f030, 0);
    if (v != 0) {
        if (func_1E7AA0(v) == 0) {
            fade = D_0047D33C;
        }
    }
    func_290690(o->f014, 1, fade, D_0047DADC, -1.0f);

    for (i = 0; i < 9; i = i + 1) {
        o->f0F0[i] = -1;
        o->f0F9[i] = -1;
        sl = &o->f030[i];
        sl->f000 = 0.0f;
        sl->f004 = 4.0f;
        sl->f008 = 0;
        func_131B60((u8 *)o->f02C + (i * 0x34), 0, 0x34);
    }
    for (i = 0; i < 4; i = i + 1) {
        func_131B60(&o->f0AC[i * 0x10], 0, 0x10);
    }
    func_131B60(&o->f09C[0], 0, 0x10);
    *(f32 *)&o->f09C[4] = -5.0f;
    *(f32 *)&o->f09C[0] = 0.0f;
    *(f32 *)&o->f09C[8] = -3.0f;
    *(s16 *)&o->f09C[0xC] = 0;

    for (i = 0; i < o->f008; i = i + 1) {
        src = func_3A2040(ctx->f020, i);
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
            ob = func_3A8C60(ctx->f014, r->f000);
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
                func_291110(o->f014, 0x48, 1, 1);
                func_2907A0(o->f014, 0x48, 0.0f);
                func_290690(o->f014, 0x48, 1.0f, D_0047D5D0, -1.0f);
                func_290F60(o->f014, 0x48, 0x8C, 0xD0);
                sel = 1;
                if (pt->f008 == 1) {
                    sel = 0;
                }
                dv = D_004843E8[D_005261B8[sel * 2]];
                func_28F510(o->f014, 0x48, dv, 0);
                func_28F300(o->f014, 0x48, 0x100, 0);
                sa = func_28F620(o->f014, 0x48, 0);
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
