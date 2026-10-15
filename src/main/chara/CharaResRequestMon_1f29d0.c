#include "types.h"

typedef struct S001f29d0 {
    u8 pad0[0xD00];
    s32 unkD00;
} S001f29d0;

typedef struct Item001f29d0 {
    u8 pad0[0x60];
    s16 unk60;
    s16 unk62;
    s16 unk64;
} Item001f29d0;

extern s32 ObjRecGetLiveObject_1c4a90(s32 arg0, s32 arg1);
extern Item001f29d0 *CharaDataFindById_1ed990(s32 arg0, s32 arg1);
extern Item001f29d0 *CharaResFindById_1f0530(void *arg0, s32 arg1);
extern void CharaResReleaseById_1f1160(void *arg0, s32 arg1, s32 arg2);
extern s32 CharaMonsterResRequest_1f11c0(void *arg0, s32 arg1);
extern s32 CharaMonCopyResRequest_1f2430(void);
extern s32 CharaResRequest_1f2d90(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void CharaResBuildMon_1f3860(void *arg0, s32 arg1, s32 arg2);
extern s32 MonDefGetCharaDataId_1f4fa0(s32 arg0);
extern s32 GetCharaDataMgr_1fdb70(void);

s32 CharaResRequestMon_1f29d0(S001f29d0 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 h;
    s32 id;
    s32 r;
    Item001f29d0 *it;
    Item001f29d0 *q;
    Item001f29d0 *a;

    if (arg3 == 0x2F11) {
        return CharaMonCopyResRequest_1f2430();
    }
    h = GetCharaDataMgr_1fdb70();
    id = MonDefGetCharaDataId_1f4fa0(arg3);
    if (id == -1) {
        return 0;
    }
    if (arg4 == 1 && CharaDataFindById_1ed990(h, id) == NULL && CharaMonsterResRequest_1f11c0(arg0, arg3) == 0) {
        return 0;
    }
    r = CharaResRequest_1f2d90(arg0, arg1, arg2, arg3, id, 1, 2);
    if (r != 0) {
        it = CharaDataFindById_1ed990(h, id);
        q = CharaResFindById_1f0530(arg0, arg2);
        if (q != NULL && it != NULL && it->unk60 == 3) {
            CharaResBuildMon_1f3860(q, arg1, arg0->unkD00);
            if (ObjRecGetLiveObject_1c4a90(arg1, arg2) == 0 || q->unk64 == 4) {
                CharaResReleaseById_1f1160(arg0, arg1, arg2);
                return 0;
            }
        }
    }
    a = CharaDataFindById_1ed990(h, id);
    q = CharaResFindById_1f0530(arg0, arg2);
    if (a == NULL || q == NULL) {
        CharaResReleaseById_1f1160(arg0, arg1, arg2);
        return 0;
    }
    return r;
}
