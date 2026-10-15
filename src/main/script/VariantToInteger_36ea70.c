#include "types.h"

typedef struct Val Val;
struct Val {
    u32 type;
    u32 pad4;
    union {
        s8 b;
        s16 h;
        s32 w;
        s64 d;
    } u;
    u8 pad10[0x20 - 0x10];
    void (*cb)(Val *, void *, s32, s32);
    u8 pad24[4];
    u8 data[8];
};

s64 VariantGetU64_36f8f0(Val *);
s64 VariantGetS64_36f9a0(Val *);
s32 VariantGetU32_36fa50(Val *);
s32 VariantGetS32_36fb30(Val *);
s16 VariantGetU16_36fbe0(Val *);
s16 VariantGetS16_36fcc0(Val *);
s8 VariantGetU8_36fd70(Val *);
s8 VariantGetS8_36fe50(Val *);

typedef s8 T_b;
typedef s16 T_h;
typedef s32 T_w;
typedef s64 T_d;
#define NOTIFY(v) if ((v)->cb != NULL) { (v)->cb((v), (v)->data, 0, 0); }

void VariantToInteger_36ea70(Val *v)
{
    switch (v->type) {
    case 1:
        {
            T_b t = VariantGetS8_36fe50(v);
            v->type = 1;
            v->u.b = t;
        }
        NOTIFY(v);
        break;
    case 2:
        {
            T_b t = VariantGetU8_36fd70(v);
            v->type = 2;
            v->u.b = t;
        }
        NOTIFY(v);
        break;
    case 3:
        {
            T_h t = VariantGetS16_36fcc0(v);
            v->type = 3;
            v->u.h = t;
        }
        NOTIFY(v);
        break;
    case 4:
        {
            T_h t = VariantGetU16_36fbe0(v);
            v->type = 4;
            v->u.h = t;
        }
        NOTIFY(v);
        break;
    case 5:
        {
            T_w t = VariantGetS32_36fb30(v);
            v->type = 5;
            v->u.w = t;
        }
        NOTIFY(v);
        break;
    case 6:
        {
            T_w t = VariantGetU32_36fa50(v);
            v->type = 6;
            v->u.w = t;
        }
        NOTIFY(v);
        break;
    case 7:
        {
            T_d t = VariantGetS64_36f9a0(v);
            v->type = 7;
            v->u.d = t;
        }
        NOTIFY(v);
        break;
    case 8:
        {
            T_d t = VariantGetU64_36f8f0(v);
            v->type = 8;
            v->u.d = t;
        }
        NOTIFY(v);
        break;
    case 9:
        {
            T_d t = VariantGetS64_36f9a0(v);
            v->type = 7;
            v->u.d = t;
        }
        NOTIFY(v);
        break;
    case 10:
        {
            T_d t = VariantGetS64_36f9a0(v);
            v->type = 7;
            v->u.d = t;
        }
        NOTIFY(v);
        break;
    }
}
