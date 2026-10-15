#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 CharaGetPos_2388a0(s32, void *);
extern s32 MapBlockIdListRebuildAtPos_1ff570(void *);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x18E];
    s16 m18E;
};

s32 EvCmdMapBlockIdListRebuildAtLeader_25a740(void)
{
    u128 v20;
    struct Obj0 *r0;
    s32 r1;
    struct Obj1 * t0;
    s16 t1;
    s32 r2;
    s32 r3;
    s32 r4;

    r0 = GetGameData_1fede0();
    r1 = GetActionMgr_1fdb50();
    t0 = r0->m18;
    t1 = r0->m18->m18E;
    r2 = ActionMgrFindById_233b50(r1, t1);
    if (r2 != 0) {
        r3 = CharaGetPos_2388a0(r2, &v20);
        r4 = MapBlockIdListRebuildAtPos_1ff570(&v20);
        return 1;
    }
    return 0;
}
