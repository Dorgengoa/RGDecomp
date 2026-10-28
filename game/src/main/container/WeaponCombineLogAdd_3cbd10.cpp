#include "types.h"
#pragma optimization_level 3

struct Elem3cbd10 {
    s16 key;
    __extension__ unsigned short b0 : 1;
    unsigned short b1 : 1;
    unsigned short cnt : 10;
    unsigned short rest : 4;
} __attribute__((aligned(2)));
struct Key3cbd10 {
    u8 pad0[3];
    u8 lo : 4;
    u8 flag : 1;
    u8 hi : 3;
    s16 key;
};
struct Obj3cbd10 {
    u8 pad0[0x16A0];
    s16 count;
    Elem3cbd10 arr[1];
};

extern "C" Elem3cbd10 *WeaponCombineLogFind_3cbf10(Obj3cbd10 *, s16, bool);
extern "C" void memmove(void *, void *, s32);
extern "C" s32 D_00465D40[];

extern "C" Elem3cbd10 *WeaponCombineLogAdd_3cbd10(Obj3cbd10 *o, Key3cbd10 *k, bool a2, u8 a3, bool *out)
{
    s32 key;
    bool flag;
    Elem3cbd10 *e;
    s32 pos;
    Elem3cbd10 *p;
    Elem3cbd10 *slot;
    s32 i;
    s32 n;
    bool hit;
    u16 c;
    u32 b0;

    if (k == 0) {
        return 0;
    }
    *out = false;
    key = k->key;
    flag = k->flag;
    e = WeaponCombineLogFind_3cbf10(o, key, flag);
    if (e != 0) {
        *out = true;
        if (a2) {
            e->b1 = true;
        }
        if (a3) {
            c = e->cnt;
            if (c < D_00465D40[0]) {
                e->cnt = c + 1;
            }
        }
    } else {
        n = o->count;
        p = o->arr;
        i = 0;
        pos = n;
        slot = &o->arr[n];
        for (; i < n; i++, p++) {
            hit = false;
            {
                s32 pk = p->key;
                b0 = p->b0;
                if (key < pk) {
                    hit = true;
                } else if (pk == key && b0 && !flag) {
                    hit = true;
                }
            }
            if (hit) {
                slot = p;
                pos = i;
                break;
            }
        }
        if (pos < n) {
            memmove(slot + 1, slot, (n - pos) * 4);
        }
        slot->key = key;
        slot->b0 = flag;
        slot->b1 = a2;
        slot->cnt = a3;
        o->count++;
        e = slot;
    }
    return e;
}
