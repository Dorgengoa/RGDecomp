#include "types.h"

/* p1 is never touched; the guard is argc == 0. */

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void CharaGetHomePos_214350(s32, void *);
extern void CharaSetPos_213a40(s32, void *);

struct Obj0 {
    s32 m00;
};

struct Buf10 {
    u8 b[0x10];
};

s32 CharaCmdPlaceAtHomePos_22d560(struct Obj0 *p0, s32 p1, s32 argc)
{
    struct Buf10 sp20;
    s32 r0;
    s32 o;

    if (argc != 0) {
        return 0;
    }
    r0 = GetActionMgr_1fdb50();
    o = ActionMgrFindById_233b50(r0, p0->m00);
    if (o == 0) {
        return 1;
    }
    CharaGetHomePos_214350(o, &sp20);
    CharaSetPos_213a40(o, &sp20);
    return 1;
}
