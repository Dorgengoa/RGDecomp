#include "types.h"

/* title.bin overlay, 0x004EEB90 -- the "press start" prompt: either fade the
 * whole scene out, or repaint the two prompt strings, then poll for the press.
 *
 * Both `beql` guards carry the NEXT block's load in their delay slots, so they
 * are ordinary tests rather than epilogue merges.
 *
 * ★ `return 1` INSIDE both arms of the D_004841F0 test was worth 5 words -> 2:
 * with one return after the join mwcc hoists `ld $31` into each arm and
 * materialises the constant once, where retail materialises it twice and shares
 * the epilogue.  Same corollary as title_FUN_004EE8F0.
 *
 * PARKED at 2 words: retail's last guard is a PLAIN `bc1f` with an empty delay
 * slot and ours is `bc1fl` carrying the target's `addiu $2,1`.  Adding a
 * `return 1` inside that arm too changes nothing, and lifting the else-if into
 * a separate `if` costs two more words.
 */

extern s16 D_004841F0;
extern void *D_004841E0;
extern void *D_004841E4;
extern f32 D_0047D518;
extern f32 D_0047D548;
extern f32 D_0047D55C;
extern f32 D_0047D560;
extern f32 D_0047D564;
extern f32 D_0047D568;

extern void func_376B10(s32 a);
extern void *func_1F5BE0(void);
extern void func_1CF730(void *a, s32 b, f32 x, f32 y, f32 z);
extern void func_290690(void *a, s32 b, f32 x, f32 y, f32 z);
extern void func_290F50(void *a, s32 b, s32 x, s32 y, s32 e, f32 f);
extern void func_37BB70(void);
extern void title_TitleSetNoAnalogPause_4f13b0(s32 a);
extern s32 func_1CF6C0(void *a);
extern void title_TitleSceneOverlayModeOff_4eaa00(void);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern f32 func_290770(void *a, s32 b);

s32 title_TitleLoadClose_4eeb90(s32 a, s32 b)
{
    if (b != 0) {
        func_376B10(0);
        if (D_004841F0 != 0) {
            func_1CF730(func_1F5BE0(), 0x3C, 0.0f, 0.0f, 0.0f);
        } else {
            func_290690(D_004841E4, 0x8, 0.0f, D_0047D55C, -1.0f);
            func_290690(D_004841E4, 0x7, 0.0f, D_0047D560, -1.0f);
            func_290F50(D_004841E4, 0x8, 0xC8, 0, 0, D_0047D564);
            func_290690(D_004841E4, 0xA, 0.0f, D_0047D548, -1.0f);
            func_290F50(D_004841E4, 0xF, -0x12, 0xC, 0, D_0047D518);
            func_290F50(D_004841E4, 0xE, -0xF, 0xF, 0, D_0047D518);
            func_290690(D_004841E4, 0xF, 0.0f, D_0047D568, -1.0f);
            func_290690(D_004841E4, 0xE, 0.0f, D_0047D568, -1.0f);
        }
        func_37BB70();
        title_TitleSetNoAnalogPause_4f13b0(0);
    }
    if (D_004841F0 != 0) {
        if (func_1CF6C0(func_1F5BE0()) != 0) {
            title_TitleSceneOverlayModeOff_4eaa00();
            D_004841F0 = 2;
            func_28EDE0(D_004841E0, 6, 0);
            return 1;
        }
    } else if (func_290770(D_004841E4, 7) <= 0.0f) {
        title_TitleSceneOverlayModeOff_4eaa00();
        func_28EDE0(D_004841E0, 4, 0);
    }
    return 1;
}
