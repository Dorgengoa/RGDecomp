/* rgp:protos */
#define RGP_SELF_EffectResRequestEfp_2e21a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 a;
    s32 b;
    s32 c;
    s32 d;
} Ret;

typedef struct {
    s32 id;
    s32 pad4;
    s32 key;
    s32 padC;
    char name[0x44];
    s32 y;
    s32 pad1CC;
    s32 z;
    s32 handle;
    s32 pad1D8;
    s32 pad1DC;
    u8 flag;
    u8 pad[3];
} Ent;

typedef struct {
    u8 pad[0x174];
    Ent ent[1];
} Mgr;

s32 Sprintf_1343b8();
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
char *strcpy(char *, const char *);
extern char D_00461778[];
extern char D_00461780[];
extern char D_004617B0[];

void EffectResRequestEfp_2e21a0(Ret *out, Mgr *p, s32 key, s32 id, char *name, s32 y) {
    Ret r __attribute__((aligned(16)));
    s32 h;
    s32 t;
    s16 i;
    s32 *found;
    s16 idx;
    char buf[64] __attribute__((aligned(16)));

    h = ((s32)GetLoaderMgr_1f59d0());
    idx = -1;
    if (name == 0) {
        out->a = 1;
        out->b = -1;
        out->c = 0;
        out->d = r.d;
        return;
    }
    found = ((s32 *)EffectResFindByName_2e2f10(p, id));
    if (found != 0) {
        t = *found;
        out->a = 1;
        out->b = t;
        out->c = 0;
        out->d = r.d;
        return;
    }
    EffectResAllocSlot_2e2e10(p, &idx);
    if (idx < 0) {
        out->a = 1;
        out->b = -1;
        out->c = 0;
        out->d = r.d;
        return;
    }
    p->ent[idx].id = idx;
    strcpy(p->ent[idx].name, name);
    i = idx;
    p->ent[i].handle = -1;
    p->ent[i].z = 0;
    p->ent[i].flag = 1;
    p->ent[idx].y = y;
    p->ent[idx].key = key;
    EffectResSetName_2e2dc0(p, &p->ent[idx], id);
    Sprintf_1343b8(p->ent[idx].name, D_00461778, p->ent[idx].name, D_004617B0);
    Sprintf_1343b8(buf, D_00461778, D_00461780, p->ent[idx].name);
    t = LoaderRequestFile_1cd870(h, buf, 0);
    p->ent[idx].handle = t;
    LoaderQueueAppendSeparator_1cd670(h);
    i = idx;
    if (p->ent[i].handle == -1) {
        out->a = 1;
        out->b = -1;
        out->c = 0;
        out->d = r.d;
    } else {
    out->a = 1;
    out->b = i;
    out->c = 0;
    out->d = r.d;
    }
}
