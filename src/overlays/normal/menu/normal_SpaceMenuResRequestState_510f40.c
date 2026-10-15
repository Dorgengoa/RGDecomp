#include "types.h"
/* normal 0x00510F40 -- loads the map-marker table and shows widget 3 if it
 * arrived.  Pass-33 LIST rank: 132 bytes, 33 instructions, ONE conditional
 * branch, 6 calls.  Both exits return 1; the guard is an EARLY return on the
 * failure value, which is what retail falls through into. */

extern void *D_004802BC;          /* gp - 0x4EB4 */
extern s32   D_00480670;          /* gp - 0x4B00 */
extern s8    D_00480674;          /* gp - 0x4AFC */
extern void *D_004846B4;          /* gp - 0xABC  */

extern void  func_158AC0(void *h, s32 id);
extern void *func_15DE40(void);
extern void  func_1CD670(void *h);
extern s32   func_1CD870(void *h, void *id, s32 a);
extern void *func_1F59D0(void);
extern void  func_28EDE0(void *p, s32 id, s32 a);

extern s32 normal_SpaceMenuResRequestState_510f40(void);

s32 normal_SpaceMenuResRequestState_510f40(void)
{
    void *q;

    q = func_1F59D0();
    func_158AC0(func_15DE40(), 0x32D);
    D_00480670 = -1;
    D_00480674 = 0;
    D_00480670 = func_1CD870(q, D_004802BC, 0);
    func_1CD670(q);
    if (D_00480670 == -1) {
        return 1;
    }
    func_28EDE0(D_004846B4, 3, 1);
    return 1;
}
