#include "types.h"

typedef struct Vec { f32 x, y, z, w; } Vec;
typedef struct Key { s16 id; u8 pad2[0xE]; s16 *kind; } Key;
typedef struct Arg2 { Key *key; u8 pad4[4]; s16 idx; u8 flag; } Arg2;
typedef struct Bits { u8 b0 : 1; u8 rest : 7; } Bits;

extern void GetNpcObjTable_312860(void);
extern void *GetMapMgr_201a90();
extern void GetGameData_1fede0(void);
extern void *MapFindAreaSlotById_1e4cb0(void *, s32);
extern void MapDataGetPosVec4_1e7740(void *, void *);
extern void MapDataGetRotVec4_1e7720(void *, void *);
extern void MatFromRotPos_1caf90(void *, void *, void *);
extern void VecCopy_1cbe30(void *, void *);
extern s32 MapAreaFindBlockNoByLocationId_1dcce0(void *, s32);
extern void *MapSlotsFindBlockById_1e49b0(void *, s32, s32);
extern void CfgVmReset_42fc10(void *);
extern void CfgVmRegisterCmds_42fb00(void *, void *);
extern void CfgVmLoad_42fac0(void *, s32, s32);
extern void CfgVmRun_42fa20(void *);
extern u8 D_00451D30[];
extern u8 D_004E6620[];
extern s16 D_004E6624[];
extern s16 D_004E6626[];
extern s32 D_004E6628[];
extern s32 D_004E662C[];
extern s16 D_004E6630[];
extern s16 D_004E6632[];
extern s16 D_004E6634[];
extern s16 D_004E6636[];
extern Bits D_004E6638[];
extern u8 D_004E6640[];
extern u8 D_004E6650[];
extern u8 D_004E6660[];
extern f32 D_004E66A0[];

s32 NpcCfgRun_2fcdd0(s32  raw_arg0, s32 arg1, Arg2 *arg2, s32 arg3, s16 arg4, s32 *arg5) {
    s32 arg0 = (s32 )raw_arg0;

    u8 sp8D0[16];
    Vec sp8C0;
    u8 sp90[0x830];
    void *h;
    void *e;
    s32 idx;
    s32 fl;
    s32 i;
    u8 *p;
    u32 n;
    Key *k;
    void *o;

    GetNpcObjTable_312860();
    *(Arg2 **)D_004E6620 = arg2;
    D_004E6624[0] = 0;
    D_004E6626[0] = -1;
    D_004E6628[0] = 0;
    D_004E662C[0] = arg3;
    D_004E6630[0] = arg4;
    D_004E6632[0] = 0;
    D_004E6634[0] = 0;
    h = GetMapMgr_201a90();
    GetGameData_1fede0();
    e = NULL;
    idx = arg2->idx;
    fl = arg2->flag & 1;
    if (h != NULL && (s16)idx >= 0) {
        e = MapFindAreaSlotById_1e4cb0(h, (s16)idx);
    }
    D_004E6636[0] = idx;
    D_004E6638[0].b0 = fl;
    if (e != NULL && fl != 0) {
        MapDataGetPosVec4_1e7740(e, D_004E6640);
        MapDataGetRotVec4_1e7720(e, D_004E6650);
        MatFromRotPos_1caf90(D_004E6660, D_004E6650, D_004E6640);
    } else {
        p = sp8D0;
        n = 16;
        if (p != NULL) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        VecCopy_1cbe30(D_004E6640, sp8D0);
        VecCopy_1cbe30(D_004E6650, sp8D0);
        for (i = 0; i < 4; i++) {
            VecCopy_1cbe30(D_004E6620 + i * 16 + 0x40, sp8D0);
        }
    }
    D_004E66A0[0] = 0.0f;
    if (arg2 != NULL) {
        k = arg2->key;
        if (k != NULL && k->kind != NULL && *k->kind == 10) {
            h = GetMapMgr_201a90();
            if (h != NULL) {
                o = MapFindAreaSlotById_1e4cb0(h, (s16)idx);
                if (o != NULL) {
                    o = MapSlotsFindBlockById_1e49b0(h, MapAreaFindBlockNoByLocationId_1dcce0(o, k->id) + 20000, 0);
                    if (o != NULL) {
                        MapDataGetPosVec4_1e7740(o, &sp8C0);
                        D_004E66A0[0] = sp8C0.y;
                    }
                }
            }
        }
    }
    CfgVmReset_42fc10(sp90);
    CfgVmRegisterCmds_42fb00(sp90, D_00451D30);
    CfgVmLoad_42fac0(sp90, arg0, arg1);
    CfgVmRun_42fa20(sp90);
    *arg5 = D_004E6632[0];
    return 1;
}
