/* rgp:protos */
#define RGP_SELF_ActCfgTableFindCallNameByFlags_2207b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Walk the 0x10-stride table at +0x30 (count = s16 at +0x64) looking for a
   key/mask hit; on miss recurse into the parent unless the s16 at +0x12 is
   the 0x7FFF sentinel.  The two `beql`s in the tail are the two
   `return 0`s. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
s32 ActCfgTableFindCallNameByFlags_2207b0(s32 arg0, s32 arg1, long long arg2);

s32 ActCfgTableFindCallNameByFlags_2207b0(s32 arg0, s32 arg1, long long arg2)
{
    s32 p;
    s32 i;
    long long a;
    s32 next;

    p = *(s32 *)(arg0 + 0x30);
    if (p != 0) {
        for (i = 0; i < *(s16 *)(arg0 + 0x64); i++, p += 0x10) {
            a = ActInfoCallGetMask_2310a0(p);
            if (arg1 == ActInfoCallGetFlags_2310c0(p)) {
                if (a == (a & arg2)) {
                    return ActInfoCallGetName_2310d0(p);
                }
            }
        }
    }
    if (*(s16 *)(arg0 + 0x12) != 0x7FFF) {
        next = ActionMgrGetGlobalTable_234850(((s32)GetActionMgr_1fdb50()));
        if (next != 0) {
            return ActCfgTableFindCallNameByFlags_2207b0(next, arg1, (long long)(arg2));
        }
        return 0;
    }
    return 0;
}
