#include "types.h"

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
} Ent;

typedef struct {
    u8 pad0[0x4A4];
    Ent ents[2];
    u8 pad4DC[4];
    s32 f4E0;
    u8 pad4E4[8];
    s16 f4EC;
} Obj;

s32 sceMcSync_12d098(s32, s32 *, s32 *);
s32 sceMcGetInfo_12d1b8(s16, s32, s32 *, s32 *, s32 *);
void SaveMgrClearResult_3759d0(Obj *);
extern s32 D_00483198;

s32 McGetInfoStep_375640(Obj *obj) {
    Ent *e;
    s32 cnt;
    s32 d;
    s32 a;
    s32 b;
    s32 r;

    e = &obj->ents[obj->f4EC];
    if (e == 0) {
        return 0;
    }
    if (obj->f4E0 == 0) {
        D_00483198 = e->f8;
    }
    switch (obj->f4E0 % 2) {
    case 0:
        if (sceMcSync_12d098(1, 0, 0) != 0) {
            SaveMgrClearResult_3759d0(obj);
            e->f18 = 0;
            r = sceMcGetInfo_12d1b8(obj->f4EC, 1, &e->f4, &e->f10, &e->f8);
            if (r == 0) {
                obj->f4E0 += 1;
            } else if (r != -200) {
                obj->f4E0 += 2;
            }
        }
        break;
    case 1:
        if (sceMcSync_12d098(1, &a, &b) != 0) {
            e->f0 = 1;
            e->f14 = b;
            e->f18 = 1;
            switch (b) {
                        case 0:
                e->f18 = 0;
                break;
            case -1:
                e->f8 = 1;
                break;
            case -2:
                e->f8 = 0;
                break;
            default:
                if (b < -10) {
                    e->f0 = 0;
                }
                break;
            }
            cnt = ++obj->f4E0;
            if (cnt >= 2 && e->f0 != 0 && e->f8 != 0) {
                d = D_00483198;
                if (d != 0 && e->f8 != 0) {
                    e->fC = 0;
                }
                if (d == 0 && e->f8 != 0) {
                    e->fC = 1;
                }
                return 1;
            }
            if (cnt >= 10) {
                d = D_00483198;
                if (d != 0 && e->f8 != 0) {
                    e->fC = 0;
                }
                if (d == 0 && e->f8 == 0) {
                    e->fC = 0;
                }
                if (d == 0 && e->f8 != 0) {
                    e->fC = 1;
                }
                if (d != 0 && e->f8 == 0) {
                    e->fC = -1;
                }
                return 1;
            }
        }
        break;
    }
    return 0;
}
