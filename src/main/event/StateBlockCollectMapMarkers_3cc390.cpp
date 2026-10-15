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
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual Set_3cc390 *f(s32);
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
