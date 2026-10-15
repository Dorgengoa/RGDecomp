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

extern void Md5Init_36a6b0(struct Obj0 *);
extern void Md5Update_369280(struct Obj0 *, s32, s64);
extern void Md5Final_369110(struct Obj0 *, s32);
extern s64 strlen(s32);

s32 Md5Digest_369090(s32 arg0, s32 arg1, s64 arg2) {
    struct Obj0 sp40;
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
