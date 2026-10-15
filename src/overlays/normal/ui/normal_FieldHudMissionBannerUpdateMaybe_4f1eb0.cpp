#pragma opt_recomposeaggregates off
#pragma divbyzerocheck on
/* SESSION 32 (2026-09-05), lane nc32j: MATCH (243 words, lit4 ok/7).
 * The s29 park at 4 bad was two adjacent transpositions in the first
 * func_290690 argument setup at 0x004F1F6C -- retail hoisted the float load
 * ABOVE the `p->f37C = lim;` store and we did not:
 *   retail  lwc1 $f13 / lui / sh $3,0x37C($16) / mtc1 $0,$f12 / daddu $4
 *   ours    sh $3,0x37C($16) / lui / lwc1 $f13 / daddu $4 / mtc1 $0,$f12
 * CAUSE: D_0047DA6C (-0.1f) and D_0047DA44 (+0.1f) are not globals at all --
 * both addresses lie inside mwcc's FLOAT LITERAL POOL band
 * 0x0047D1C8-0x0048025C.  An `extern f32` read is PINNED at its use because it
 * may alias the `sh`; a .lit4 load carries no alias hazard and HOISTS, which is
 * exactly retail's schedule.  Writing the two constants as LITERALS closes the
 * unit.  s29 had only tried `const` on the externs (length-wrong, +3/+4 words)
 * and moving the store (14 and 74 bad); the s32 pool-wide lit deck never
 * reached this unit (its 220 arms were 200 declaration / 7 move / 3 extract /
 * 2 bool, zero lit arms).
 * MEASURED, 22-arm deck, identity arm reproduced the 4-bad park:
 *   -0.1f literal alone            = MATCH   (the whole payment)
 *   +0.1f literal alone            = 4 bad   (inert, but correct spelling)
 *   store moved after call 1 / 3   = 14 / 74 bad, with or without the literals
 *   s16 lim, (s16) cast on the store, p->f37C = p->f380 = all inert
 */
#include "types.h"
/* normal 0x004F1EB0 -- the off-screen target arrow's per-frame tick.  While the
 * 0x37A flag is up it advances the 0x37C timer, pulses the 0x51 arrow on a
 * (t/5)%2 square wave, and once the timer reaches the 0x380 limit fades the
 * three widgets out.  Before the limit it rebuilds the camera basis
 * (normal_FUN_004F2280 gives the target vector, the camera's virtual slots 39
 * and 40 give eye and up), projects onto it and parks the 0x52/0x53 caret on
 * the left or the right edge of the screen every fifth frame.
 *
 * TWO VIRTUAL calls with the vptr at +0xC0 (`lw $25,0xC0($x) /
 * lw $25,0xA4($25) / jalr $25`), so the unit is .cpp; the slots are
 * (0xA4-8)/4 = 39 and (0xA8-8)/4 = 40 and the class carries 0xC0 bytes of
 * padding before its first virtual.
 * ⚠ `bnez $2 / div / break 0,7` appears on the `/` only -- the three `%`
 * divides carry no trap -- so `#pragma divbyzerocheck on` is required and the
 * modulos must stay written as `%`.
 * `neg.s` builds the perpendicular {z, y, -x} in place.
 * `sltu $17,$0,$2` sits in func_1CBA90's DELAY SLOT: `(t % 10) != 0` is the
 * statement BEFORE that call. */

typedef struct Vec { f32 x; f32 y; f32 z; f32 w; } Vec;

typedef struct Arw {
    u8  pad000[0x37A];
    s16 f37A;
    s16 f37C;
    u8  pad37E[2];
    s16 f380;
} Arw;

typedef struct Root { u8 pad0000[0x4344]; s32 f4344; } Root;

struct Cam {
    u8 pad000[0xC0];
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
    virtual void getA(Vec *v);        /* slot 39 -> vtable +0xA4 */
    virtual void getB(Vec *v);        /* slot 40 -> vtable +0xA8 */
};

extern "C" Cam  *func_1C3BC0(Root *r, s32 k);
extern "C" f32   func_1CBA90(Vec *a, Vec *b);
extern "C" void  func_1CBD00(Vec *d, Vec *a, Vec *b);
extern "C" Root *func_1F5BE0(void);
extern "C" void  func_28F850(Arw *p, u16 id, s32 a, s32 b);
extern "C" void  func_28F930(Arw *p, u16 id, s32 a, s32 b);
extern "C" void  func_290690(Arw *p, u16 id, f32 a, f32 b, f32 c);
extern "C" f32   func_290770(Arw *p, u16 id);
extern "C" void  func_2907A0(Arw *p, u16 id, f32 a);
extern "C" void  func_290F50(Arw *p, u16 id, s32 x, s32 y, s32 c, f32 t);
extern "C" void  func_290F60(Arw *p, u16 id, s32 x, s32 y);
extern "C" void  func_291110(Arw *p, u16 id, s32 c, s32 d);
extern "C" void  normal_FieldHudGetEnemyCentroid_4f2280(Vec *v);

extern "C" void normal_FieldHudMissionBannerUpdateMaybe_4f1eb0(Arw *p);

void normal_FieldHudMissionBannerUpdateMaybe_4f1eb0(Arw *p)
{
    Vec   tgt;
    Vec   fwd;
    Vec   up;
    Vec   eye;
    Vec   ax;
    Vec   pv;
    Root *r;
    Cam  *c;
    s32   lim;
    s32   t;
    s32   j;
    u16   id;

    if (p->f37A == 0) {
        return;
    }
    if (p->f37C == 0) {
        func_2907A0(p, 0x52, 0.0f);
        func_2907A0(p, 0x53, 0.0f);
    }
    p->f37C = p->f37C + 1;
    if (p->f37A != 2) {
        func_2907A0(p, 0x51, (f32)((p->f37C / 5) % 2));
    }
    lim = p->f380;
    if (lim < 0) {
        return;
    }
    if (p->f37C >= lim) {
        p->f37C = lim;
        func_290690(p, 0x51, 0.0f, -0.1f, -1.0f);
        func_290690(p, 0x52, 0.0f, -0.1f, -1.0f);
        func_290690(p, 0x53, 0.0f, -0.1f, -1.0f);
        if (func_290770(p, 0x51) <= 0.0f) {
            p->f37A = 0;
            func_291110(p, 0x51, 0, 1);
            func_291110(p, 0x52, 0, 1);
            func_291110(p, 0x53, 0, 1);
        }
    } else {
        normal_FieldHudGetEnemyCentroid_4f2280(&tgt);
        r = func_1F5BE0();
        c = func_1C3BC0(r, r->f4344);
        c->getA(&up);
        c->getB(&eye);
        func_1CBD00(&ax, &eye, &up);
        func_1CBD00(&fwd, &tgt, &up);
        pv.x = ax.z;
        pv.y = ax.y;
        pv.z = -ax.x;
        if (func_1CBA90(&ax, &fwd) >= 0.0f) {
            func_291110(p, 0x52, 0, 1);
            func_291110(p, 0x53, 0, 1);
        } else {
            func_291110(p, 0x52, 1, 1);
            func_291110(p, 0x53, 1, 1);
            t = p->f37C;
            if (t % 5 == 0) {
                j = (t % 10) != 0;
                if (func_1CBA90(&pv, &fwd) >= 0.0f) {
                    id = (u16)(j + 0x52);
                    func_290F60(p, id, 0xC, 0xD6);
                    func_290F50(p, id, 2, 0xD6, 0, 0.1f);
                    func_290690(p, id, 0.0f, 0.1f, 1.0f);
                    func_28F930(p, id, 0xC0, 0);
                    func_28F850(p, id, -0x1C, 0);
                } else {
                    id = (u16)(j + 0x52);
                    func_290F60(p, id, 0x1D8, 0xD6);
                    func_290F50(p, id, 0x1E2, 0xD6, 0, 0.1f);
                    func_290690(p, id, 0.0f, 0.1f, 1.0f);
                    func_28F930(p, id, 0xA4, 0);
                    func_28F850(p, id, 0x1C, 0);
                }
            }
        }
    }
}
