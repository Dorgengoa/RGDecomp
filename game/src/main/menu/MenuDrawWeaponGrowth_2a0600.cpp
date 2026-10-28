#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v60() { return VCM0(s32, 0x60); }
    s32 v64() { return VCM0(s32, 0x64); }
    
    
    
    
    s32 v78() { return VCM0(s32, 0x78); }
    
    
    
    
    
    s32 v90(s32 a0) { return VCM(s32, (void *, s32), 0x90, a0); }
    s32 v94(s32 a0) { return VCM(s32, (void *, s32), 0x94, a0); }
};

typedef struct Info {
    u8 pad0[0x2C];
    s16 x2C;
} Info;

typedef struct Holder {
    Obj o;
    u8 pad4[0xC];
    Info *info;
} Holder;

typedef struct E {
    s16 x0;
    u8 pad2[2];
    s16 x4;
    u8 pad6[6];
    s16 xC;
    u8 padE[0x12];
} E;

typedef struct R {
    s16 x0;
    s16 x2;
    u8 pad4[0x1C];
    s16 x20;
    u8 pad22[6];
    s16 x28;
    s16 x2A;
} R;

typedef struct P {
    u8 pad0[8];
    s64 x8;
    u8 pad10[0x10];
} P;

extern "C" {
R *UiSetItemIconSprite_288490(s32, s32, s32, s32, s32, s32);
P *UiGetWidgetSubItem_28f2b0(s32, s32, s32);
E *UiGetWidgetSprite_28fe10(s32, s32, s32);
s32 UiFindWidget_290460(s32, s32);
}

extern "C" s32 MenuDrawWeaponGrowth_2a0600(s32 arg0, s32 arg1, Obj *obj, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    R *r;
    E *w;
    s32 i;
    s32 cur;
    s32 max;
    R *r2;
    s32 f;
    P *p;
    s32 a;
    s32 fa;
    s32 fb;
    s32 bb;
    E *q;
    s32 t;
    s32 k;
    E *e;

    if (obj == 0) {
        return 0;
    }
    r = UiSetItemIconSprite_288490(arg0, UiFindWidget_290460(arg1, arg3), ((Holder *)obj)->info->x2C, 0x28, 0x2D, 1);
    r->x0 = 0x12;
    r->x2 = 0xA;
    w = UiGetWidgetSprite_28fe10(arg1, arg4, 0);
    for (i = 3; i < 0x18; i++) {
        w[i].xC = 0;
        w[i].x4 = 0;
    }
    cur = obj->v60();
    max = obj->v64();
    r2 = (R *)UiGetWidgetSprite_28fe10(arg1, arg5, 0);
    if (r2 == 0) {
        return 0;
    }
    if (cur == 0) {
        w[2].xC = 0xA;
        w[2].x4 = 0xA;
        w[0].xC = 0xA;
        w[0].x4 = 0xA;
        w[1].x4 = 0x2A;
        w[18].xC = 0;
        w[18].x4 = 0;
        r2->x20 = -1;
    } else {
        f = (s32)(52.0f * ((f32)cur / (f32)max));
        if (cur == max) {
            w[2].xC = 0;
            cur = 0;
            w[2].x4 = 0;
            max = 0;
            w[1].xC = 0;
            w[1].x4 = 0;
            w[0].xC = 0;
            w[0].x4 = 0;
            w[18].xC = 0;
            w[18].x4 = 0;
            do {
                if (obj->v90(max) == obj->v94(max)) {
                    cur++;
                }
                max++;
            } while (max < 5);
            if (cur == 5) {
                r2->x28 = 0x36;
                r2->x2A = 0x30;
            } else {
                r2->x28 = 0;
                r2->x2A = 0x30;
            }
            r2->x20 = 0x68;
        } else {
            w[2].xC = 0xA;
            w[2].x4 = 0xA;
            w[0].xC = 0xA;
            w[0].x4 = 0xA;
            w[1].x4 = 0x2A;
            w[1].xC = 8;
            w[18].x4 = f;
            w[18].xC = 8;
            r2->x20 = -1;
        }
    }
    p = UiGetWidgetSubItem_28f2b0(arg1, arg6, 0);
    if (p == 0) {
        return 0;
    }
    p->x8 = obj->v78();
    for (i = 0; i < 5; i++) {
        a = obj->v90(i);
        bb = obj->v94(i);
        fa = (s32)(88.0f * ((f32)a / 99.0f));
        fb = (s32)(90.0f * ((f32)bb / 99.0f));
        k = i * 3;
        q = UiGetWidgetSprite_28fe10(arg1, arg4, 0);
        if (q == 0) {
            return 0;
        }
        if (fb >= 2) {
            q[k + 3].xC = 1;
            q[k + 4].xC = 8;
            q[k + 5].xC = 1;
            q[k + 3].x4 = 1;
            t = fb - 2;
            q[k + 4].x4 = t;
            if ((s16)t == 0) {
                q[k + 4].x4 = 0;
                q[k + 4].xC = 0;
            }
            e = &q[(u32)k];
            e[5].x4 = 1;
            e[5].x0 = e[3].x0 + q[k + 4].x4 + 1;
        }
        q[i + 19].x4 = fa;
        if ((s16)fa != 0) {
            q[i + 19].xC = 8;
        }
        p++;
        p->x8 = a;
    }
    return 1;
}
