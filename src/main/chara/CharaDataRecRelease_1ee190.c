#include "types.h"

typedef struct Obj_FUN_001ee190 {
    u8 pad000[0x62];
    s16 f62;
} Obj_FUN_001ee190;

typedef struct Sub_FUN_001ee190 Sub_FUN_001ee190;

extern void CharaDataRecReleaseSubRecs_1ee0d0(Obj_FUN_001ee190 *o);
extern void CharaDataRecReset_1ee5e0(Obj_FUN_001ee190 *o);
extern Sub_FUN_001ee190 *GetEffectMgr_2d9040(void);
extern void EffectReleaseByGroup_2e12f0(Sub_FUN_001ee190 *s, s32 n);

void CharaDataRecRelease_1ee190(Obj_FUN_001ee190 *o)
{
    s32 t;

    t = o->f62;
    CharaDataRecReleaseSubRecs_1ee0d0(o);
    CharaDataRecReset_1ee5e0(o);
    EffectReleaseByGroup_2e12f0(GetEffectMgr_2d9040(), t);
}
