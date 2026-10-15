#include "types.h"

/* title.bin overlay, 0x004ECBC0 -- scene construction.  Six allocations off
 * the same context, each one's result stored in the NEXT call's delay slot,
 * then a long block of gp-relative resets.
 *
 * title_FUN_004ED330 returns its own argument, so the guarded call is written
 * back into the same local -- that is what lets ONE store serve both paths.
 *
 * The three zero stores go through a LOCAL and the fourth re-reads the global.
 * Spelled `D_00484158->f = 0` three times, mwcc reloads the pointer before each
 * one -- a store through it may alias the pointer itself -- which is two words
 * long; the local removes the alias and the re-read after the call is what the
 * call boundary forces anyway.
 *
 * PARKED at 2 words: retail issues `lw $6, D_00484158` and THEN
 * `lwc1 $f0, D_0047D7E0`, we issue them the other way round.  Everything else
 * matches.  Getting from 12 words to 2 took two real levers -- the local for
 * the aliasing pointer, and reading the float into a local BETWEEN the call and
 * the store through that pointer (a store through a pointer blocks the load's
 * hoist, so with the read written after it mwcc cannot move it up) -- and the
 * last two are the same "retail hoists a gp float load" residue that parks
 * title_FUN_004EFB90, ECD40, EDCF0 and E9F00.  Measured: inline 12,
 * +local pointer 12, +Req field order 8, +float read before the store 2,
 * pointer read first 2, no float local 8.
 *
 * CLOSED 2026-08-25 by the pragma below: with copy propagation off, mwcc
 * stops forwarding the pointer load past the float load and the two issue in
 * retail's order.  Found by t_knob.py's recognised-pragma sweep (116 variants:
 * 109 inert, this one 0 bad; opt_dead_assignments off yields the identical
 * object).  The pragma is per-TU and does NOT generalise to the other three
 * hoist units -- it is inert on EFB90/ECD40/EDCF0, measured.
 */
#pragma opt_propagation off

typedef struct Node_title_FUN_004ecbc0 {
    s16 field000;      /* +0x0 */
    u8 pad002[0x2];
    s32 field004;      /* +0x4 */
    void *field008;    /* +0x8 */
} Node_title_FUN_004ecbc0;

typedef struct Req_title_FUN_004ecbc0 {
    u8 pad000[0x4];
    s32 field004;      /* +0x4  */
    s32 field008;      /* +0x8  */
    u8 pad00C[0x8];
    s32 field014;      /* +0x14 */
    u8 pad018[0x8];
} Req_title_FUN_004ecbc0;

extern void *D_00484150;
extern void *D_00484154;
extern Node_title_FUN_004ecbc0 *D_00484158;
extern void *D_0048415C;
extern void *D_00484160;
extern s32 D_00484164;
extern void *D_00484170;
extern void *D_00484174;
extern s16 D_00484178;
extern s16 D_0048417C;
extern s32 D_00484180;
extern void *D_00484184;
extern s16 D_00484188;
extern s16 D_0048418C;
extern s16 D_00484194;
extern s16 D_00484198;
extern s16 D_004841A4;
extern u8 D_004841A8;
extern s16 D_004803A8;
extern s16 D_004803AC;
extern f32 D_004803B0;
extern f32 D_004803B4;
extern void *D_004803E0;
extern f32 D_0047D7E0;

extern void func_372F80(void);
extern void *func_14E230(s32 a, void *b);
extern void *title_TitleMenuObjCtor_4ed330(void *o);
extern void *func_206A40(void);
extern void func_42B650(void *a, s32 b);
extern void title_TitleMenuObjResetMaybe_4ed320(void *a);
extern void *func_42C950(void *a, s32 b);
extern void func_3730F0(void);
extern void func_373040(void);
extern void title_TitleLoadDoneReset_4ef3b0(void);
extern void *func_1165A0(Req_title_FUN_004ecbc0 *r);
extern void func_12C648(void);

s32 title_TitleObjectsCreate_4ecbc0(void *a, void *b)
{
    Req_title_FUN_004ecbc0 req;
    void *p;
    void *scene;
    Node_title_FUN_004ecbc0 *n;
    void *r;
    f32 v;
    Node_title_FUN_004ecbc0 *n2;

    D_00484150 = a;
    D_00484154 = b;
    D_004803E0 = (void *)-1;
    func_372F80();
    D_00484184 = func_14E230(0x528, D_00484150);
    D_00484170 = func_14E230(0x14, D_00484150);
    D_00484158 = func_14E230(0xC, D_00484150);
    D_0048415C = func_14E230(0x24, D_00484150);
    p = func_14E230(0x1C, D_00484150);
    if (p != 0) {
        p = title_TitleMenuObjCtor_4ed330(p);
    }
    D_00484160 = p;
    D_00484174 = func_14E230(0x14, D_00484150);
    scene = func_206A40();
    func_42B650(scene, 2);
    title_TitleMenuObjResetMaybe_4ed320(D_00484160);
    n = D_00484158;
    n->field004 = 0;
    n->field008 = 0;
    n->field000 = 0;
    r = func_42C950(scene, 9);
    n2 = D_00484158;
    v = D_0047D7E0;
    n2->field008 = r;
    D_004803A8 = 1;
    D_004803B4 = v;
    D_004803AC = 2;
    D_004803B0 = 1.0f;
    D_00484188 = 0;
    D_0048418C = 0;
    D_00484194 = 0;
    D_00484198 = 0;
    D_00484164 = 0;
    D_00484178 = 0;
    D_0048417C = 0;
    D_00484180 = 0;
    D_004841A4 = 0;
    D_004841A8 = 0;
    func_3730F0();
    func_373040();
    title_TitleLoadDoneReset_4ef3b0();
    req.field008 = 0xB;
    req.field014 = 0;
    req.field004 = 1;
    D_004803E0 = func_1165A0(&req);
    func_12C648();
    return 1;
}
