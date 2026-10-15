#include "types.h"

struct Obj {
    u8 pad000[0x1A4];
    s32 mF;
};

struct Root {
    u8 pad00[0x10];
    void *m10;
};

extern struct Root *GetGameData_1fede0(void);
extern s32 StateFlagTestByName_3ccd10(void *a, s32 b);

s32 EvDoorObjTestStateFlag_303d30(struct Obj *o)
{
    struct Root *r;

    if (o->mF == 0) {
        return 1;
    }
    r = GetGameData_1fede0();
    return StateFlagTestByName_3ccd10(r->m10, *(volatile s32 *)&o->mF);
}
