/* rgp:protos */
#line 1
#include "types.h"

typedef struct Self {
    s16 m00;
    s16 pad02;
    s16 m04;
    u8  m06;
} Self;

extern "C" void *GetCharaDataMgr_1fdb70(void);
extern "C" void *CharaDataFindSubRecById_1ed710(void *a, s16 b, s32 c);
extern "C" void CharaDataSubRecRelease_1ee6d0(void *);
extern "C" void  GameSceneObjReleaseMaybe_1cfc50(void *b, s32 k);

extern "C" void CharaResReleaseWeapon2_1f2f90(Self *self, void *b)
{
    s16 v;
    bool ok;
    s32 k;

    CharaDataSubRecRelease_1ee6d0(CharaDataFindSubRecById_1ed710(GetCharaDataMgr_1fdb70(), self->m04, 3));

    v = self->m00;
    ok = false;
    if (v >= 0 && v < 0xC) {
        ok = true;
    }
    if (ok) {
        k = v * 4 + 0xE;
    } else {
        k = -1;
    }
    GameSceneObjReleaseMaybe_1cfc50(b, k);

    v = self->m00;
    ok = false;
    if (v >= 0 && v < 0xC) {
        ok = true;
    }
    if (ok) {
        k = v * 4 + 0xF;
    } else {
        k = -1;
    }
    GameSceneObjReleaseMaybe_1cfc50(b, k);

    self->m06 &= ~4;
}
