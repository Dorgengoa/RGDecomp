/* rgp:protos */
#define RGP_SELF_NpcObjTableCharaLoadUpdate_2faac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem {
    u16 flags;
    u8 pad2[0xC8];
    s16 ca;
    u8 padCC[8];
    f32 d4;
} Elem;

typedef struct Obj {
    u8 pad0[0xC];
    Elem *slots[0x80];
    s16 count;
    u8 pad20E[6];
    f32 lim;
    s16 state;
    u8 pad21A[2];
    Elem *cur;
} Obj;

extern s32 D_004827F8 __attribute__((section(".sdata")));
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void NpcObjTableCharaLoadUpdate_2faac0(Obj *s)
{
    Elem **pp;
    s32 i;
    Elem *e;
    s32 r;
    s32 n;

    if (D_004827F8 != s->state) {
        *(s32 *)&D_004827F8 = s->state;
    }
    if (s->state == 0) {
        s->state = 1;
        return;
    }
    if (s->state == 1) {
        pp = s->slots;
        for (i = 0; i < s->count; i++, pp++) {
            e = *pp;
            r = NpcObjFindFreeSlotId_2fb540(s);
            if (r != -1 && (e->flags & 1) && e->d4 <= s->lim && e->ca != 5) {
                NpcObjAssignSlot_2fb8e0(e, r);
                s->state = 2;
                s->cur = e;
                break;
            }
        }
        return;
    }
    if (s->state == 2) {
        if (s->cur->ca == 5) {
            s->state = 0;
        }
        if (s->cur->ca == 1) {
            s->state = 3;
        }
        return;
    }
    if (s->state == 3) {
        n = s->count - 1;
        pp = s->slots;
        pp += n;
        while (n > 0) {
            e = *pp;
            if ((e->flags & 1) && e->ca == 5) {
                if (e->d4 < s->cur->d4) {
                    s->state = 0;
                    return;
                }
                NpcObjSetUnloadState_2fb8d0(e);
                s->cur = e;
                s->state = 4;
                break;
            }
            n--;
            pp--;
        }
        return;
    }
    if (s->state == 4) {
        if (s->cur->ca == 7) {
            s->state = 0;
            NpcObjTableUnloadChara_2face0(s, s->cur);
        }
    }
}
