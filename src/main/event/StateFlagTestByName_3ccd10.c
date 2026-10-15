#include "types.h"

typedef struct SubObjCcd10 {
    u8 pad0[0xC];
    void *unkC;
} SubObjCcd10;

typedef struct ObjCcd10 {
    u8 pad0[0x4];
    SubObjCcd10 *unk4;
} ObjCcd10;

void *TableFindByName_4223f0(void *arg0);
s32 StateFlagTest_3ccd70(ObjCcd10 *arg0, s16 arg1);

s32 StateFlagTestByName_3ccd10(ObjCcd10 *arg0)
{
    SubObjCcd10 *p;
    void *q;

    p = arg0->unk4;
    if (p == 0) {
        return 0;
    }
    q = TableFindByName_4223f0(p->unkC);
    if (q != 0) {
        return StateFlagTest_3ccd70(arg0, *(s16 *)q);
    }
    return 0;
}
