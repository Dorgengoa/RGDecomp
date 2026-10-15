#include "types.h"
/* normal 0x0050DE30 -- the 0x16/0x1A/0x33 panel opener on the gp handle
 * D_004845C8.  f(void *, s32), `$4` never read, guard on `b`, returns 1.
 *
 * `lui 0xBD800000` is the inline literal -0.0625f and `lui 0xBF800000`
 * -1.0f; only the three gp floats come from small data.
 * `mtc1 $0,$f1 / c.eq.s $f1,$f0 / bc1fl` is `== 0.0f` on func_290770.
 * func_290460's return is dereferenced twice (`lw 0x20`, then `sh` at 8) and
 * must be NAMED in a local: written inline, mwcc evaluates the assignment's
 * constant RHS BEFORE the call, pinning 0x93 in $16 and buying a whole
 * callee-saved save area (2 words).  Splitting the call out is the fix.
 */

typedef struct Node { u8 pad00[8]; s16 f08; } Node;
typedef struct Slot { u8 pad00[0x20]; Node *f20; } Slot;

extern f32   D_0047D4B0;          /* gp - 0x7CC0 */
extern f32   D_0047D4C0;          /* gp - 0x7CB0 */
extern f32   D_0047D4C4;          /* gp - 0x7CAC */
extern void *D_004845C4;          /* gp - 0xBAC  */
extern void *D_004845C8;          /* gp - 0xBA8  */

extern void  func_28EDE0(void *p, s32 id, s32 a);
extern Slot *func_290460(void *p, u16 id);
extern void  func_290690(void *p, u16 id, f32 x, f32 y, f32 z);
extern void  func_290E00(void *p, u16 id, s32 c, s32 d, s32 e, f32 x, f32 y);
extern void  func_290F60(void *p, u16 id, s32 c, s32 d);
extern f32   func_290770(void *p, u16 id);
extern void  func_291110(void *p, u16 id, s32 c, s32 d);

s32 normal_ShopMenuBuyListCloseState_50de30(void *a, s32 b)
{
    Slot *s;

    if (b != 0) {
        func_290690(D_004845C8, 0x33, 0.0f, D_0047D4C0, -1.0f);
        func_290E00(D_004845C8, 0x1A, 0x200, 0x4A, 3, D_0047D4B0, 0.0f);
        func_290690(D_004845C8, 0x1A, 0.0f, -0.0625f, -1.0f);
        func_290F60(D_004845C8, 9, -0x4A, 0x32);
        func_290F60(D_004845C8, 6, -0x45, 0x36);
        func_290690(D_004845C8, 0x16, 1.0f, D_0047D4C4, -1.0f);
        s = func_290460(D_004845C8, 0x16);
        s->f20->f08 = 0x93;
    }
    if (func_290770(D_004845C8, 0x1A) == 0.0f) {
        func_291110(D_004845C8, 0x19, 0, 1);
        func_28EDE0(D_004845C4, 0x7532, 0);
    }
    return 1;
}
