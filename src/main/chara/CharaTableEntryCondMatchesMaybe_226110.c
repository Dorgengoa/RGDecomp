#include "types.h"

typedef struct {
    s8 *name;
    u8 pad4[0x30];
    s32 flags;
    u8 pad38[2];
    s16 type;
    u32 lo;
    u32 hi;
} Obj;

s32 StrEqualNonNull_1ca6c0(s8 *);

s32 CharaTableEntryCondMatchesMaybe_226110(Obj *o, s32 a1, u64 m, f32 f) {
    u64 k;

    if (*o->name != 0x23 && StrEqualNonNull_1ca6c0(o->name) == 0) {
        return 0;
    }
    switch (o->type) {
    case 2:
        k = ((u64)o->hi << 32) | o->lo;
        return k == (k & m);
    case 3:
        k = ((u64)o->hi << 32) | o->lo;
        return k != (k & m);
    case 0:
        if (o->flags & 2) {
            return f >= 1.0f;
        }
        return 1;
    case 5:
        return (m & (2LL << 32)) != 0;
    case 1:
    case 4:
    default:
        return 1;
    }
}
