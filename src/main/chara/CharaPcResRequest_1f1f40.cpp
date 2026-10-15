#include "types.h"

#define V1(n) virtual void v##n();
#define V4(n) V1(n##0) V1(n##1) V1(n##2) V1(n##3)
#define V16(n) V4(n##0) V4(n##1) V4(n##2) V4(n##3)

class Tbl {
public:
    V16(a) V4(b0) V4(b1) V1(c0) V1(c1)
    virtual u8 *Find(s16);
};

class Obj {
public:
    V16(a) V16(b) V16(c) V16(d) V16(e) V16(f) V16(g) V16(h)
    V16(i) V16(j) V16(k) V16(l) V16(m)
    V4(n0) V4(n1) V4(n2) V1(n3) V1(n4) V1(n5)
    virtual u8 *Slot(s32);
    V4(o0) V4(o1) V4(o2) V1(o3) V1(o4) V1(o5)
    virtual u8 *Main();
    V16(p) V16(q) V4(r0) V1(r1) V1(r2)
    virtual s32 Flag();
};

typedef struct {
    s32 f[6];
    char *text;
    s32 g[7];
} Desc;

typedef struct {
    s32 id;
    s32 b;
    s32 v[7];
} Pos;

extern "C" {
extern void Sprintf_1343b8(char *, u8 *, ...);
extern void LoaderQueueAppendSeparator_1cd670(s32);
extern void CharaDataReleaseById_1ed850(s32, s32);
extern s32 CharaDataFindById_1ed990(s32, s32);
extern void CharaDataLoadSubRecById_1eda70(s32, void *);
extern s32 CharaDataCreate_1edab0(s32, Pos *);
extern void CharaLoadWeapon2Chr_1f4b50(s32, s32, s32, u8 *);
extern void CharaLoadWeapon1Chr_1f4c70(s32, s32, s32, u8 *);
extern void CharaPcLoadRequest_1f4db0(s32, s32, u8 *);
extern s32 PcIdToResIndexMaybe_1f4f90(s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern s32 GetCharaDataMgr_1fdb70(void);
extern u8 *GetGameData_1fede0(void);
extern u8 *GetWorldDataMgr_1fedf0(void);
extern Obj *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
extern char *strcpy(char *, char *);
extern s32 strlen(char *);
extern u8 D_0045B790[];
extern u8 D_0045B7D0[];
extern u8 D_0045B810[];
}

static inline void initDesc(Desc *d) {
    d->f[0] = -1;
    d->f[1] = -1;
    d->f[2] = -1;
    d->f[3] = -1;
    d->f[4] = -1;
    d->f[5] = -1;
    d->text = 0;
    d->g[0] = -1;
    d->g[1] = 0;
    d->g[2] = -1;
    d->g[3] = 0;
    d->g[4] = 0;
    d->g[5] = -1;
    d->g[6] = 0;
}

extern "C" s32 CharaPcResRequest_1f1f40(s32 a0, s32 a1, s32 id) {
    char text[256];
    Pos pos;
    Desc d1;
    Desc d2;
    Desc d3;
    char name[16];
    u8 *gm;
    s32 tbl;
    s32 no;
    u8 *r;
    s32 i;
    Obj *o;
    u8 *ent;
    Obj *obj;
    u8 *sys;
    u8 *dat;

    tbl = GetCharaDataMgr_1fdb70();
    sys = GetWorldDataMgr_1fedf0();
    gm = GetGameData_1fede0();
    if (id == 0x2F11) {
        id = 0x2B00;
    }
    obj = CharaMgrPoolFindByDataId_3a8a70(*(s32 *)(gm + 0x14), id, 1, 1, 0, 0, 0);
    if (obj == 0) {
        return 0;
    }
    ent = (*(Tbl **)(*(u8 **)(sys + 0x60) + 0xC))->Find(id);
    if (ent == 0) {
        return 0;
    }
    dat = *(u8 **)(ent + 8);
    if (dat == 0) {
        return 0;
    }
    no = *(s16 *)dat;
    pos.id = -1;
    pos.b = -1;
    for (i = 0; i < 7; i++) {
        pos.v[i] = -1;
    }
    pos.id = no;
    pos.b = 0;
    pos.v[0] = (*(s16 *)(dat + 0x6) << 10) / 16;
    pos.v[1] = (*(s16 *)(dat + 0x8) << 10) / 16;
    pos.v[2] = (*(s16 *)(dat + 0xE) << 10) / 16;
    pos.v[3] = (*(s16 *)(dat + 0x12) << 10) / 16;
    pos.v[5] = 0x280;
    pos.v[6] = 1;
    CharaDataReleaseById_1ed850(tbl, no);
    if (CharaDataFindById_1ed990(tbl, no) != 0) {
        return 1;
    }
    if (CharaDataCreate_1edab0(tbl, &pos) == 0) {
        return 0;
    }
    initDesc(&d1);
    d1.f[0] = no;
    d1.f[4] = no;
    d1.f[1] = 0;
    d1.g[0] = PcIdToResIndexMaybe_1f4f90(id);
    d1.f[2] = 0;
    d1.f[3] = 0;
    d1.text = text;
    Sprintf_1343b8(text, D_0045B790, *(s32 *)(dat + 0x20));
    CharaDataLoadSubRecById_1eda70(tbl, &d1);
    r = obj->Main();
    if (r != 0) {
        CharaPcLoadRequest_1f4db0(id, no, *(u8 **)(r + 0x10));
    } else {
        r = (*(Tbl **)(*(u8 **)(sys + 0x40) + 8))->Find(*(s16 *)(ent + 0x2A));
        if (r != 0) {
            CharaPcLoadRequest_1f4db0(id, no, r);
        }
    }
    r = obj->Slot(0);
    if (r != 0) {
        CharaLoadWeapon1Chr_1f4c70(id, no, *(s16 *)(dat + 0xC), *(u8 **)(r + 0x10));
    } else {
        r = (*(Tbl **)(*(u8 **)(sys + 0x40) + 8))->Find(*(s16 *)(ent + 0x26));
        if (r != 0) {
            CharaLoadWeapon1Chr_1f4c70(id, no, *(s16 *)(dat + 0xC), r);
        }
    }
    r = obj->Slot(1);
    if (r != 0) {
        CharaLoadWeapon2Chr_1f4b50(id, no, *(s16 *)(dat + 0x10), *(u8 **)(r + 0x10));
    } else {
        r = (*(Tbl **)(*(u8 **)(sys + 0x40) + 8))->Find(*(s16 *)(ent + 0x28));
        if (r != 0) {
            CharaLoadWeapon2Chr_1f4b50(id, no, *(s16 *)(dat + 0x10), r);
        }
    }
    initDesc(&d2);
    d2.f[0] = *(s16 *)dat;
    d2.f[3] = 4;
    d2.g[4] = 0x200;
    d2.f[1] = 0;
    d2.f[2] = 0;
    d2.text = text;
    Sprintf_1343b8(text, D_0045B810, *(s32 *)(dat + 0x28));
    CharaDataLoadSubRecById_1eda70(tbl, &d2);
    initDesc(&d3);
    d3.f[0] = no;
    d3.f[5] = no;
    d3.f[1] = 0;
    d3.f[2] = 5;
    d3.f[3] = 5;
    d3.g[2] = 7;
    d3.text = text;
    Sprintf_1343b8(text, D_0045B7D0, *(s32 *)(dat + 0x24));
    o = CharaMgrPoolFindByDataId_3a8a70(*(s32 *)(GetGameData_1fede0() + 0x14), id, 1, 1, 0, 0, 0);
    if (o != 0 && o->Flag() != 0) {
        strcpy(name, *(char **)(dat + 0x24));
        name[strlen(name) - 1] = '0';
        Sprintf_1343b8(text, D_0045B7D0, name);
    }
    CharaDataLoadSubRecById_1eda70(tbl, &d3);
    LoaderQueueAppendSeparator_1cd670(GetLoaderMgr_1f59d0());
    return 1;
}
