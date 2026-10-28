#include "types.h"

#define V1(n) virtual void v##n();
#define V4(n) V1(n##0) V1(n##1) V1(n##2) V1(n##3)
#define V16(n) V4(n##0) V4(n##1) V4(n##2) V4(n##3)

class VTbl {
public:
    VC_VPTR_MEMBER;                         
    u8 * get(s16 a0) { return VCM(u8 *, (void *, s16), 0x70, a0); }
};

class GObj {
public:
    VC_VPTR_MEMBER;                                                                                                                               
                                                                                                   
    u8 * Slot() { return VCM0(u8 *, 0x388); }
    u8 * Slot2() { return VCM0(u8 *, 0x38C); }
                
    u8 * Main() { return VCM0(u8 *, 0x3C4); }
                                         
    s32 Named() { return VCM0(s32, 0x460); }
};

typedef struct Def {
    u8 pad0[0x20];
    char *s20;
    char *s24;
    char *s28;
} Def;

typedef struct Ent {
    u8 pad0[0x8];
    Def *def;       /* 0x08 */
    u8 padC[0x26 - 0xC];
    s16 x26;
    s16 x28;
    s16 x2A;
} Ent;

typedef struct Sys {
    u8 pad0[0x40];
    struct { u8 pad0[0x8]; VTbl *tbl; } *m40;
    u8 pad44[0x60 - 0x44];
    struct { u8 pad0[0xC]; VTbl *tbl; } *m60;
} Sys;

typedef struct Gm {
    u8 pad0[0x14];
    s32 x14;
} Gm;

typedef struct NameTbl {
    char name[16][0x100];
    s32 id[16];
} NameTbl;

extern "C" {
Gm *GetGameData_1fede0(void);
Sys *GetWorldDataMgr_1fedf0(void);
s32 GetLoaderMgr_1f59d0(void);
NameTbl *GetFileNameSlotTable_1ed0c0(void);
GObj *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
void Sprintf_1343b8(char *, char *, char *);
s32 LoaderRequestFile_1cd870(s32, char *, s32);
char *CharaPcResNameBuildMaybe_40dc60(u8 *);
void CharaPcBuildPath_1f4ef0(char *, u8 *);
u32 strlen(char *);
char *strcpy(char *, char *);
extern char D_0045B790[];
extern char D_0045B7D0[];
extern char D_0045B810[];
extern char D_0045B870[];
void CharaPcResNamesQueue_1f17d0(s32 id);
}

static inline void addName(NameTbl *t, s32 dm, char *buf) {
    s32 h = LoaderRequestFile_1cd870(dm, buf, 0);
    if (strlen(buf) < 0x100) {
        s32 i;
        for (i = 0; i < 16; i++) {
            if (t->id[i] < 0) {
                break;
            }
        }
        if (i != 16) {
            t->id[i] = h;
            strcpy(t->name[i], buf);
        }
    }
}

extern "C" void CharaPcResNamesQueue_1f17d0(s32 id)
{
    char buf[0x100] __attribute__((aligned(16)));
    Gm *gm;
    Sys *sys;
    s32 dm;
    NameTbl *t;
    Ent *e;
    Def *d;
    GObj *obj;
    u8 *p;
    u8 *q;

    gm = GetGameData_1fede0();
    sys = GetWorldDataMgr_1fedf0();
    dm = GetLoaderMgr_1f59d0();
    t = GetFileNameSlotTable_1ed0c0();
    if (t == 0) {
        return;
    }
    e = (Ent *)sys->m60->tbl->get(id);
    if (e == 0) {
        return;
    }
    d = e->def;
    if (d == 0) {
        return;
    }
    obj = CharaMgrPoolFindByDataId_3a8a70(gm->x14, id, 1, 1, 0, 0, 0);
    if (obj == 0) {
        return;
    }
    Sprintf_1343b8(buf, D_0045B790, d->s20);
    addName(t, dm, buf);
    p = obj->Main();
    if (p != 0) {
        q = *(u8 **)(p + 0x10);
        if (q != 0) {
            if (obj->Named()) {
                CharaPcBuildPath_1f4ef0(buf, q);
            } else {
                Sprintf_1343b8(buf, D_0045B790, CharaPcResNameBuildMaybe_40dc60(q));
            }
            addName(t, dm, buf);
        }
    } else {
        q = sys->m40->tbl->get(e->x2A);
        if (q != 0) {
            if (obj->Named()) {
                CharaPcBuildPath_1f4ef0(buf, q);
            } else {
                Sprintf_1343b8(buf, D_0045B790, CharaPcResNameBuildMaybe_40dc60(q));
            }
            addName(t, dm, buf);
        }
    }
    p = obj->Slot();
    if (p != 0) {
        q = *(u8 **)(p + 0x10);
        if (q != 0) {
            Sprintf_1343b8(buf, D_0045B870, CharaPcResNameBuildMaybe_40dc60(q));
            addName(t, dm, buf);
        }
    } else {
        q = sys->m40->tbl->get(e->x26);
        if (q != 0) {
            Sprintf_1343b8(buf, D_0045B870, CharaPcResNameBuildMaybe_40dc60(q));
            addName(t, dm, buf);
        }
    }
    p = obj->Slot2();
    if (p != 0) {
        q = *(u8 **)(p + 0x10);
        if (q != 0) {
            Sprintf_1343b8(buf, D_0045B870, CharaPcResNameBuildMaybe_40dc60(q));
            addName(t, dm, buf);
        }
    } else {
        q = sys->m40->tbl->get(e->x28);
        if (q != 0) {
            Sprintf_1343b8(buf, D_0045B870, CharaPcResNameBuildMaybe_40dc60(q));
            addName(t, dm, buf);
        }
    }
    Sprintf_1343b8(buf, D_0045B810, d->s28);
    addName(t, dm, buf);
    Sprintf_1343b8(buf, D_0045B7D0, d->s24);
    addName(t, dm, buf);
}
