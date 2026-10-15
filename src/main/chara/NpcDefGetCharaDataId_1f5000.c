#include "types.h"

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x6C];
    s32 m6C;
};

struct Obj1 {
    u8 pad000[0xC];
    struct Obj2 *m0C;
};

struct Obj2 {
    s16 m00;
};

extern struct Obj0 * GetWorldDataMgr_1fedf0(void);
extern struct Obj1 * GroupGetRecordById_41c2a0(s32, s32, s32, s32);

s32 NpcDefGetCharaDataId_1f5000(s32 p0)
{
    struct Obj0 *r0;
    struct Obj1 *r1;
    struct Obj2 *t1;

    r0 = GetWorldDataMgr_1fedf0();
    r1 = GroupGetRecordById_41c2a0(r0->m6C, (s16)p0, -1, 1);
    if (r1 == 0) {
        return -1;
    }
    t1 = r1->m0C;
    if (t1 == 0) {
        return -1;
    }
    return t1->m00;
}
