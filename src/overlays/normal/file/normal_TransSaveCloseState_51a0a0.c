#include "types.h"
/* normal 0x0051A0A0 -- the outer tick for normal_FUN_0051A1A0's state word
 * D_004847F8 (gp - 0x978, ADDRESS-TAKEN so it must stay <= 8 B / small data).
 */

extern void *D_004847D4;          /* gp - 0x99C */
extern void *D_004847D0;          /* gp - 0x9A0 */
extern void *D_00484794;          /* gp - 0x9DC */
extern s32   D_004847F8;          /* gp - 0x978 */

extern void  func_376B10(s32 a);
extern void  func_2910A0(void *w, u16 id, s32 *outX, s32 *outY);
extern void  func_290F60(void *w, u16 id, s32 x, s32 y);
extern void  func_28BDF0(void *p, s32 a);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern s32   normal_TransMenuWidgetListShow_514a10(s32 a);
extern s32   normal_TransSaveCloseSlide_51a1a0(s32 *p);

s32 normal_TransSaveCloseState_51a0a0(void *a, s32 b)
{
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;
    s32 st;

    if (b != 0) {
        func_376B10(0);
        D_004847F8 = 0;
    }
    normal_TransSaveCloseSlide_51a1a0(&D_004847F8);
    func_2910A0(D_004847D4, 0x753B, &x, &y);
    if (x == -0x12) {
        if (y == 0xC) {
            func_290F60(D_004847D4, 0x753B, -0x4A, 0x4F);
            func_290F60(D_004847D4, 0x7536, -0x45, 0x53);
        }
    }
    st = D_004847F8;
    if (st == 3) {
        D_004847F8 = 4;
    } else if (st == 4) {
        func_2910A0(D_004847D4, 0x753B, &x2, &y2);
        if (x2 == -0x4A) {
            func_28BDF0(D_00484794, -1);
            D_00484794 = 0;
            normal_TransMenuWidgetListShow_514a10(0);
            func_28EDE0(D_004847D0, 3, 0);
        }
    }
    return 1;
}
