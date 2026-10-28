/* rgp:protos */
#define RGP_SELF_ProgressGetCurSubEntryMaybe_3cd200 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub_FUN_003cd200 {
    u8 pad000[0x8];
    s32 f08;
} Sub_FUN_003cd200;

typedef struct Obj_FUN_003cd200 {
    u8 pad000[0x4];
    Sub_FUN_003cd200 *f04;
} Obj_FUN_003cd200;

/*rgp*/
/*rgp*/

void * ProgressGetCurSubEntryMaybe_3cd200(Obj_FUN_003cd200 *o, s32 b, s32 c, int rgp_a3)
{
    s32 r;

    r = ((short)ProgressValueGet_3cd2c0(o, (long long)(b), (long long)(c), (int)rgp_a3));
    return GroupTableFindSubEntry_422880(o->f04->f08, (s16)b, (s16)c, (s16)r);
}
