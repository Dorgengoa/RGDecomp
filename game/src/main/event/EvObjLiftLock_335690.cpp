/* rgp:protos */
#line 1
#include "types.h"

struct Obj0 { u8 pad000[0xA0]; s32 mA0; u8 pad0A4[0x2C]; s32 mD0; };
struct Obj1 { u8 pad000[0x2C]; s32 m2C; };

extern "C" s32 EvObjLiftGetPlayState_336120(struct Obj0 *);
extern "C" s32 TargetRefSetAreaFlag2_2e6790(s32 *);
extern "C" s32 GetMapMgr_201a90(void);
extern "C" s32 TargetRefGetId_2e7120(s32 *);
extern "C" struct Obj1 *MapSlotsFindById_1e4b90(s32, s32, s32);

extern "C" void EvObjLiftLock_335690(struct Obj0 *p0)
{
    s32 t0;
    bool ok;
    struct Obj1 *r4;

    t0 = p0->mD0;
    ok = !(t0 & 0x80000000);
    if (ok) {
        if ((t0 & 0x2000000) == 0) {
            return;
        }
        if (((short)EvObjLiftGetPlayState_336120(p0)) != 0) {
            TargetRefSetAreaFlag2_2e6790(&p0->mA0);
            r4 = MapSlotsFindById_1e4b90(GetMapMgr_201a90(), ((short)TargetRefGetId_2e7120(&p0->mA0)), 0);
            if (r4 != 0) {
                r4->m2C = r4->m2C | 0x10;
            }
        }
    }
}
