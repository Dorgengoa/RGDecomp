/* === SESSION 64 (2026-09-15, SOLO): CLOSED, 71 bad -> BYTE-IDENTICAL.
 * s45 named the first half (`u8 bit` supplies retail's `andi $2,$2,0xFF`,
 * +2 words alone) and s45/s58 both concluded the partner had to be a -2 in
 * STATEMENT ORDER and failed to find one.  It is not one edit, it is four,
 * and two of them are TOKEN choices the u8 type made load-bearing
 * (memory/levers.d/mwcc-daddiu-unsigned-narrow.md: the re-narrow cost is the
 * `!= 0` / `== 0` TOKEN, not the type):
 *   1. `u8 bit` (s45).  +2 alone.
 *   2. The `bit` COMPARE spelled with a bare truth test instead of `bit == 0`
 *      -- as a nested `if (a2 < w) { if (bit) t2 = 0x15; else t2 = 0x14; }
 *      else t2 = 0x15;`.  Every `== 0` / `!= 0` spelling of the same shape is
 *      +1 or +2; `!bit` with the arms the other way round is 3 bad.
 *   3. The `f` parameter tested BARE: `if (f && ...)`, not `if (f != 0 && ..)`
 *      -- that `!= 0` was emitting a redundant `daddu $2,$2,$0` after the
 *      `lbu`.  -1 word, and it is what paid for edit 1.
 *   4. STATEMENT ORDER, two places, both of them retail's own order which
 *      s45 had measured as +1 at the OLD coat and correctly rejected there:
 *        head of the `mask != 0` block -> `c; h; e; t1; t2; got`
 *          (calls first, `e = o->f04` after them)            64 -> 12
 *        first kid branch -> `call; var; got = true; t1 = 0x2F;`
 *          (t1 LAST, so it lands in the `b`'s delay slot)    12 -> 7
 *        `func_1D05F0(h, t1, 1.0f);` BEFORE `D_004804A8 = t1;`
 *          (the store goes after the call, the argument copy
 *           takes the jal delay slot)                          7 -> 4/3
 * !! The general lesson, and it is the reason this sat for three sessions:
 * s45 measured the retail statement order as +1 and wrote "look for a -2, not
 * another +1".  The order was RIGHT ALL ALONG -- it only reads as +1 while a
 * DIFFERENT word is being paid somewhere else.  A statement-order arm measured
 * at the wrong coat is not a measurement of the order.
 * * Found by re-running memory/levers.d/opcode-histogram-screen.md over the
 * CURRENT open list: `andi:1->0` (retail narrows, we do not) put it in the
 * top three.  Arms: build/wf-normal/s64/v2ab0*.py
 */
#include "types.h"
/* normal 0x004F2AB0 -- picks the two help-line ids for object `o`.  The object's
 * node supplies an action id and a kind id; the three func_3A6D* probes build a
 * 1/2/3 capability mask.  Kinds 0x40DA..0x40DD and the default branch resolve
 * the action through func_3A8C60 / func_1C4A90 and arm hint 0x2F, kinds
 * 0x40DE/0x40DF arm 0x30 instead; the default branch also compares the probe
 * against three quarters of the target's slot-72 value to choose 0x14 vs 0x15.
 *
 * C++ virtual: `lw $25,0x128($25)` -> slot (0x128-8)/4 = 72.
 * `addiu -0x40DA / sltiu 4` is the equality OR-CHAIN fold, not a range test.
 * `daddiu $30,$0,1` is the C++ `bool`. */
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
    virtual s32 s072(s32 a);
};

typedef struct Nd  { u8 pad00[8]; s16 f08; u8 pad0A[2]; s16 *f0C; } Nd;
typedef struct Obj { Nd *f00; s32 f04; u8 pad08[0x18 - 8]; u8 f18;
                     u8 pad19[0x41 - 0x19]; u8 b41r : 7; u8 b41 : 1; } Obj;
typedef struct Ctx { u8 pad00[0x14]; void *f14; } Ctx;
typedef struct Var { u8 pad000[0x4FC]; void *f4FC; } Var;

extern const u8 D_00527020[];

extern "C" {
extern s32   D_004804A4;          /* gp - 0x4CCC */
extern s32   D_004804A8;          /* gp - 0x4CC8 */

extern s32   func_3A6D10(Obj *o);
extern s32   func_3A6D00(Obj *o);
extern s32   func_1F5BE0(void);
extern Ctx  *func_1FEDE0(void);
extern Ent  *func_3A8C60(void *a, s32 i);
extern Var  *func_1C4A90(s32 h, s32 i);
extern void  func_1D05F0(s32 h, s32 id, f32 t);
extern void  func_1B9520(void *p, s32 id, s32 a, f32 t);
extern void  normal_FieldHudPanelHealGlowStart_4f2f40(const u8 *p, s32 e, s32 mask);
}

extern "C" s32 normal_FieldHudItemUseFeedback_4f2ab0(Obj *o, u8 f)
{
    Nd  *nd;
    s16 *x;
    Ctx *c;
    Ent *m;
    Var *var;
    s32  kid;
    s32  mask;
    s32  a;
    s32  b;
    s32  a2;
    u8   bit;
    s32  h;
    s32  e;
    s32  aid;
    s32  t1;
    s32  t2;
    s32  w;
    bool got;

    if (o == 0) {
        return 0;
    }
    nd = o->f00;
    aid = -1;
    kid = -1;
    if (nd != 0) {
        x = nd->f0C;
        if (x != 0) {
            aid = nd->f08;
            kid = x[0];
        }
    }
    mask = 0;
    a = func_3A6D10(o);
    b = func_3A6D00(o);
    if (a != 0) {
        mask |= 1;
    }
    if (b != 0) {
        mask |= 2;
    }
    if ((a == 0) && (b == 0) && (o->f18 != 0)) {
        mask |= 3;
    }
    a2 = func_3A6D10(o);
    func_3A6D00(o);
    bit = o->b41;
    func_1F5BE0();
    if (mask != 0) {
        c = func_1FEDE0();
        h = func_1F5BE0();
        e = o->f04;
        t1 = -1;
        t2 = -1;
        got = false;
        if ((kid == 0x40DA) || (kid == 0x40DB) || (kid == 0x40DC) || (kid == 0x40DD)) {
            func_3A8C60(c->f14, e);
            var = func_1C4A90(h, e);
            got = true;
            t1 = 0x2F;
        } else if ((kid == 0x40DE) || (kid == 0x40DF)) {
            func_3A8C60(c->f14, aid);
            var = func_1C4A90(h, aid);
            t1 = 0x30;
        } else {
            m = func_3A8C60(c->f14, e);
            var = func_1C4A90(h, e);
            got = true;
            if (m != 0) {
                w = m->s072(1) * 3 / 4;
                if (a2 < w) {
                    if (bit) {
                        t2 = 0x15;
                    } else {
                        t2 = 0x14;
                    }
                } else {
                    t2 = 0x15;
                }
            }
        }
        if (got) {
            normal_FieldHudPanelHealGlowStart_4f2f40(D_00527020, e, mask);
        }
        if (t1 > 0) {
            func_1D05F0(h, t1, 1.0f);
            D_004804A8 = t1;
        }
        if (f && (t2 > 0) && (var != 0)) {
            func_1B9520(var->f4FC, t2, 0, 1.0f);
            D_004804A4 = t2;
        }
    }
    return 1;
}
