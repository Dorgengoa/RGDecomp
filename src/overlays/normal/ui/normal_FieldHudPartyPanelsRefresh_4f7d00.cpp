#include "types.h"
/* SESSION 41 (n41i, SOLO): CLOSED -- 17 bad -> BYTE-IDENTICAL, at 688 words the
 * largest unit closed on NORMAL to date (2,752 B = 1.16% of the text).
 * THREE separate things, and none of them alone is enough:
 *
 * 1. `#pragma opt_pulloutconstants off` (this line).  Retail RE-MATERIALISES
 *    `1.0f` with a fresh `lui`/`mtc1` at every one of the five sites in the
 *    two clamps below; mwcc's default pulls the constant out into ONE $f1 web
 *    and reaches it with `mov.s`, which is 2 words short at the rb assignment
 *    and 4 long across the ra block.  ARMED: a BOGUS pragma name reproduces
 *    the pre-arm object exactly, so the channel is real.  ⚠ Scoped between
 *    the two clamps it is INERT -- like `no_branch_likely` it is evaluated
 *    per-procedure, so it must sit before the function.  (`opt_dead_assignments
 *    off` whole-file also reaches the right length, at a different object;
 *    opt_foldconstants/treetransformation/strength_reduction/unroll_loops/
 *    lifetimes/optimize_for_size/no_register_coloring are all inert or long.)
 * 2. The `rb` clamp's `||` operands are in RETAIL'S ORDER, `rb < 0.0f` FIRST:
 *    it is what turns the pair into `bc1tl`/`bc1t` (branch INTO the shared
 *    assignment) instead of `bc1fl`/`bc1f` (branch PAST it).  The `ra` clamp
 *    four lines later was already written that way and was already exact --
 *    which is what made the disagreement legible.  ⚠ WITHOUT the pragma this
 *    edit is 2 words SHORT, i.e. it reads as a REGRESSION on its own; it is a
 *    [[two-edit-cross-beats-count-ranking]] cross.  Two separate `if`s instead
 *    of the `||` is +1 word; a ternary +2; both ternary +4.
 * 3. scripts/n_data.py, NEW THIS SESSION.  The three local array initialisers
 *    (`base`, `step`, `tbl`) are copied from mwcc TEMPLATES emitted into this
 *    object's own `.data`, and both the scorer and the linker mishandled that:
 *    bytecheck refuses to resolve a symbol outside `.text` (six words read BAD
 *    forever), and olink's lcf would collect the templates on top of the copies
 *    the overlay's data assembly already carries at D_00524D60 / D_00524D80 /
 *    D_00524DA0, doubling them.  n_data finds each template's bytes UNIQUELY
 *    in retail's .BIN, checks the address carries a `glabel D_`, retargets the
 *    lui/addiu pair and empties the section -- the exact twin of n_jtbl.py for
 *    jump tables.  All three templates are byte-identical to retail already.
 */
#pragma opt_pulloutconstants off
/* normal 0x004F7D00 -- FRESH (lane nf32e, session 32).  The party-formation
 * panel refresh: for each of the normal_FieldHudPartyRowCount_4f9c50 rows it re-drives ~9
 * widget ids whose numbers are `base[k] + step[k] * row`.
 *
 * C++ virtual (17 jalr): 0xF0 -> s058, 0x10C -> s065, 0x128 -> s072,
 * 0x130 -> s074, 0x264 -> s151, 0x268 -> s152, 0x278 -> s156.
 * gp floats: -0x7F28 = 0.7f, -0x7BA0 = D_0047D5D0,
 * -0x79CC/-0x79C8/-0x79C4/-0x79C0/-0x79BC = D_0047D7A4..D_0047D7B4.
 *
 * The three tables are LOCAL ARRAY INITIALISERS, not pointer copy loops:
 * retail hoists every `base[k]` / `step[k]` load out of the row loop and
 * spills it, which only happens when the array's address is never taken.
 * D_00524D60 / D_00524D80 / D_00524DA0 are mwcc's own initialiser templates.
 * base/step are read with `lhu`, so they are u16; tbl is read with `lh`.
 *
 * Frame 0x250: spills 0xB0..0x1CF, tbl[2][13] @0x1D0, step[9] @0x210,
 * base[9] @0x230, y @0x248, x @0x24C -- top-down in declaration order.
 */
class Ent {
public:
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
    virtual s32 s058();
    virtual void s059();
    virtual void s060();
    virtual void s061();
    virtual void s062();
    virtual void s063();
    virtual void s064();
    virtual s32 s065();
    virtual void s066();
    virtual void s067();
    virtual void s068();
    virtual void s069();
    virtual void s070();
    virtual void s071();
    virtual s32 s072(s32 a);
    virtual void s073();
    virtual s32 s074(s32 a);
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
    virtual s32 s151();
    virtual s32 s152();
    virtual void s153();
    virtual void s154();
    virtual void s155();
    virtual s32 s156();
};

typedef struct Box  { s16 x; s16 y; s16 w; s16 h; } Box;
typedef struct Row  { Box a; Box b; u8 pad10[0x10]; } Row;
typedef struct Hold { u8 pad00[0x20]; Row *f20; } Hold;
typedef struct Ctx  { u8 pad00[0x18]; s32 f18; } Ctx;
typedef struct St   { u8 pad00[0x2C]; s16 f2C; } St;
typedef struct Pan {
    u8  pad000[0x2BA];
    s16 f2BA[9];
    f32 f2CC[37];
    s8  f360[0x18];
    s16 f378;
} Pan;

extern "C" {
extern f32 D_0047D248;   /* gp - 0x7F28 */
extern f32 D_0047D5D0;   /* gp - 0x7BA0 */
extern f32 D_0047D7A4;   /* gp - 0x79CC */
extern f32 D_0047D7A8;   /* gp - 0x79C8 */
extern f32 D_0047D7AC;   /* gp - 0x79C4 */
extern f32 D_0047D7B0;   /* gp - 0x79C0 */
extern f32 D_0047D7B4;   /* gp - 0x79BC */

extern const s16 D_005261F0[][2];
extern const s16 D_00526220[][2];

extern Ctx  *func_1FEDE0(void);
extern void  func_290010(void *w, s32 id, s32 a, s32 b);
extern Hold *func_290460(void *p, u16 id);
extern f32  *func_2904B0(void *w, u16 id);
extern void  func_2904E0(void *w, u16 id, f32 a, f32 b, f32 c, f32 d, f32 e);
extern void  func_2905B0(const void *a, s32 b, f32 x, f32 y, f32 z, f32 w);
extern void  func_290F60(const void *a, s32 b, s32 c, s32 d);
extern void  func_2910A0(void *w, s32 id, s32 *x, s32 *y);
extern void  func_291110(void *w, u16 id, s32 a, s32 b);
extern void  func_291250(void *w, u16 id, s32 a, s64 v);
extern St   *func_3AE3E0(void *o);
extern s32   func_3AE1A0(void *o);
extern Ent  *func_3C2420(s32 w, s32 i);
extern s32   normal_FieldHudPanelSetPortrait_4f6f80(void *a, s32 b, s32 c);
extern void  normal_FieldHudPanelFrameLayout_4f87c0(void *p);
extern s32   normal_FieldHudPartyRowCount_4f9c50(void *p);
}

extern "C" void normal_FieldHudPartyPanelsRefresh_4f7d00(Pan *w)
{
    s32   x;
    s32   y;
    Ctx  *c;
    s32   n;
    s32   i;
    s32   j;
    s32   k;
    s32   cnt;
    s32   v0;
    u16   id0;
    s32   id2;
    Ent  *e;
    Hold *h;
    Row  *o;
    St   *st;
    s16   target;
    f32   r;
    f32   rr;
    f32   ra;
    f32   rb;
    f32   t;
    f32  *p;
    s32   v3;
    u16   id3;
    s32   id5;
    u16   id1;

    if (w->f378 == 0) {
        return;
    }
    c = func_1FEDE0();
    if (c == 0) {
        return;
    }
    n = normal_FieldHudPartyRowCount_4f9c50(w);

    u16 base[9] = { 6, 3, 12, 11, 10, 27, 9, 8, 7 };
    u16 step[9] = { 7, 1, 7, 7, 7, 1, 7, 7, 7 };

    for (i = 0; i < 3; i++) {
        func_290010(w, (u16)(base[0] + step[0] * i), 0, -1);
        func_291110(w, (u16)(base[1] + step[1] * i), 0, 1);
        func_291110(w, (u16)(base[2] + step[2] * i), 0, 1);
    }
    normal_FieldHudPanelFrameLayout_4f87c0(w);

    for (j = 0; j < n; j++) {
        e = func_3C2420(c->f18, j);
        if (e == 0) {
            continue;
        }
        v0 = base[0] + step[0] * j;
        id0 = (u16)v0;
        func_290010(w, id0, 1, -1);
        r = (f32)e->s058() / (f32)e->s072(1);
        if (e->s058() > 0) {
            if (r <= D_0047D5D0) {
                func_2904B0(w, id0);
                w->f360[j] = 1;
            } else {
                w->f360[j] = 0;
                func_2905B0(w, id0, 1.0f, 1.0f, 1.0f, -1.0f);
            }
        } else {
            w->f360[j] = 0;
            func_2905B0(w, id0, 0.7f, 0.7f, 0.7f, -1.0f);
        }
        w->f2CC[j] = r;

        v3 = base[3] + step[3] * j;
        id3 = (u16)v3;
        func_291250(w, id3, 0, (s64)e->s058());
        func_291250(w, id3, 1, (s64)e->s072(1));
        func_291250(w, id3, 2, (s64)e->s065());
        func_291250(w, id3, 3, (s64)e->s074(1));

        normal_FieldHudPanelSetPortrait_4f6f80(w, (u16)(base[4] + step[4] * j), j);
        if (w->f2BA[j] == 0) {
            func_290F60(w, (u16)(base[4] + step[4] * j), 0x33, -0x19);
        }

        id5 = (u16)(base[5] + step[5] * j);
        h = func_290460(w, id5);
        if (h != 0) {
            o = h->f20;
            if (o != 0) {
                st = func_3AE3E0(e);
                if (st == 0) {
                    continue;
                }
                target = st->f2C;
                o->a.x = 0;
                o->a.y = 0;
                for (k = 0; k < 11; k++) {
                    if (target == D_005261F0[k][0]) {
                        o->b.x = D_005261F0[k][1];
                    }
                    if (target == D_00526220[k][0]) {
                        o->b.y = D_00526220[k][1];
                    }
                }
                o->b.w = 0x30;
                o->a.w = 0x30;
                o->b.h = 0x30;
                o->a.h = 0x30;
                func_290F60(w, id5, 0, 1);
            }
        }

        h = func_290460(w, (u16)(base[6] + step[6] * j));
        if (h != 0) {
            o = h->f20;
            if (o != 0) {
                ra = (f32)e->s058() / (f32)e->s072(1);
                rb = (f32)e->s065() / (f32)e->s074(1);
                if (rb < 0.0f || rb > 1.0f) {
                    rb = 1.0f;
                }
                if (ra < 0.0f || ra > 1.0f) {
                    ra = 1.0f;
                }
                o[4].b.w = 0x4B;
                o[1].b.w = 0x4B;
                if ((f32)e->s074(1) <= 0.0f) {
                    rb = 0.0f;
                    o[4].b.w = 0;
                }
                if (ra <= 0.0f) {
                    ra = 0.0f;
                    o[1].b.w = 0;
                    func_291110(w, (u16)(base[7] + step[7] * j), 0, 1);
                    func_291110(w, (u16)(base[6] + step[6] * j), 0, 1);
                    func_291110(w, (u16)v3, 0, 1);
                    id2 = (u16)(base[2] + step[2] * j);
                    func_291110(w, id2, 1, 1);
                    func_2910A0(w, (u16)v0, &x, &y);
                    func_290F60(w, id2, x, y);
                    func_2905B0(w, id2, D_0047D7A4, D_0047D7A4, D_0047D7A4, -1.0f);
                } else {
                    func_291110(w, (u16)(base[7] + step[7] * j), 1, 1);
                    func_291110(w, (u16)(base[6] + step[6] * j), 1, 1);
                    func_291110(w, (u16)(base[8] + step[8] * j), 1, 1);
                    func_291110(w, (u16)(base[2] + step[2] * j), 0, 1);
                }
                o[1].a.w = (s16)(s32)(75.0f * ra);
                o[4].a.w = (s16)(s32)(75.0f * rb);
                if (o[1].a.w == 0) {
                    o[1].b.w = 0;
                }
                if (o[4].a.w == 0) {
                    o[4].b.w = 0;
                }
            }
        }

        id1 = (u16)(base[1] + step[1] * j);
        func_291110(w, id1, 1, 1);
        h = func_290460(w, id1);
        if (h == 0) {
            continue;
        }
        o = h->f20;
        if (o == 0) {
            continue;
        }
        s16 tbl[2][13] = {
            { 0, 8, 0x10, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31 },
            { 0x18, 0x20, 0x28, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F },
        };
        if (func_3AE1A0(e) != 0) {
            for (k = 0; k < 13; k++) {
                o[k].b.x = tbl[0][k];
            }
        } else {
            for (k = 0; k < 13; k++) {
                o[k].b.x = tbl[1][k];
            }
        }
        rr = (f32)e->s152() / (f32)e->s151();
        t = D_0047D7A8;
        if (e->s156() != 0) {
            t = D_0047D7AC;
        }
        cnt = (s32)(10.0f * (rr + t));
        if (e->s152() == 0) {
            cnt = 0;
        }
        if (cnt < 0) {
            cnt = 0;
        } else if (cnt > 10) {
            cnt = 10;
        }
        for (k = 3; k < 13; k++) {
            if (k >= cnt + 3) {
                o[k].a.x = -1;
            } else {
                o[k].a.x = (s16)((k - 3) * 10 + 2);
            }
        }
        if (e->s156() != 0) {
            p = func_2904B0(w, id1);
            if (*p >= 1.0f) {
                func_2904E0(w, id1, 0.5f, 0.5f, 0.5f, -1.0f, D_0047D7B0);
            } else if (*p <= 0.5f) {
                func_2904E0(w, id1, 1.0f, 1.0f, 1.0f, -1.0f, D_0047D7AC);
            }
        } else {
            func_2904E0(w, id1, 1.0f, 1.0f, 1.0f, -1.0f, D_0047D7B4);
        }
    }
}
