#include "types.h"

/* Stack locals are allocated in REVERSE declaration order, so `a` is the
   0x50 slot, `b` the 0x40 slot and `c` the 0x30 slot. */

extern s32 GetActionMgr_1fdb50(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern struct Ctx *GetGameData_1fede0(void);
extern void CharaGetPos_2388a0(s32, f32 *);
extern void VecSub_1cbd00(f32 *, f32 *, f32 *);
extern f32 Atan2f_1291a8(f32, f32);
extern void CharaSetYaw_2138f0(s32, f32);

struct Obj0 {
    s32 m00;
};

struct Sub {
    u8 pad[0x18E];
    s16 m18E;
};

struct Ctx {
    u8 pad[0x18];
    struct Sub *m18;
};

s32 CharaCmdLookAtPlayer_22d350(struct Obj0 *p0, s32 p1, s32 argc)
{
    f32 a[4];
    f32 b[4];
    f32 c[4];
    s32 r0;
    s32 o1;
    s32 o2;

    if (argc != 0) {
        return 0;
    }
    r0 = GetActionMgr_1fdb50();
    o1 = ActionMgrFindById_233b50(r0, p0->m00);
    if (o1 == 0) {
        return 1;
    }
    o2 = ActionMgrFindById_233b50(r0, GetGameData_1fede0()->m18->m18E);
    if (o2 == 0) {
        return 1;
    }
    if (o1 == o2) {
        return 1;
    }
    CharaGetPos_2388a0(o1, a);
    CharaGetPos_2388a0(o2, b);
    VecSub_1cbd00(c, b, a);
    CharaSetYaw_2138f0(o1, Atan2f_1291a8(c[0], c[2]));
    return 1;
}
