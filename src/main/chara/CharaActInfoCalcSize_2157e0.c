#include "types.h"
#pragma no_branch_likely on
extern u32 AlignUp16_1cacd0(s32);
extern void SwordTrailReset_2d7630(void *);
extern s32 SwordTrailCalcSize_2d76a0(void *, s32);
extern void TargetRefClear_2e71d0(void *);
extern void TargetRefCtor_2e71f0(void *);

typedef struct {
    u8 b[0x30];
} Sub30;

typedef struct {
    u8 head[0x30];
    Sub30 arr[2];
    s32 c0;
    s8 c4;
    u8 pad[0x1F];
    s32 e4;
} Obj;

typedef struct {
    u8 pad[0x7A];
    s16 x7A;
} Arg;

s32 CharaActInfoCalcSize_2157e0(s32 pad0, Arg *arg1)
{
    Obj o;
    Sub30 *p;
    s32 r;

    if (arg1 == NULL) {
        return 0;
    }
    SwordTrailReset_2d7630(&o);
    p = o.arr;
    do {
        TargetRefCtor_2e71f0(p);
        p++;
    } while (p < (Sub30 *)&o.c0);
    SwordTrailReset_2d7630(&o);
    TargetRefClear_2e71d0(&o.arr[0]);
    TargetRefClear_2e71d0(&o.arr[1]);
    o.c4 = 0;
    o.c0 = -1;
    o.e4 = 0;
    r = 2;
    r += AlignUp16_1cacd0(arg1->x7A * sizeof(Obj)) >> 4;
    {
        s32 t = SwordTrailCalcSize_2d76a0(&o, 0x14);
        return r + t * arg1->x7A;
    }
}
