/* rgp:protos */
#define RGP_SELF_NpcViewCtor_41c210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00472250[0x10];
extern u8 D_0047B1B0[0x10];
extern u8 D_0047B330[0x10];

typedef struct Obj {
    void *vt;
    s32 unk4;
    s16 unk8;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 pad : 6;
    u8 padB;
    s16 unkC;
    s16 unkE;
    s16 unk10;
} Obj;

Obj *NpcViewCtor_41c210(Obj *self, void *arg1, s16 arg2, s32 arg3, s32 arg4)
{
    self->vt = D_00472250;
    self->vt = D_0047B330;
    self->vt = D_0047B1B0;
    if (arg1 != NULL) {
        self->unk4 = *(s32 *)((u8 *)(*(void **)((u8 *)arg1 + 8)) + 0x6C);
    } else {
        self->unk4 = 0;
    }
    self->unk8 = arg2;
    self->b0 = arg3;
    self->b1 = arg4;
    self->unkC = -1;
    self->unkE = -1;
    self->unk10 = -1;
    return self;
}
