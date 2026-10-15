#include "types.h"

/* title.bin overlay, 0x004EE640 -- the cursor/scroll step of a list page.
 * Two symmetric blocks, one per direction: a flag bit, a pad poll, a repeat
 * poll, then the position checks.  Every failure in a block branches to the
 * SAME place, so each block is one `&&` chain -- and the first block's checks
 * exit past the second, which makes the two an if/else rather than two ifs.
 *
 * PARKED at 2 words, and they are the BRANCH-LIKELY CONVERSION class: retail's
 * last guard is a plain `beqz` with a `nop`, ours is `beqzl` carrying the
 * shared `addiu $2,1` duplicated out of the target.  Three spellings --
 * guarded body, guarded body with its own `return 1`, and the guard inverted
 * into an early return (that one costs two words) -- leave it unchanged.
 * Same class as title_FUN_004EEB90 (`bc1f`/`bc1fl`) and title_FUN_004EBAF0's
 * second cluster.
 */

typedef struct Obj_title_FUN_004ee640 {
    u8 pad000[0xA];
    s16 field00A;      /* +0xA  */
    u8 pad00C[0x2];
    s16 field00E;      /* +0xE  */
    u8 pad010[0x2];
    s16 field012;      /* +0x12 */
    u8 pad014[0x2];
    s16 field016;      /* +0x16 */
} Obj_title_FUN_004ee640;

typedef struct Sys_title_FUN_004ee640 {
    u8 pad000[0x14];
    s32 field014;      /* +0x14 */
    u8 pad018[0x4];
    s32 field01C;      /* +0x1C */
} Sys_title_FUN_004ee640;

extern Sys_title_FUN_004ee640 *D_004841E8;
extern s32 D_004841FC;
extern s32 D_00484200;
extern const u8 D_004B2570;

extern void title_TitleLoadSlotCursorBob_4edcf0(void *o, void *b, s32 c);
extern s32 func_37B970(void);
extern u8 func_37B9B0(s32 a);
extern void title_TitleLoadShowError_4eeb70(s32 a);
extern s32 func_1839F0(void *a, s32 b);
extern s32 func_183DD0(void *a, s32 b);
extern s32 func_37B500(void *a, s32 b);
extern void func_28E9E0(void *a, s32 b);
extern void title_TitleLoadSlotMoveCb_4ee970(void *o, void *b);
extern void func_3777A0(void *o, s32 b, s32 c);
extern void title_TitleLoadSlotListConfirm_4ee8f0(void *o, void *b);
extern void title_TitleLoadSlotListCancel_4ee8c0(void *o, void *b);
extern void func_376B20(s32 a);

s32 title_TitleLoadSlotListTickCb_4ee640(Obj_title_FUN_004ee640 *o, void *b)
{
    s32 mode;
    s32 moved;

    title_TitleLoadSlotCursorBob_4edcf0(o, b, 0);
    mode = func_37B970();
    if (func_37B9B0(1) == 0 || mode == 6 || mode == 5 || mode == 8) {
        title_TitleLoadShowError_4eeb70(8);
        return 1;
    }
    moved = 0;
    if (func_1839F0((void *)&D_004B2570, 0x2000) != 0) {
        moved = func_37B500(o, 1);
    } else if (func_1839F0((void *)&D_004B2570, 0x8000) != 0) {
        moved = func_37B500(o, 0);
    } else if ((D_004841E8->field014 & 1) != 0 &&
               func_1839F0((void *)&D_004B2570, 0x1000) != 0 &&
               func_183DD0((void *)&D_004B2570, 0x1000) == 0) {
        if (o->field012 == 0 && o->field016 == 0 && o->field00E > 0) {
            o->field012 = o->field00A;
            moved = 1;
            o->field016 = o->field00E - o->field00A;
        }
    } else if ((D_004841E8->field014 & 2) != 0 &&
               func_1839F0((void *)&D_004B2570, 0x4000) != 0 &&
               func_183DD0((void *)&D_004B2570, 0x4000) == 0 &&
               o->field012 == o->field00A &&
               o->field016 == o->field00E - o->field00A &&
               o->field00E > 0) {
        o->field012 = 0;
        moved = 1;
        o->field016 = 0;
    }
    if (moved != 0) {
        if ((D_004841E8->field01C & 1) == 0) {
            func_28E9E0(D_004841E8, 0);
        }
        title_TitleLoadSlotMoveCb_4ee970(o, b);
        func_3777A0(o, 0x45, 0);
    }
    if (func_1839F0((void *)&D_004B2570, D_004841FC) != 0) {
        title_TitleLoadSlotListConfirm_4ee8f0(o, b);
    } else if (func_1839F0((void *)&D_004B2570, D_00484200) != 0) {
        func_376B20(6);
        title_TitleLoadSlotListCancel_4ee8c0(o, b);
    }
    return 1;
}
