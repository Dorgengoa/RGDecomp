/* rgp:protos */
#line 1
#include "types.h"

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v5C() { return VCM0(s32, 0x5C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vC0() { return VCM0(s32, 0xC0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v4F0() { VCM0(void, 0x4F0); }
    void v4F4() { VCM0(void, 0x4F4); }
    u8 pad4[0x230];
    u8 f234a : 1;
    u8 f234b : 1;
    u8 f234c : 1;
    u8 pad235[0x4B4 - 0x235];
    u8 f4B4 : 1;
};

typedef struct {
    u8 pad0[0x18C];
    s16 n18C;
    s16 cur;
    s16 arr[(0x42D0 - 0x190) / 2];
    u8 fl : 1;
} ObjA;

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
} Mgr;

extern "C" {
extern Unit *CharaMgrPoolFindById_3a8c60(s32, s32);
extern s32 CharaCanBeLeader_3ae200(Unit *, s32, int, int);
extern Mgr *D_00483890;
}

static inline s32 find(ObjA *obj, s32 id)
{
    s32 i;
    if (id < 0) {
        return -1;
    }
    for (i = 0; i < obj->n18C; i++) {
        if (obj->arr[i] == id) {
            return i;
        }
    }
    return -1;
}

extern "C" s32 PartySetLeader_3c1600(ObjA *obj, s32 id, s32 flag)
{
    Unit *u;
    Unit *prev;
    s32 i;

    if (id < 0) {
        return 0;
    }
    if (D_00483890 == 0) {
        return 0;
    }
    u = CharaMgrPoolFindById_3a8c60(D_00483890->unk14, id);
    if (u == 0) {
        return 0;
    }
    if (u->f234c) {
        return 0;
    }
    if (u->f4B4) {
        return 0;
    }
    if (obj->fl && u->v5C() != 0x2AF9) {
        return 0;
    }
    if (id == obj->cur) {
        return 1;
    }
    if (u->vC0() != 0) {
        return 0;
    }
    if (find(obj, id) >= 0) {
        if (CharaCanBeLeader_3ae200(u, 0, 0, 0) != 0) {
            if (flag == 0) {
                prev = CharaMgrPoolFindById_3a8c60(D_00483890->unk14, obj->cur);
                obj->cur = id;
                u->v4F0();
                if (prev != 0) {
                    prev->v4F4();
                }
            }
            return 1;
        }
    }
    return 0;
}
