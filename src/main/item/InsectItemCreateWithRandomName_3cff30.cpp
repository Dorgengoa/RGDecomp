#pragma divbyzerocheck on
#include "types.h"

typedef struct {
    s16 unk0;
    u8 pad2[0xC - 0x2];
    char *unkC;
} Def;

class Obj {
public:
    virtual void v008();
    virtual void v00C();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01C();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02C();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03C();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04C();
    virtual void v050();
    virtual void v054();
    virtual void v058();
    virtual void v05C();
    virtual void v060();
    virtual void v064();
    virtual void v068();
    virtual void v06C();
    virtual void v070();
    virtual void v074();
    virtual void v078();
    virtual void v07C();
    virtual void v080();
    virtual void v084();
    virtual void v088();
    virtual void v08C();
    virtual void v090();
    virtual void v094();
    virtual void v098();
    virtual void v09C();
    virtual void v0A0();
    virtual void v0A4();
    virtual void v0A8();
    virtual void v0AC();
    virtual void v0B0();
    virtual void v0B4();
    virtual void v0B8();
    virtual void v0BC();
    virtual void v0C0();
    virtual void v0C4();
    virtual void v0C8();
    virtual void v0CC();
    virtual void v0D0();
    virtual void v0D4();
    virtual void v0D8();
    virtual void v0DC();
    virtual void v0E0();
    virtual void v0E4();
    virtual void v0E8();
    virtual void v0EC();
    virtual void v0F0();
    virtual void v0F4();
    virtual void v0F8();
    virtual void v0FC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114(char *);
    virtual void v118();
    virtual void v11C();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12C();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13C();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14C();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15C();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16C();
    virtual void v170();
    virtual void v174();
    virtual void v178();
    virtual void v17C();
    virtual void v180();
    virtual void v184();
    virtual void v188();
    virtual void v18C();
    virtual void v190();
    virtual void v194();
    virtual void v198();
    virtual s32 v19C();
    virtual void v1A0();
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
extern void IterInit_370170(void *, s32);
extern s32 InvAddItemCoreMaybe_3c6540(s32, s32, s32, s32, s32, s32, s32);
extern u8 InsectRecSlotAddItem_3d0190(s32, Obj *);
extern s32 InsectRecSlotFindFree_3d0210(void);
extern Obj *InvObjCastToInsect_3d3d10(s32);
extern char *strncpy(char *, const char *, u32);
extern Mgr1 *D_004838E8;
extern Mgr2 *D_004838EC;
}

extern "C" Obj *InsectItemCreateWithRandomName_3cff30(s32 arg0, s32 arg1)
{
    u8 it[8];
    char buf[0x18];
    s32 arr[0x40];
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

    if (InsectRecSlotFindFree_3d0210() < 0) {
        return 0;
    }
    id = InvAddItemCoreMaybe_3c6540(D_004838E8->unk18, arg1, 7, 1, -1, 0, 0);
    if (id == 0) {
        return 0;
    }
    o = InvObjCastToInsect_3d3d10(id);
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
        IterInit_370170(it, t);
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
