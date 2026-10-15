#include "types.h"

typedef struct Obj003a6f30 {
    u8 pad00[0x1C];
    s16 unk1C;
} Obj003a6f30;

typedef struct Sub003a6f30 {
    u8 pad00[0x1C];
    u8 unk1C;
} Sub003a6f30;

extern s32 ExecInfoGetActDataMaybe_3a7170(Obj003a6f30 *p0);
extern Sub003a6f30 *ExecInfoGetEffObjMaybe_3a70b0(Obj003a6f30 *p0, s32 flag);
extern u8 AtkPrmHitsOtherGroupMaybe_3f8cc0(void *o);

u8 ExecInfoCanHitOtherGroupMaybe_3a6f30(Obj003a6f30 *arg0)
{
    s32 r;
    Sub003a6f30 *s;
    s32 m;

    switch (arg0->unk1C) {
    case 1:
    case 2:
        r = ExecInfoGetActDataMaybe_3a7170(arg0);
        if (r != 0) {
            return AtkPrmHitsOtherGroupMaybe_3f8cc0((void *)r);
        }
        break;
    case 3:
    case 4:
        s = ExecInfoGetEffObjMaybe_3a70b0(arg0, 0);
        if (s != 0) {
            m = s->unk1C & 0x1F;
            if (m == 3) {
                goto one;
            }
            if (m == 4) {
one:
                return 1;
            }
            return 0;
        }
        break;
    case 5:
        break;

    }
    return 0;
}
