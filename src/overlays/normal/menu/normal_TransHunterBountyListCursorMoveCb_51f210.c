#include "types.h"
/* normal 0x0051F210 -- twin of normal_FUN_0051DAD0.
 * ARM: the float product is spelled INLINE here; the twin names it. */

typedef struct Box {
    u8  pad00[0x2];
    s16 f02;
    u8  pad04[0x2];
    s16 f06;
    u8  pad08[0xA];
    s16 f12;
    u8  pad14[0x2];
    s16 f16;
} Box;

extern f32   D_0047D34C;          /* gp - 0x7E24 */
extern s16   D_004848B4;          /* gp - 0x8BC  */
extern f32   D_004848B8;          /* gp - 0x8B8  */
extern void *D_00484710;          /* gp - 0xA60  */

extern void func_28FC90(void *w, s32 id, s32 v, s32 k);
extern void func_290F50(void *p, u16 id, s32 c, s32 d, s32 e, f32 x);
extern void normal_TransHunterBountyListFill_51efe0(s32 a);

s32 normal_TransHunterBountyListCursorMoveCb_51f210(Box *p)
{
    func_28FC90(D_00484710, 0x7637, p->f02 + p->f12 * p->f06, 0);
    if (D_004848B4 == p->f12) {
        func_290F50(D_00484710, 0x763E, 0,
                    (s32)((f32)p->f16 * D_004848B8), 0, D_0047D34C);
        normal_TransHunterBountyListFill_51efe0(p->f16);
    }
    D_004848B4 = p->f12;
    return 1;
}
