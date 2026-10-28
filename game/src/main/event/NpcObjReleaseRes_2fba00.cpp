/* rgp:protos */
#line 1
#include "types.h"
extern "C" {
extern s32 GetStaticScene_1c6c70(void);
extern void CharaResReleaseById_1f1160(s32, s32, s16);
extern s32 GetCharaResMgr_1fdb60(void);
extern void NpcObjReleaseCharaData_2fb820(void *);
}
typedef struct {
    u16 unk0;
    u8 pad2[0xc2];
    s16 unkC4;
} T2fba00_arg0;

extern "C" void NpcObjReleaseRes_2fba00(T2fba00_arg0 *arg0, bool arg1) {
    s32 t17;
    s32 t4;
    s16 t6;
    bool flag;

    t17 = GetStaticScene_1c6c70();
    t4 = GetCharaResMgr_1fdb60();
    t6 = arg0->unkC4;
    flag = arg1;
    if (t6 != -1) {
        CharaResReleaseById_1f1160(t4, t17, t6);
        flag = true;
        arg0->unkC4 = -1;
    }
    if (flag) {
        arg0->unk0 = arg0->unk0 & 0xFFFE;
    }
    if (arg0->unk0 & 4) {
        NpcObjReleaseCharaData_2fb820(arg0);
    }
}
