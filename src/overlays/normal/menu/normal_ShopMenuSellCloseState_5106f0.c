#include "types.h"
/* normal 0x005106F0 -- a pure CALL LIST on the two panels D_004845C8 /
 * D_004845CC: ten setup calls under the `b` guard, then a float test on the
 * 0x32 slot that gates the 0x19 re-arm and the 0x7532 post.
 *
 * `$4` is never read -- the f(void *, s32) state-handler family, returns 1.
 * `lui 0xBD80 / mtc1` is -0.0625f materialised inline (low half zero); every
 * gp `lwc1` is a constant whose low half is NOT zero.
 * func_290E00 takes FIVE ints ($4-$8, the fifth in $8 -- EABI) and TWO floats
 * ($f12/$f13); `mtc1 $0,$f13` is the second one being 0.0f, not a leftover.
 * The `ld $31` in the `bc1fl` delay slot is the shared epilogue duplicated by
 * the scheduler, not a second return.
 * The 0x93 store MUST go through a NAMED Hold* local.  Written as ONE
 * expression (`func_290460(..)->f020->f008 = 0x93;`) mwcc evaluates the RHS
 * first, so 0x93 has to survive the call: it lands in $16 in the delay slot
 * and drags in an `sq $16`/`lq $16` pair and a 0x20 frame -- TWO WORDS LONG
 * (len 0x178 vs 0x170).  Naming the pointer puts the constant AFTER the call
 * in $3 and the function needs no callee-saved register at all.  A named
 * Bar* (`..->f020` in the local) instead is 3 bad words, not a fix.
 */

typedef struct Bar  { u8 pad000[0x8];  s16 f008; } Bar;
typedef struct Hold { u8 pad000[0x20]; Bar *f020; } Hold;

extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845C8;          /* gp - 0xBA8  */
extern void *D_004845CC;          /* gp - 0xBA4  */
extern f32   D_0047D460;          /* gp - 0x7D10 */
extern f32   D_0047D49C;          /* gp - 0x7CD4 */
extern f32   D_0047D4AC;          /* gp - 0x7CC4 */
extern f32   D_0047D4B0;          /* gp - 0x7CC0 */
extern f32   D_0047D4B4;          /* gp - 0x7CBC */

extern void  func_28EDE0(void *w, s32 id, s32 a);
extern Hold *func_290460(void *w, u16 id);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);
extern f32   func_290770(void *w, u16 id);
extern void  func_290E00(void *w, u16 id, s32 a, s32 b, s32 c, f32 x, f32 y);
extern void  func_290F60(void *w, u16 id, s32 a, s32 b);
extern void  func_291110(void *w, u16 id, s32 a, s32 b);

s32 normal_ShopMenuSellCloseState_5106f0(void *a, s32 b)
{
    Hold *h;

    if (b != 0) {
        func_290690(D_004845C8, 0x33, 0.0f, D_0047D49C, -1.0f);
        func_290E00(D_004845C8, 0x32, 0x200, 0x49, 3, D_0047D4B0, 0.0f);
        func_290690(D_004845C8, 0x32, 0.0f, -0.0625f, -1.0f);
        func_290690(D_004845CC, 0x57, 0.0f, D_0047D4AC, -1.0f);
        func_290690(D_004845CC, 0x5B, 0.0f, D_0047D4AC, -1.0f);
        func_290690(D_004845C8, 0x3C, 0.0f, D_0047D460, -1.0f);
        func_290F60(D_004845C8, 0xA, -0x4A, 0x58);
        func_290F60(D_004845C8, 0x7, -0x45, 0x5C);
        func_290690(D_004845C8, 0x17, 1.0f, D_0047D4B4, -1.0f);
        h = func_290460(D_004845C8, 0x17);
        h->f020->f008 = 0x93;
    }
    if (func_290770(D_004845C8, 0x32) == 0.0f) {
        func_291110(D_004845C8, 0x19, 0, 1);
        func_28EDE0(D_004845C4, 0x7532, 0);
    }
    return 1;
}
