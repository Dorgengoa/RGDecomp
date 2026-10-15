#include "types.h"

/* 0x4F2A90 / 0x4F2D40 are OVERLAY addresses; main.s has no relocations so the
   disassembler prints them raw.  `lui/addiu` is the %hi/%lo shape, so they are
   symbol references, not integer literals. */

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 CharaGetExecInfo_2149f0(s32);
extern void func_4F2D40(void);
extern void func_4F2A90(void);
extern void ItemUseMaybe_2eef60(s32, s32, void (*)(void), s32, s32);
extern void CharaExecInfoInit_219100(s32);

struct Obj0 {
    s32 m00;
};

s32 CharaCmdItem_22bba0(struct Obj0 *p0)
{
    s32 r0;
    s32 o;
    s32 h;

    r0 = GetActionMgr_1fdb50();
    o = ActionMgrFindById_233b50(r0, p0->m00);
    if (o == 0) {
        return 1;
    }
    h = CharaGetExecInfo_2149f0(o);
    func_4F2D40();
    ItemUseMaybe_2eef60(*(s32 *)(h + 0x6C), h, func_4F2A90, 1, 0);
    CharaExecInfoInit_219100(h);
    return 1;
}
