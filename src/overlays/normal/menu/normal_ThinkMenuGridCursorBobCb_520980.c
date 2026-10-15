#include "types.h"
/* normal 0x00520980 -- the two-argument forwarder onto normal_ThinkMenuGridCursorBobToCell_5209c0
 * with both trailing counters zero, then the shared 0x753B notify. */

extern const u8 D_00528060[];

extern s32  normal_ThinkMenuGridCursorBobToCell_5209c0(void *a, void *b, s32 c, s32 d);
extern void func_28D820(const u8 *p, s32 id);

s32 normal_ThinkMenuGridCursorBobCb_520980(void *a, void *b)
{
    normal_ThinkMenuGridCursorBobToCell_5209c0(a, b, 0, 0);
    func_28D820(D_00528060, 0x753B);
    return 1;
}
