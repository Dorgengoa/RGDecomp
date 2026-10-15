#include "types.h"

void MemStackReset_14d830(s32);
void MemStackHeapReinit_14de90(s32);
s32 CharaDataMgrGetMemStack_1ed3f0(s32, s32);
void GetCurrentScene_1f5be0();
s32 GetCharaDataMgr_1fdb70();
void CameraPushMode15_309bb0();
void InsectBattleShutdown_31a230();
s32 InsectBattleGet_31a8d0();
void func_4F3390(s32);
void func_50D8C0(s32, s32, s32, s32);
s32 func_50DA40(s32, s32);
s32 func_50E110(s32, s32);
void func_50E250(s32);
void func_50E5E0(s32);
void func_511CF0(s32, s32, s32);
void func_511EB0(s32, void *);
extern u8 D_00452410[0x400];

void InsectBattleReinit_31a5b0(void) {
    s32 arr[2];
    s32 t;
    s32 r;
    s32 p;
    s32 m;
    s32 i;
    s32 v;
    s32 *q;

    t = InsectBattleGet_31a8d0();
    if (t == 0) {
        InsectBattleShutdown_31a230();
        return;
    }
    GetCurrentScene_1f5be0();
    CameraPushMode15_309bb0();
    r = func_50E110(t, 1);
    if (r == 0) {
        InsectBattleShutdown_31a230();
        return;
    }
    MemStackHeapReinit_14de90(r);
    func_50E5E0(t);
    p = t + 0x4F90;
    if (p != 0) {
        func_511EB0(p, D_00452410);
        func_511CF0(p, 0, 1);
    }
    func_50D8C0(t, 0, 0, -1);
    func_4F3390(t);
    if (func_50DA40(t, 2) != 0) {
        m = GetCharaDataMgr_1fdb70();
        i = 0;
        do {
            arr[i] = CharaDataMgrGetMemStack_1ed3f0(m, i);
            if (arr[i] != 0) {
                MemStackReset_14d830(arr[i]);
            }
            i++;
        } while (i < 2);
    }
    func_50E250(t);

}
