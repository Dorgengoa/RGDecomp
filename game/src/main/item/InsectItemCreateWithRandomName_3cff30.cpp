/* rgp:protos */
#line 1
#pragma divbyzerocheck on
#include "types.h"

typedef struct {
    s16 unk0;
    u8 pad2[0xC - 0x2];
    char *unkC;
} Def;

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v114(char * a0) { VCM(void, (void *, char *), 0x114, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v19C() { return VCM0(s32, 0x19C); }
    
    u8 pad4[0xC];
    Def *unk10;
};

typedef struct {
    u8 pad0[2];
    s16 unk2;
    u8 k : 2;
    u8 cnt : 6;
    u8 pad5[3];
    s32 *unk8;
} Ent;

typedef struct {
    u8 pad0[0x9C];
    struct {
        u8 pad0[0x18];
        s32 unk18;
    } *unk9C;
} Mgr2;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} Mgr1;

extern "C" {
extern s32 Rand_133710(void);
extern Ent *IterNext_370040(void *);
extern void IterInit_370170(void *, s32, int, int);
extern s32 InvAddItemCoreMaybe_3c6540(s32, s32, s32, s32, s32, s32, s32);
extern u8 InsectRecSlotAddItem_3d0190(s32, Obj *);
extern s32 InsectRecSlotFindFree_3d0210(void *);
extern Obj * InvObjCastToInsect_3d3d10(s32, int, int, int);
extern char *strncpy(char *, const char *, u32);
extern Mgr1 *D_004838E8;
extern Mgr2 *D_004838EC;
}

extern "C" Obj *InsectItemCreateWithRandomName_3cff30(s32 arg0, s32 arg1)
{
    u8 it[8];
    char buf[0x18] __attribute__((aligned(16)));
    s32 arr[0x40] __attribute__((aligned(16)));
    s32 id;
    Obj *o;
    char *p;
    s8 c;
    s32 t;
    Ent *e;
    s16 n;
    s32 i;
    s32 k;
    s32 m;

    if (InsectRecSlotFindFree_3d0210((void *)arg0) < 0) {
        return 0;
    }
    id = InvAddItemCoreMaybe_3c6540(D_004838E8->unk18, arg1, 7, 1, -1, 0, 0);
    if (id == 0) {
        return 0;
    }
    o = InvObjCastToInsect_3d3d10(id, 0, 0, 0);
    if (o == 0) {
        return 0;
    }
    strncpy(buf, o->unk10->unkC, 6);
    buf[6] = 0;
    for (p = buf; *p != 0; p++) {
        c = *p;
        if (c >= 0x61 && c < 0x7B) {
            c -= 0x20;
        }
        *p = c;
    }
    o->v114(buf);
    if (D_004838EC != 0) {
        t = D_004838EC->unk9C->unk18;
        if (t != 0) {
            t += 0x88;
        }
        IterInit_370170(it, t, 0, 0);
        for (;;) {
            e = IterNext_370040(it);
            if (e == 0) {
                break;
            }
            if (e->unk2 != o->unk10->unk0) {
                continue;
            }
            n = 0;
            for (i = 0; i < e->cnt; i++) {
                k = e->k;
                if (k == 0 || k == (u8)((o->v19C() != 0) ^ 1) + 1) {
                    arr[n] = e->unk8[i];
                    n++;
                }
            }
            m = n;
            if (m > 0) {
                o->v114((char *)arr[Rand_133710() % m]);
            }
            break;
        }
    }
    if (InsectRecSlotAddItem_3d0190(arg0, o) != 0) {
        return o;
    }
    return 0;
}
