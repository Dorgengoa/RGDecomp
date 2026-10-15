#include "types.h"

/* Known-positive sibling shape of GroupFindByNameInRange_411390 (byte-identical, in cunits). */

extern s32 GroupFindByKey_4116b0(s32, s32);
extern s32 TableGetByIdChecked_412e20(s32, s32, s32);

s32 GroupGetRecordChecked_411340(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;
    s32 r1;

    r0 = GroupFindByKey_4116b0(p0, p1);
    if (r0 != 0) {
        r1 = TableGetByIdChecked_412e20(r0, p2, p3);
        return r1;
    }
    return 0;
}
