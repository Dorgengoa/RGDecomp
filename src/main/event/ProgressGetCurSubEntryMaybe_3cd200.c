#include "types.h"

typedef struct Sub_FUN_003cd200 {
    u8 pad000[0x8];
    s32 f08;
} Sub_FUN_003cd200;

typedef struct Obj_FUN_003cd200 {
    u8 pad000[0x4];
    Sub_FUN_003cd200 *f04;
} Obj_FUN_003cd200;

extern s32 ProgressValueGet_3cd2c0(Obj_FUN_003cd200 *o, s32 b, s32 c);
extern void GroupTableFindSubEntry_422880(s32 h, s16 b, s16 c, s16 r);

void ProgressGetCurSubEntryMaybe_3cd200(Obj_FUN_003cd200 *o, s32 b, s32 c)
{
    s32 r;

    r = ProgressValueGet_3cd2c0(o, b, c);
    GroupTableFindSubEntry_422880(o->f04->f08, (s16)b, (s16)c, (s16)r);
}
