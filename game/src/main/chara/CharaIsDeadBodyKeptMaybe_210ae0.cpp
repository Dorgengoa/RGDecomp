#include "types.h"
struct Obj0 {
    u8 pad000[0x3D0];
    s64 m3D0;
    u8 pad3D8[0x65A];
    s16 mA32;
    s16 mA34;
};

extern "C" bool CharaIsDeadBodyKeptMaybe_210ae0(struct Obj0 *p0)
{
    bool b;

    b = !(p0->m3D0 & (((s64)0x2000000) << 32));
    if (b) {
        return false;
    }
    if (p0->mA32 != 0x11) {
        return false;
    }
    return p0->mA34 == 0xA;
}
