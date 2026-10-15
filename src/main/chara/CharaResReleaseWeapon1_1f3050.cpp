#include "types.h"

typedef struct Self {
    s16 m00;
    s16 pad02;
    s16 m04;
    u8  m06;
} Self;

extern "C" void *GetCharaDataMgr_1fdb70(void);
extern "C" void *CharaDataFindSubRecById_1ed710(void *a, s16 b, s32 c);
extern "C" void *CharaDataSubRecRelease_1ee6d0(void *a);
extern "C" void  GameSceneObjReleaseMaybe_1cfc50(void *b, s32 k);

extern "C" void CharaResReleaseWeapon1_1f3050(Self *self, void *b)
{
    s16 v;
    bool ok;
    s32 k;

    CharaDataSubRecRelease_1ee6d0(CharaDataFindSubRecById_1ed710(GetCharaDataMgr_1fdb70(), self->m04, 2));

    v = self->m00;
    ok = false;
    if (v >= 0 && v < 0xC) {
        ok = true;
    }
    if (ok) {
        k = v * 4 + 0xC;
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
        k = v * 4 + 0xD;
    } else {
        k = -1;
    }
    GameSceneObjReleaseMaybe_1cfc50(b, k);

    self->m06 &= ~0x2;
}
