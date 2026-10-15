#include "types.h"
#include "vec.h"

typedef struct { u8 b[0x60]; } E;

void FrameSetRot_14a390(s32, u128 *);
void FrameSetPos_14a450(s32, u128 *);
s32 CollFrameTreeCollectTrisFwd_16c180(s32, E *, s32, s32);
void CollTriSetAttr_1ce5a0(E *, s32);
s32 MapEntryGetFloorAttr_1e1220(u8 *);
u8 *MapEntryAsObjRelated_1e1230(u8 *);
s32 GetGateCollObj_1fdab0(void);

s32 MapBlockCollectEntryCollTrisMaybe_1dfa20(u8 *o, E *arr, s32 total, s32 x) {
    u128 a;
    u128 b;
    s32 h;
    u8 *p;
    u8 *q;
    s32 sum;
    s32 i;
    s32 j;
    s32 n;
    E *e;

    if (*(s32 *)(o + 0xC0) == 0 || *(s16 *)(o + 0xC8) <= 0) {
        return 0;
    }
    h = GetGateCollObj_1fdab0();
    if (h == 0) {
        return 0;
    }
    p = *(u8 **)(o + 0xC0);
    sum = 0;
    for (i = 0; i < *(s16 *)(o + 0xC8); i++, p += 0x7A0) {
        q = MapEntryAsObjRelated_1e1230(p);
        a = *(u128 *)(q + 0x180);
        b = *(u128 *)(q + 0x190);
        FrameSetPos_14a450(h, &a);
        FrameSetRot_14a390(h, &b);
        e = &arr[sum];
        n = CollFrameTreeCollectTrisFwd_16c180(h, e, x, total - sum);
        for (j = 0; j < n; j++, e++) {
            CollTriSetAttr_1ce5a0(e, MapEntryGetFloorAttr_1e1220(p));
        }
        sum += n;
    }
    return sum;
}
