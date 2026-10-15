/* MATCHED byte-identical, lane r2c (round 2, session 19).  292 words.
 * WHAT CLOSED IT, worth 2 words: the four-way kind test is NOT a `switch` and
 * NOT an `||` chain.  mwcc FOLDS `k==1||k==2||k==3||k==4` to a range check
 * (`addiu -1 / sltiu 4`, 7 words SHORT) and gives a merged-label `switch` a
 * positive `beq` plus `b DEFAULT` on the LAST arm (2 words LONG).  Retail
 * closes the chain with the last arm INVERTED and its delay slot filled from
 * the target:
 *     addiu $2,$0,0x4 / bnel $3,$2,.L004F2798 / daddu $4,$17,$0
 * The spelling that reaches it is FOUR SEPARATE `if` STATEMENTS WITH `goto`,
 * over ONE named local read of the selector:
 *     k = e->f2C;
 *     if (k == 1) goto wide;  if (k == 2) goto wide;  if (k == 3) goto wide;
 *     if (k != 4) goto narrow;
 *   wide:   ... goto done;
 *   narrow: ...
 *   done: ;
 * Separate `if` statements are NOT folded to a range check the way an `||`
 * chain is, and the inverted last test falls through into the shared body --
 * which is exactly retail's control flow.  The named `k` is load-bearing: four
 * inline `e->f2C` reads would emit four loads (retail reads it once into $3).
 * The SECOND kind chain (1/2/3/4 -> different format calls) still re-reads
 * `e->f2C` per arm, which is retail's. */
#include "types.h"
/* normal 0x004F23E0 -- fills the quest/objective banner.  With an active
 * objective (t->f20->f238) the 0x4F frame is raised and, for kinds 1..4, the
 * 0x51 icon takes the wide 0x526360 art and the 0x50 caption is formatted from
 * the kind: 1 adds the target's rank, 2 and 4 the remaining seconds
 * (f30 / 60), 3 a fixed string.  The caption is then measured with the
 * 0x26C610 text engine and centred in 0x200 before three shadow copies are
 * stamped.  Any other kind falls back to the narrow 0x526370 art.
 *
 * ONE `lw $25,0($19) / lw $25,0x60($25) / jalr $25` -> C++ virtual, vptr 0,
 * slot (0x60-8)/4 = 22.
 * `bgez / sra 1 / addiu +1 / sra 1` is a SIGNED `/ 2`, not a shift.
 * The FIRST kind test is an OR-chain over one shared body (last term
 * inverted); the second is an if/else-if chain, and it RE-READS e->f2C.
 * Stack locals come out in REVERSE declaration order. */

struct Tgt {
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
    virtual s32 rank();   /* slot 22 -> vtable +0x60 */
};

typedef struct Cell { s16 f00; s16 f02; s16 f04; s16 f06; s16 f08; s16 f0A;
                      s16 f0C; s16 f0E; } Cell;
typedef struct Wgt  { u8 pad00[4]; u8 f04; u8 pad05[0x20 - 5]; Cell *f20; } Wgt;
typedef struct Obj  { u8 pad00[0x2C]; s16 f2C; s16 f2E; f32 f30; } Obj;
typedef struct Hub  { u8 pad000[0x238]; Obj *f238; } Hub;
typedef struct Top  { u8 pad00[0x14]; s32 f14; u8 pad18[8]; Hub *f20; } Top;
typedef struct Bar  { u8 pad000[0x378]; s16 f378; s16 f37A;
                      s16 f37C; s16 f37E; s16 f380; } Bar;

extern const u8 D_00526350[];
extern const u8 D_00526360[];
extern const u8 D_00526370[];
extern u8       D_00527520[];

extern void *D_00481BBC;          /* gp - 0x35B4 */
extern f32   D_0047D5D0;          /* gp - 0x7BA0 */
extern f32   D_0047DADC;          /* gp - 0x7694 */

extern "C" {

extern void  func_1343B8(u8 *dst, const void *a, ...);
extern void  func_134A98(u8 *dst, const u8 *src);
extern Top  *func_1FEDE0(void);
extern void  func_26C610(void *e);
extern void  func_26DAF0(void *e, const u8 *s, s32 *w, void *h);
extern void  func_26EDF0(void *e, s32 k);
extern void  func_26F2B0(void *e, s32 k, s32 c);
extern const void *func_28AA30(void *p, s32 id);
extern void  func_28FBF0(Bar *w, u16 id, s32 x, s32 k);
extern void  func_28FCD0(Bar *w, u16 id, s32 x, s32 k);
extern Wgt  *func_290460(Bar *w, u16 id);
extern void  func_2904E0(Bar *w, u16 id, f32 r, f32 g, f32 b, f32 t, f32 u);
extern void  func_290690(Bar *w, u16 id, f32 r, f32 g, f32 b);
extern void  func_2907A0(Bar *w, u16 id, f32 t);
extern void  func_290B20(Bar *w, u16 id, const u8 *s, s32 c, s32 d, s32 e);
extern void  func_290F60(Bar *w, u16 id, s32 x, s32 y);
extern void  func_291110(Bar *w, u16 id, s32 c, s32 d);
extern Tgt  *func_3A8C60(s32 a, s16 k);

}

extern "C" void normal_FieldHudMissionBannerShowMaybe_4f23e0(Bar *a, s16 b)
{
    s32   w0;
    s32   w1;
    s32   eng[0x12];
    Top  *t;
    Obj  *e;
    Wgt  *p;
    Cell *g;
    Tgt  *h;
    const void *s;
    s32   n;
    s32   i;
    s32   j;
    s32   k;

    if (a->f378 != 0) {
        t = func_1FEDE0();
        if (t != 0) {
            e = t->f20->f238;
            if (e != 0) {
                func_291110(a, 0x4F, 1, 1);
                k = e->f2C;
                if (k == 1) goto wide;
                if (k == 2) goto wide;
                if (k == 3) goto wide;
                if (k != 4) goto narrow;
                wide:
                    p = func_290460(a, 0x51);
                    func_134A98(&p->f04, D_00526360);
                    g = p->f20;
                    if (g != 0) {
                        g->f00 = 0x80;
                        g->f02 = 0xCA;
                        g->f0C = 0x100;
                        g->f04 = 0x100;
                        g->f0E = 0x1A;
                        g->f06 = 0x1A;
                        g->f08 = 0;
                        g->f0A = 0x1A;
                    }
                    if (e->f2C == 1) {
                        h = func_3A8C60(t->f14, e->f2E);
                        if (h != 0) {
                            s = func_28AA30(D_00481BBC, 7);
                            n = (s32)(e->f30 / 60.0f);
                            func_1343B8(D_00527520, s, n, h->rank());
                        }
                    } else if (e->f2C == 2) {
                        func_1343B8(D_00527520, func_28AA30(D_00481BBC, 3),
                                    (s32)(e->f30 / 60.0f));
                    } else if (e->f2C == 3) {
                        func_1343B8(D_00527520, D_00526350,
                                    func_28AA30(D_00481BBC, 4));
                    } else if (e->f2C == 4) {
                        func_1343B8(D_00527520, func_28AA30(D_00481BBC, 5),
                                    (s32)(e->f30 / 60.0f));
                    }
                    func_290B20(a, 0x50, D_00527520, -1, -1, 0);
                    func_291110(a, 0x50, 1, 1);
                    func_2907A0(a, 0x50, 0.0f);
                    func_290690(a, 0x50, 1.0f, D_0047D5D0, -1.0f);
                    func_291110(a, 0x54, 1, 1);
                    func_2907A0(a, 0x54, 0.0f);
                    func_290690(a, 0x54, 1.0f, D_0047D5D0, -1.0f);
                    func_26C610(eng);
                    func_26C610(eng);
                    func_26EDF0(eng, 2);
                    func_26F2B0(eng, 3, 0);
                    func_26DAF0(eng, D_00527520, &w0, &w1);
                    func_290F60(a, 0x50, (0x200 - w0) / 2, 0x12C);
                    i = 0;
                    do {
                        j = i * 3;
                        func_28FBF0(a, 0x50, w0 + 0x10, j + 1);
                        func_28FCD0(a, 0x50, w0 + 8, j + 2);
                        i++;
                    } while (i < 3);
                    a->f37E = 1;
                    goto done;
                narrow:
                    func_291110(a, 0x50, 0, 1);
                    p = func_290460(a, 0x51);
                    func_134A98(&p->f04, D_00526370);
                    g = p->f20;
                    if (g != 0) {
                        g->f00 = 0xBB;
                        g->f02 = 0xCA;
                        g->f0C = 0x86;
                        g->f04 = 0x86;
                        g->f0E = 0x1A;
                        g->f06 = 0x1A;
                        g->f08 = 0x78;
                        g->f0A = 0xCA;
                    }
                done: ;
                func_2907A0(a, 0x4F, 1.0f);
                func_2904E0(a, 0x4F, 1.5f, 1.5f, 1.5f, -1.0f, D_0047DADC);
                a->f37A = 1;
                a->f37C = 0;
                a->f380 = b;
            }
        }
    }
}
