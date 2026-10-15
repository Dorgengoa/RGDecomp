#include "types.h"

typedef struct S {
    u8 a[9];
    u8 b[6];
    s8 xF;
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 f3 : 1;
    u8 pad11;
    s16 x12;
    s16 x14;
    u8 pad16[2];
    u8 arr[5][0x28];
} S;

extern void InsectTeamMemberInit_4325b0(void *);
extern void *memset(void *, s32, u32);

void InsectTeamInit_4324d0(S *arg0)
{
    u8 *p;
    s32 i;

    memset(arg0->a, 0, 9);
    memset(arg0->b, 0, 6);
    arg0->xF = 0;
    arg0->f0 = 0;
    arg0->f1 = 0;
    arg0->f2 = 0;
    arg0->f3 = 0;
    arg0->x12 = 0;
    arg0->x14 = 0;
    p = arg0->arr[0];
    for (i = 0; i < 5; i++) {
        InsectTeamMemberInit_4325b0(p);
        p += 0x28;
    }
}
