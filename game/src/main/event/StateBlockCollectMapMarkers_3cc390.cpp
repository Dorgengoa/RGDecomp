#include "types.h"

typedef struct {
    s16 key;
    s16 val;
    f32 x;
    f32 y;
    f32 z;
} Item_3cc390;

typedef struct {
    u8 pad0[0xA];
    s16 count;
    Item_3cc390 *items;
} Set_3cc390;

class VC_3cc390 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Set_3cc390 * f(s32 a0) { return VCM(Set_3cc390 *, (void *, s32), 0x70, a0); }
};

extern "C" {

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Out_3cc390;

typedef struct {
    u8 pad0[0x1C];
    VC_3cc390 *obj;
} Sub4_3cc390;

typedef struct {
    u8 pad0[4];
    Sub4_3cc390 *unk4;
    u8 pad8[0x340];
    s16 unk348;
    s32 unk34C[1];
} S003cc390;

typedef struct {
    u8 pad0[4];
    s16 unk4;
} K_3cc390;

typedef struct {
    u8 pad0[0x18];
    K_3cc390 *unk18;
} ArgObj_3cc390;

extern ArgObj_3cc390 *D_004838C0;

s32 StateBlockCollectMapMarkers_3cc390(S003cc390 *arg0, Out_3cc390 *arg1, s16 *arg2) {
    Item_3cc390 *it;
    s32 j;
    s32 n;
    s32 key;
    Out_3cc390 *o;
    s32 i;
    Set_3cc390 *set;
    s32 cnt;

    if (arg1 == NULL) {
        return 0;
    }
    if (D_004838C0 == NULL) {
        return 0;
    }
    n = 0;
    key = D_004838C0->unk18->unk4;
    for (i = 0; i < arg0->unk348; i++) {
        set = arg0->unk4->obj->f(arg0->unk34C[i]);
        if (set != NULL) {
            cnt = set->count;
            it = set->items;
            for (j = 0; j < cnt; j++, it++) {
                if (it->key == key) {
                    o = &arg1[n];
                    o->x = it->x;
                    o->y = it->y;
                    o->z = it->z;
                    o->w = 1.0f;
                    if (arg2 != NULL) {
                        arg2[n] = it->val;
                    }
                    n++;
                }
            }
        }
    }
    return n;
}

}
