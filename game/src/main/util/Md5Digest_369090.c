/* rgp:protos */
#define RGP_SELF_Md5Digest_369090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 {
    s64 m00;
    s64 m08;
    s64 m10;
    s64 m18;
    s64 m20;
    s64 m28;
    u8 pad[0x40];
};

/*rgp*/
/*rgp*/
/*rgp*/
extern unsigned int strlen(s32);

s32 Md5Digest_369090(s32 arg0, s32 arg1, s64 arg2) {
    struct Obj0 sp40 __attribute__((aligned(16)));
    s64 var_16;

    var_16 = arg2;
    if (arg2 < 0) {
        var_16 = strlen(arg1);
    }
    Md5Init_36a6b0(&sp40);
    Md5Update_369280(&sp40, arg1, (s32) var_16);
    Md5Final_369110(&sp40, arg0);
    return arg0;
}
