/* rgp:protos */
#define RGP_SELF_ExecInfoCanHitOpposingMaybe_3a6e80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 ExecInfoCanHitOpposingMaybe_3a6e80(void *arg0) {
    s16 tag;
    s32 r;
    void *s;

    tag = *(s16 *)((u8 *)arg0 + 0x1C);
    switch (tag) {
    case 1:
    case 2:
        r = ExecInfoGetActDataMaybe_3a7170(arg0);
        if (r != 0) {
            return ((unsigned char)AtkPrmHitsOpposingMaybe_3f8ca0(r));
        }
        break;
    case 3:
    case 4:
    case 5:
        s = ExecInfoGetEffObjMaybe_3a70b0(arg0, 0);
        if (s != 0) {
            return (*(u8 *)((u8 *)s + 0x1C) & 0x1F) == 1;
        }
        break;
    }
    return 0;
}
