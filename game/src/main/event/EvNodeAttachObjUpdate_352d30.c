/* rgp:protos */
#define RGP_SELF_EvNodeAttachObjUpdate_352d30 1
#define RGP_SELF_alive 1
#include "port/game_protos.h"
#line 1
/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/EvNodeAttachObjUpdate_352d30.s and build/b_drafts/EvNodeAttachObjUpdate_352d30.txt
   (m2c draft already generated, just not worked). */
/* s49m: MATCH */
#include "types.h"

typedef struct { u32 w[9]; } Blk;
typedef struct { f32 x, y, z; } V3;

typedef struct Req {
    s32 id;
    s32 w[8];
} Req;

typedef struct Obj {
    u8 pad0[0x10];
    V3 m[3];
    Blk b;
    V3 pm[3];
    Blk pb;
    u8 padA0[0xD0 - 0xA0];
    u32 flags;
    u8 padD4[0x124 - 0xD4];
    u8 *unk124;
    s32 unk128;
    u8 pad12C[0xC];
    char name[0x10];
    s16 unk148;
    s16 unk14A;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char *strcpy(char *, const char *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char D_004629A0[];

static inline s32 alive(Obj *o)
{
    return !((o->flags & 0x80000000) != 0);
}

void EvNodeAttachObjUpdate_352d30(Obj *o)
{
    u8 sp60[0x40] __attribute__((aligned(16)));
    Req r __attribute__((aligned(16)));
    s32 x;

    EvObjUpdateBase_2f9910(o);
    if (!alive(o)) {
        return;
    }
    if (!(o->flags & 0x2000000)) {
        return;
    }
    o->pm[0] = o->m[0];
    o->pm[1] = o->m[1];
    o->pm[2] = o->m[2];
    o->pb = o->b;
    TargetRefApplyToEventObj_2e6810((u8 *)&o->padA0, (u8 *)o->m);
    o->flags &= ~0x40000000;
    switch (((short)EvNodeAttachObjGetPlayState_3532f0(o))) {
    case 0:
        EvNodeAttachObjPlayStart_353290(o);
        break;
    case 1:
        x = *(s32 *)(o->unk124 + 0x6C);
        ModelObjPlayMotionByName_1867a0(x, EvNodeAttachObjGetMotionName_353300(o), 4);
        o->unk148 = 2;
        o->unk14A = 0;
        strcpy(o->name, D_004629A0);
        break;
    case 2:
        break;
    case 3:
        x = *(s32 *)(o->unk124 + 0x6C);
        ModelObjPlayMotionByName_1867a0(x, EvNodeAttachObjGetMotionName_353300(o), 1);
        o->unk148 = 0;
        break;
    }
    if (((short)EvNodeAttachObjGetPlayState_3532f0(o)) == 2) {
        FrameCalcWorldMatrix_148ff0(o->unk128, sp60);
        EventObjSetFromMatrix_2e72f0((u8 *)o->m, sp60);
        TargetRefDetachFromParent_2e5890((u8 *)&o->padA0);
        TargetRefSetFromEventObj_2e59c0((u8 *)&o->padA0, (u8 *)o->m);
    }
    r.id = -1;
    r.w[0] = 0;
    r.w[1] = 0;
    r.w[2] = 0;
    r.w[3] = 0;
    r.w[4] = 0;
    r.w[5] = 0;
    r.w[6] = 0;
    r.w[7] = 0;
    r.id = EventRecGetId_2e5710(o);
    EvScriptDispatchByNameAndId_2f9ab0(o, &r, o->name, o->unk14A);
    o->unk14A++;
    if (o->unk14A > 10000) {
        o->unk14A--;
    }
}
