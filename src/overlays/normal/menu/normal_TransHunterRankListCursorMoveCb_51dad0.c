#include "types.h"
/* normal 0x0051DAD0 -- twin of normal_FUN_0051F210 (same shape, different
 * ids and a func_28FD10 tail instead of func_28FC90).  The gp latch
 * D_004848B4 memoises p->f12 and gates the re-layout.
 * ARM: the float product is a NAMED local here; the twin spells it inline. */

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

extern void func_28FD10(void *w, u16 id, s32 a, s32 b, s32 k);
extern void func_290F50(void *p, u16 id, s32 c, s32 d, s32 e, f32 x);
extern void normal_TransHunterRankListFill_51d820(s32 a);

s32 normal_TransHunterRankListCursorMoveCb_51dad0(Box *p)
{
    f32 m;

    func_28FD10(D_00484710, 0x7642, 0x1E, p->f02 + p->f12 * p->f06, 0);
    if (D_004848B4 == p->f12) {
        m = (f32)p->f16 * D_004848B8;
        func_290F50(D_00484710, 0x7644, 0, (s32)m, 0, D_0047D34C);
        normal_TransHunterRankListFill_51d820(p->f16);
    }
    D_004848B4 = p->f12;
    return 1;
}
