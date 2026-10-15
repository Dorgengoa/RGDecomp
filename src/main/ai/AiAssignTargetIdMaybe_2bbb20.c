#include "types.h"

typedef struct { u8 pad[0x18E]; s16 x18E; } G2;
typedef struct { u8 pad[0x18]; G2 *x18; } G1;
typedef struct { u8 pad[0xA8]; s16 xA8; } A0;
typedef struct { u8 pad[0x148]; s16 x148; u8 pad2[0x16E - 0x14A]; s16 x16E; } P;

extern s32 GetActionMgr_1fdb50(void);
extern G1 *GetGameData_1fede0(void);
extern P *CharaGetAi_214a10(s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void AiSetTargetCharaId_2c0f10(P *, s32);

void AiAssignTargetIdMaybe_2bbb20(A0 *arg0, s32 arg1) {
    s32 t16;
    s32 d;
    s32 h;
    P *p;

    t16 = GetGameData_1fede0()->x18->x18E;
    t16 = (s32)(u32)t16;
    d = GetActionMgr_1fdb50();
    h = ActionMgrFindById_233b50(d, arg1);
    if (h != 0) {
        p = CharaGetAi_214a10(h);
        p->x16E = arg0->xA8;
    }
    if (t16 == arg1) {
        h = ActionMgrFindById_233b50(d, t16);
        if (h != 0) {
            p = CharaGetAi_214a10(h);
            p->x148 = arg0->xA8;
            AiSetTargetCharaId_2c0f10(p, arg0->xA8);
        }
    }
}
