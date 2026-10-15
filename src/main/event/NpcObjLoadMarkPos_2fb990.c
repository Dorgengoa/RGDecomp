#include "types.h"

typedef struct { u8 pad[0xA0]; f32 fA0, fA4, fA8; s32 fAC; u8 pad2[0xC6 - 0xB0]; s16 fC6; } T_002fb990;
typedef struct { u8 pad[0x38]; f32 f38, f3C, f40, f44; } B_002fb990;

extern void *GetGameData_1fede0(void);
extern B_002fb990 *GroupGetRecordById_41c2a0(void *, s32, s32, s32);
extern void NpcObjSetYaw_2fb900(T_002fb990 *, f32);

void NpcObjLoadMarkPos_2fb990(T_002fb990 *p)
{
    void *r;
    void *x;
    B_002fb990 *b;

    r = GetGameData_1fede0();
    x = *(void **)((s32)r + 8);
    b = GroupGetRecordById_41c2a0(*(void **)((s32)x + 0x6C), p->fC6, -1, 1);
    if (b == 0) return;
    p->fA0 = b->f38;
    p->fA4 = b->f3C;
    p->fA8 = b->f40;
    p->fAC = 0;
    NpcObjSetYaw_2fb900(p, b->f44);
}
