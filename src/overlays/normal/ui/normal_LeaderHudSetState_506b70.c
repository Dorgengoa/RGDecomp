#include "types.h"
/* normal 0x00506B70 -- the `bnel` delay slot moves the handle into $4 for the
 * guarded call; $16 holds the id across func_289B40. */
extern void *func_289B40(void *p);
extern void  func_28EDE0(void *w, s32 id, s32 a);
extern s32 normal_LeaderHudSetState_506b70(void *p, s32 id);
s32 normal_LeaderHudSetState_506b70(void *p, s32 id)
{
    void *w = func_289B40(p);
    if (w == 0) {
        return 0;
    }
    func_28EDE0(w, id, 0);
    return 1;
}
