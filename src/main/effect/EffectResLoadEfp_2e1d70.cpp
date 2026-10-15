#include "types.h"
#pragma opt_propagation off

typedef struct Obj {
    u8 pad[0x28];
    s32 f28;
    s32 f2C;
    s32 pad30;
    s32 f34;
} Obj;

typedef struct Ent {
    s32 id;         /* 0x00 (0x174) */
    s32 h; /* 0x04 (0x178) */
    Obj *obj;       /* 0x08 (0x17C) */
    s32 buf;        /* 0x0C (0x180) */
    char name[0x44];/* 0x10 (0x184) */
    s32 arg;        /* 0x54 (0x1C8) */
    s32 diff;       /* 0x58 (0x1CC) */
    s32 state;      /* 0x5C (0x1D0) */
    s32 f60;        /* 0x60 (0x1D4) */
    s32 f64;        /* 0x64 (0x1D8) */
    s32 f68;        /* 0x68 (0x1DC) */
    u8 used;        /* 0x6C (0x1E0) */
    u8 pad6D[3];
} Ent;

typedef struct Self {
    u8 pad[0x58];
    u8 sub[0x11C];
    Ent ent[1];
} Self;

typedef struct Res {
    s16 a;
    s32 b;
    s32 c;
    s32 d;
} Res;

typedef struct Desc {
    char tag[8];
    char *name;
    s32 arg;
    char *tagp;
    Obj *obj;
} Desc;

extern "C" {
void Sprintf_1343b8(char *, const char *, s32);
void MemStackReturnToOwnerMaybe_14dad0(Obj *);
s32 MemStackHeapAlloc_14db10(Obj *, s32, s32, s32);
void MemStackHeapFree_14dcb0(Obj *, s32);
u8 *GetDrawCtxNameTable_15de40(void);
void EffDefLoad_19fc30(s32 *, void *, s32, Desc *);
f32 EffDefGetDurationByHandle_1a0a50(void *, s32);
void GetLoaderMgr_1f59d0(void);
void EffectResSetName_2e2dc0(Self *, Ent *, s32, s32);
void EffectResAllocSlot_2e2e10(Self *, s16 *);
s32 *EffectResFindByName_2e2f10(Self *, s32);
void *memset(void *, s32, u32);
char *strcpy(char *, const char *);
extern char D_0045A818[];
extern char D_004617A0[];
extern f32 D_0047D7A4;
}

static inline bool IsSet(s32 x) { return x != 0; }

extern "C" void EffectResLoadEfp_2e1d70(Res *out, Self *self, Obj *obj, s32 key, char *name, s32 arg5, s32 rate, s32 arg7) {
    s16 idx;
    s32 i;
    s32 k;
    s32 dd;
    s32 h;
    Res r;
    Desc d;
    char buf[0x40];
    s32 ret;
    s32 *found;
    u8 flag;
    s32 size;
    s32 n;
    f32 f;
    s32 v;
    u8 *w;

    GetLoaderMgr_1f59d0();
    dd = r.d;
    ret = -1;
    idx = -1;
    if (name == 0) {
        out->a = 1; out->b = ret; out->c = 0; out->d = dd;
        return;
    }
    found = EffectResFindByName_2e2f10(self, key);
    if (found != 0) {
        v = *found; out->a = 1; out->b = v; out->c = 0; out->d = dd;
        return;
    }
    EffectResAllocSlot_2e2e10(self, &idx);
    if (idx < 0) {
        out->a = 1; out->b = -1; out->c = 0; out->d = dd;
        return;
    }
    self->ent[idx].id = idx;
    strcpy(self->ent[idx].name, name);
    k = idx;
    self->ent[idx].f60 = -1;
    self->ent[idx].state = 0;
    self->ent[idx].used = 1;
    self->ent[idx].arg = arg7;
    self->ent[idx].obj = obj;
    EffectResSetName_2e2dc0(self, &self->ent[idx], key, k);
    i = idx;
    flag = !(IsSet(self->ent[i].obj->f28) != 0);
    if (flag) {
        self->ent[i].buf = MemStackHeapAlloc_14db10(self->ent[i].obj, 2, 0, 0x40);
    }
    size = self->ent[i].obj->f34 - self->ent[i].obj->f2C;
    n = (s32)(D_0047D7A4 * (f32)rate);
    if (size < n / 16 + 1) {
        if (flag) {
            MemStackReturnToOwnerMaybe_14dad0(self->ent[i].obj);
            if (self->ent[idx].buf != 0) {
                MemStackHeapFree_14dcb0(self->ent[idx].obj, self->ent[idx].buf);
            }
        }
        memset(&self->ent[idx], 0, 0x70);
        self->ent[idx].id = -1;
        self->ent[idx].f60 = -1;
    } else {
        d.name = 0;
        d.arg = 0;
        d.obj = 0;
        strcpy(d.tag, D_0045A818);
        d.tagp = d.tag;
        d.name = self->ent[idx].name;
        d.arg = self->ent[idx].arg;
        d.obj = self->ent[idx].obj;
        w = GetDrawCtxNameTable_15de40();
        Sprintf_1343b8(buf, D_004617A0, idx);
        strcpy((char *)w + 0x1E4, buf);
        EffDefLoad_19fc30(&h, self->sub, arg5, &d);
        *(s32 *)((u8 *)self + idx * 0x70 + 0x178) = h;
        w[0x1E4] = 0;
        self->ent[idx].diff = size - (self->ent[idx].obj->f34 - self->ent[idx].obj->f2C);
        if ((IsSet(*(volatile s32 *)&self->ent[idx].h) ^ 1) == 0) {
            f = EffDefGetDurationByHandle_1a0a50(self->sub, self->ent[idx].h);
            if (f <= 0.0f) {
                f = 60.0f;
            }
            { Ent *e = (Ent *)((u8 *)self + 0x174) + idx; v = (s32)(0.5f + f); e->f68 = v; e->f64 = v; }
        }
        if (flag) {
            MemStackReturnToOwnerMaybe_14dad0(self->ent[idx].obj);
        }
        ret = idx;
        self->ent[ret].f60 = -1;
        self->ent[ret].state = 1;
    }
    out->a = 1; out->b = ret; out->c = 0; out->d = dd;
}
