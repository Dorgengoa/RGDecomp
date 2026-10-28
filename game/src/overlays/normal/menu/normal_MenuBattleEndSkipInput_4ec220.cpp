/* rgp:protos */
#line 1
/* === SESSION 71 (2026-09-21, SOLO): 138 bad -> MATCH.  Read against the
 * listing; five edits (build/wf-normal/s71/b1..b6.py):
 *  - `lift = 0;` restored to right after `ctx = func_1FEDE0();` (s31's move
 *    deck had parked it after normal_MenuBattleEndItemRowsShow_4ea890(o), where it is DEAD and the
 *    loop read it uninitialised).  +1 word, as s65 measured.
 *  - `if (o->f004 <= 0) { if (f02C[i].f004) 0x14 } else { 0x15 }` -- retail
 *    lays the 0x14 arm out as the fall-through (bgtzl to the 0x15 call).
 *  - `k3 = k * 3;` named at the top of the k loop (retail computes it before
 *    the normal_D_00527000[k] load and derives +3/+4/+5 from it).
 *  - `mv = ob->measure(...)` as an s32 and `(f32)mv` at the f02C store: fills
 *    retail's mtc1/cvt hazard slot with the f02C load, fv in $f0.
 *  - statement 6's element pointer is INTEGER arithmetic:
 *    `r = (Rec *)((s32)o->f02C + (u32)i * 0x34);` -- `&o->f02C[(u32)i]` breaks
 *    the CSE with $s4 (right shape, +2 words elsewhere absorbed) but colours
 *    base/index v0/v1 the wrong way round; `(u8 *)` arithmetic is the same
 *    object as the array form, and without the `(u32)` it is 2 words short.
 * Everything below predates this session. */
/* === SESSION 65 (2026-09-15, SOLO): 141 -> 138 bad, still 403 words EXACT.
 * ONE EDIT INSTALLED, ONE MEASURED AND HELD BACK.
 *
 * INSTALLED: `if (o->f00C < o->f008)` -> `if (o->f008 > o->f00C)`.  Retail
 * loads 0x8 BEFORE 0xC (`lw $3,0x8($19) / lw $2,0xC($19) / slt $1,$2,$3` at
 * 0x004EC474); the operands of a `<` are evaluated left to right, so the
 * SPELLING picks the load order.  -3 bad, length unchanged.
 *
 * ★ HELD BACK, and it is a [[uninit-local-draft-screen]] WRONG SOURCE:
 * `lift` is READ in the `for (i...)` loop (`lift + 0x3D + i*0x2A`) before it
 * is ever written -- our only `lift = 0;` is AFTER that loop.  Retail writes
 * it at 0x004EC4C0, `daddu $18,$0,$0`, immediately after
 * `ctx = func_1FEDE0();` and before the loop, and $18 IS lift (`addiu
 * $18,$0,0x6` = `lift = 6`, `addiu $7,$18,0x3D` = `lift + 0x3D`).  Adding
 *     ctx = func_1FEDE0();
 *     lift = 0;                <- HERE
 * is **+1 word (0x650 vs 0x64c)** and the unit stops being scoreable, which
 * is why it is not installed.  Per that lever the fix is length-wrong ALONE
 * and needs a -1 partner.
 *
 * ⚠ THE PARTNER IS NAMED AND IT IS NOT A RELOAD.  With `lift = 0;` in, the
 * whole opcode histogram is +1 lw, +1 nop, -2 sll, and mdiff's FIRST hunk is
 * exact: retail 0x004EC570 fills the `mtc1 $2,$f0` -> `cvt.s.w $f0,$f0`
 * HAZARD GAP with `lw $2,0x2C($19)` (the next statement's `o->f02C` load);
 * we emit a NOP there and load later.  Four schedule arms (moving
 * `r = &o->f02C[i];` above or between the two calls, writing the f028 store
 * through `o->f02C[i]`, an intermediate `(s32)` cast) are ALL still +1.
 * Six arms that delete an `o->f02C` RELOAD by reading through `r` instead
 * (`r->f02C = fv`, `r->f004 != 0` at either site, dropping a redundant
 * `r = &o->f02C[i];`) are each -2, i.e. 402 -- they overshoot.
 * => the -1 has to FILL THAT NOP, not remove a load.
 */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_id_L492_T493_DEREF_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 403 words, 143 bad   after: 403 words, 141 bad   (retail 403 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_lift_L454_T484_SAFE_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 404 words, ? bad   after: 403 words, 143 bad   (retail 403 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x004EC220 -- 1616 B.  Written FRESH in s31 (lane a4).
 * Shares Scene/Rec/Slot/Obj with the merged normal_MenuBattleEndOpen_4ec990.cpp.
 * The lw $25,0x444($25) + jalr $25 pair is a C++ virtual, vptr at offset 0,
 * slot index (0x444-8)/4 = 271.  Hence .cpp.
 */
struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 measure(s32 a) { return VCM(s32, (void *, s32), 0x444, a); }
};

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

typedef struct Slot {
    f32 f000;
    f32 f004;
    s16 f008;
    u8  pad00A[2];
} Slot;

typedef struct Blk {
    f32 f000;
    f32 f004;
    s32 f008;
    u8  pad00C[4];
} Blk;

typedef struct Fx {
    f32 f000;
    f32 f004;
    u8  pad008[8];
    f32 f010;
    f32 f014;
    u8  pad018[8];
} Fx;

typedef struct Scene {
    s32   f000;
    s32   f004;
    s32   f008;
    s32   f00C;
    s32   f010;
    u8    f014[0x18];
    Rec  *f02C;
    Slot  f030[9];
    u8    f09C[0x10];
    Blk   f0AC[4];
    Fx   *f0EC;
    s8    f0F0[9];
    s8    f0F9[9];
    s16   f102;
    s16   f104;
    s16   f106;
    void *f108;
    s16   f10C;
    s16   f10E;
    u8    f110;
    u8    f111;
    u8    f112;
    u8    f113;
    u8    f114;
} Scene;

typedef struct Elem {
    s16 f000;
    u8  pad002[2];
    s16 f004;
    u8  pad006[0x1A];
    s16 f020;
} Elem;

typedef struct Handle { u8 pad000[0x20]; Elem *f020; } Handle;

typedef struct Ctx { u8 pad000[0x14]; void *f014; } Ctx;

extern "C" s32 normal_D_00527000[];
extern "C" void *D_004843E0;
extern "C" u8 D_004B2570[];

extern "C" s32     PadIsTriggered_1839f0(void *a, s32 b);
extern "C" Ctx    *GetGameData_1fede0(void);
extern "C" Handle *UiFindWidget_290460(void *a, u16 id);
extern "C" void    UiFadeWidgetAlpha_290690(void *a, u16 id, f32 x, f32 y, f32 z);
extern "C" void    UiSetWidgetAlpha_2907a0(void *a, u16 id, f32 v);
extern "C" void    UiSetWidgetPos_290f60(void *a, u16 id, s32 x, s32 y);
extern "C" void    UiSetWidgetsVisibleById_291110(void *a, u16 id, s32 c, s32 d);
extern "C" Obj    *CharaMgrPoolFindById_3a8c60(void *a, s32 i);
extern "C" void    SoundPlayScaledVolume_1b9520(void *a, s32 b, s32 c, f32 v);
extern "C" void    normal_MenuBattleEndItemRowsShow_4ea890(Scene *o);

extern "C" void normal_MenuBattleEndSkipInput_4ec220(Scene *o);

void normal_MenuBattleEndSkipInput_4ec220(Scene *o) {
    Ctx *ctx;
    Obj *ob;
    Elem *p;
    Elem *q;
    Fx *fx;
    Rec *r;
    s32 ok;
    s32 cnt;
    s32 i;
    s32 k;
    s32 id;
    s32 lift;
    s32 n;
    s32 k3;
    f32 fv;
    s32 mv;

    ok = 0;
    if (PadIsTriggered_1839f0(D_004B2570, 0x40) != 0) {
        ok = 1;
    }
    if (o->f112 != 0) {
        cnt = 0;
        for (i = 0; i < o->f008; i = i + 1) {
            if (o->f030[i].f008 == 1) {
                cnt = cnt + 1;
            }
        }
        if (o->f000 == 4) {
            if (cnt == 0) {
                o->f010 = o->f010 - 1;
            }
        }
        if (o->f010 <= 0 && o->f000 < 5) {
            o->f010 = 0;
            o->f000 = 5;
            o->f10E = 0;
            if (o->f114 == 0) {
                o->f10E = 0x14;
            }
        }
    } else {
        if (o->f000 == 4 || o->f000 == 0xFF) {
            o->f112 = 1;
            o->f000 = 4;
        } else if (o->f000 < 5) {
            if (o->f000 >= 3) {
                if (ok != 0) {
                    if (o->f000 == 4) {
                        o->f000 = 4;
                    } else if (o->f110 == 1) {
                        if (o->f000 < 4) {
                            o->f104 = 1;
                            o->f106 = 0;
                            o->f010 = 0x14;
                        }
                    }
                }
            }
        }
        if (o->f112 == 0 && o->f104 == 1) {
            if (o->f000 >= 3 && o->f000 < 5) {
                o->f106 = (s16)(o->f106 + 1);
                if (ok != 0 || o->f106 >= 0xC) {
                    p = UiFindWidget_290460(o->f014, 0xF)->f020;
                    p->f004 = 0x100;
                    UiFadeWidgetAlpha_290690(o->f014, 0x10, 1.0f, 0.5f, -1.0f);
                    UiFadeWidgetAlpha_290690(o->f014, 0x13, 1.0f, 0.5f, -1.0f);
                    p->f020 = p->f004;
                    q = UiFindWidget_290460(o->f014, 0x12)->f020;
                    q->f000 = -0x100;
                    q->f004 = 0x100;
                    if (o->f008 > o->f00C) {
                        UiSetWidgetsVisibleById_291110(o->f014, 0x14, 1, 1);
                    }
                    q = UiFindWidget_290460(o->f014, 0x14)->f020;
                    q->f000 = 0;
                    q->f004 = 0xFC;
                    ctx = GetGameData_1fede0();
                    lift = 0;
                    for (i = 0; i < o->f008; i = i + 1) {
                        id = (i * 3) + 0x15;
                        UiSetWidgetAlpha_2907a0(o->f014, id, 1.0f);
                        if (i >= o->f00C) {
                            lift = 6;
                        }
                        UiSetWidgetPos_290f60(o->f014, id, 0xC, lift + 0x3D + (i * 0x2A));
                        ob = CharaMgrPoolFindById_3a8c60(ctx->f014, o->f02C[i].f000);
                        mv = ob->measure(o->f02C[i].f00C);
                        r = &o->f02C[i];
                        r->f028 = (f32)r->f014;
                        o->f02C[i].f02C = (f32)mv;
                        r = &o->f02C[i];
                        r->f020 = r->f00C;
                        if (o->f02C[i].f004 != 0) {
                            SoundPlayScaledVolume_1b9520(D_004843E0, 0x13, 0, 1.0f);
                        }
                        r = (Rec *)((s32)o->f02C + (u32)i * 0x34);
                        if ((r->f00C - r->f008) != 0) {
                            o->f0F9[i] = 1;
                            o->f030[i].f008 = 1;
                            if (o->f004 <= 0) {
                                if (o->f02C[i].f004 != 0) {
                                    SoundPlayScaledVolume_1b9520(D_004843E0, 0x14, 0, 1.0f);
                                }
                            } else {
                                SoundPlayScaledVolume_1b9520(D_004843E0, 0x15, 0, 1.0f);
                            }
                            o->f004 = o->f004 + 1;
                        }
                    }
                    normal_MenuBattleEndItemRowsShow_4ea890(o);
                    for (k = 0; k < 4; k = k + 1) {
                        k3 = k * 3;
                        n = normal_D_00527000[k];
                        if (n > 0 || n == -0xFF) {
                            id = k3 + 5;
                            UiSetWidgetPos_290f60(o->f014, id, 0xF2, (k * 0x2A) + 0x35);
                            UiSetWidgetsVisibleById_291110(o->f014, id, 1, 1);
                            p = UiFindWidget_290460(o->f014, id)->f020;
                            p->f000 = -0xF0;
                            id = k3 + 3;
                            p->f004 = 0xFC;
                            UiSetWidgetAlpha_2907a0(o->f014, id, 1.0f);
                            o->f0AC[k].f000 = (f32)((k * 0x2A) + 0xE);
                            o->f0AC[k].f004 = o->f0AC[k].f000;
                            o->f0AC[k].f008 = 0;
                            UiSetWidgetPos_290f60(o->f014, id, 0xF, (s32)o->f0AC[k].f000);
                            UiSetWidgetAlpha_2907a0(o->f014, k3 + 4, 1.0f);
                        }
                    }
                    UiSetWidgetPos_290f60(o->f014, 2, 0x103, 0xD0);
                    UiSetWidgetAlpha_2907a0(o->f014, 2, 1.0f);
                    o->f000 = 0xFF;
                    for (i = 0; i < o->f008; i = i + 1) {
                        if (i < o->f00C) {
                            fx = &o->f0EC[i];
                            if (fx->f004 > 0.0f) {
                                fx->f000 = 1.0f;
                            }
                            fx = &o->f0EC[i];
                            if (fx->f014 > 0.0f) {
                                fx->f010 = 1.0f;
                            }
                        }
                    }
                }
            }
        }
    }
    if (o->f113 != 0) {
        o->f113 = 0;
    }
}
