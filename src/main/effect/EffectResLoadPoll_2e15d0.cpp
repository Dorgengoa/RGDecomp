#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off

struct Obj {
    u8 pad0[0x28];
    s32 x28;
    s32 x2C;
    u8 pad30[4];
    s32 x34;
    bool Valid() { return x28 != 0; }
};

struct Desc {
    char name[8];
    u8 *e8;
    s32 ec;
    char *f0;
    Obj *f4;
};

#define ENT(i) ((u8 *)self + (i) * 0x70)
#define F32(p, o) (*(s32 *)((p) + (o)))

static inline bool NonZero(s32 *p) { return *p != 0; }
static inline bool IsZero(s32 *p) { return !NonZero(p); }

extern "C" {
void Sprintf_1343b8(char *, const char *, s32);
void MemStackReturnToOwnerMaybe_14dad0(Obj *);
s32 MemStackHeapAlloc_14db10(Obj *, s32, s32, s32);
void MemStackHeapFree_14dcb0(Obj *, s32);
u8 *GetDrawCtxNameTable_15de40(void);
void EffDefLoad_19fc30(s32 *, u8 *, s32, Desc *);
f32 EffDefGetDurationByHandle_1a0a50(u8 *, s32);
void LoaderReleaseById_1cd340(s32, s32);
s32 LoaderGetData_1cd490(s32, s32, s32 *);
s32 LoaderGetStatus_1cd4f0(s32, s32);
s32 GetLoaderMgr_1f59d0(void);
void *memset(void *, s32, u32);
char *strcpy(char *, const char *);
extern char D_0045A818[];
extern char D_004617A0[];
extern f32 D_0047D7A4;
}

extern "C" s32 EffectResLoadPoll_2e15d0(u8 *self) {
    s32 cnt;
    s32 out;
    Desc desc;
    char buf[0x40];
    s32 h;
    s32 i;
    u8 *e;
    s32 *ps;
    s32 *pid;
    Obj **po;
    u8 need;
    s32 size;
    s32 r;
    s32 n;
    u8 *m;
    f32 f;
    s32 v;
    s32 *px;
    Obj *o;
    s32 k;
    u8 *t;
    bool nz;

    h = GetLoaderMgr_1f59d0();
    for (i = 0; i < 48; i++) {
        e = ENT(i);
        ps = (s32 *)(e + 0x1D0);
        if (F32(e, 0x1D0) != 0) {
            continue;
        }
        pid = (s32 *)(e + 0x1D4);
        k = F32(e, 0x1D4);
        if (k == -1) {
            continue;
        }
        k = LoaderGetStatus_1cd4f0(h, k);
        *ps = k;
        if (k != 1) {
            continue;
        }
        o = *(Obj **)(e + 0x17C);
        need = !(o->Valid() != 0);
        po = (Obj **)(e + 0x17C);
        if (need) {
            t = ENT(i);
            F32(t, 0x180) = MemStackHeapAlloc_14db10(o, 2, 0, 0x40);
        }
        o = *po;
        size = o->x34 - o->x2C;
        r = LoaderGetData_1cd490(h, *pid, &cnt);
        n = (s32)(D_0047D7A4 * (f32)cnt) / 16;
        if (size < n + 1) {
            LoaderReleaseById_1cd340(h, *pid);
            if (need) {
                e = ENT(i);
                MemStackReturnToOwnerMaybe_14dad0(*po);
                k = F32(e, 0x180);
                if (k != 0) {
                    MemStackHeapFree_14dcb0(*po, k);
                }
            }
            memset(ENT(i) + 0x174, 0, 0x70);
            k = *pid;
            if (k >= 0) {
                LoaderReleaseById_1cd340(h, k);
            }
            t = ENT(i);
            *pid = F32(t, 0x174) = -1;
        } else {
            desc.e8 = 0;
            desc.ec = 0;
            desc.f4 = 0;
            strcpy(desc.name, D_0045A818);
            desc.f0 = desc.name;
            t = ENT(i);
            desc.e8 = t + 0x184;
            desc.ec = F32(t, 0x1C8);
            desc.f4 = *po;
            m = GetDrawCtxNameTable_15de40();
            Sprintf_1343b8(buf, D_004617A0, i);
            strcpy((char *)m + 0x1E4, buf);
            EffDefLoad_19fc30(&out, self + 0x58, r, &desc);
            px = (s32 *)(e + 0x178);
            F32(e, 0x178) = out;
            m[0x1E4] = 0;
            t = ENT(i);
            o = *po;
            F32(t, 0x1CC) = size - (o->x34 - o->x2C);
            if (!IsZero(px)) {
                f = EffDefGetDurationByHandle_1a0a50(self + 0x58, *px);
                if (f <= 0.0f) {
                    f = 60.0f;
                }
                t = ENT(i);
                v = 0.5f + f;
                F32(t, 0x1DC) = v;
                F32(t, 0x1D8) = v;
            }
            if (need) {
                MemStackReturnToOwnerMaybe_14dad0(*po);
            }
            pid = (s32 *)(ENT(i) + 0x1D4);
            LoaderReleaseById_1cd340(h, *pid);
            *pid = -1;
        }
    }
    return 0;
}
