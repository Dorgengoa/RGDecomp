/* rgp:protos */
#line 1
#include "types.h"

typedef struct Vec3 { s32 x, y, z; } Vec3;
typedef struct Obj { u8 pad[0x1F0]; Vec3 pos; } Obj;
typedef struct Ent { u8 pad0[4]; char *name; u8 pad8[0xA44 - 8]; s32 fA44; u8 padA48[0xB20 - 0xA48]; s32 fB20; } Ent;
typedef struct Self {
    u8 pad0[0x3D0];
    u64 fl;          /* 3D0 */
    u8 pad3D8[0x3F4 - 0x3D8];
    Obj *p3F4;       /* 3F4 */
    u8 pad3F8[4];
    s32 f3FC;        /* 3FC */
    u8 pad400[8];
    s32 flags;       /* 408 */
    u8 pad40C[0x424 - 0x40C];
    s16 id;          /* 424 */
    u8 pad426[2];
    s32 f428;        /* 428 */
    u8 pad42C[0xA2E - 0x42C];
    s16 fA2E;        /* A2E */
    u8 padA30[8];
    s16 fA38;        /* A38 */
    u8 padA3A[0xA8C - 0xA3A];
    char name[1];    /* A8C */
} Self;

extern "C" {
s32 MotionListFindByName_1721d0(Vec3 *, char *, s32 *, s32 *);
s32 ObjIdResolveAlias_1ce490(s32, s32);
char *strcpy(char *, const char *);
s32 StrEqualNonNull_1ca6c0(char *, char *);
Ent *ActCfgTableFindNameById_223270(s32, s32);
char *CharaGetCurMotionName_238560(Self *);
void MotionListResetAll_171e00(Vec3 *);
void ModelObjPlayMotionByName_1867a0(Obj *, char *, s32);
void ModelObjSetMotionBlendSpeed_1add60(Obj *, f32);
void *GetActionMgr_1fdb50(void);
void *GetCurrentScene_1f5be0(void);
Self *ActionMgrFindById_233b50(void *, s32);
Obj *ObjRecGetLiveObject_1c4a90(void *, s32);
}
extern "C" char D_0045C8F0[];
extern "C" char D_0045C910[];
extern "C" char D_0045CA28[];

static inline s32 hit(Obj *p, char *name, Vec3 *v, s32 *a, s32 *b) {
    if (p == 0 || name == 0) return 0;
    *v = p->pos;
    return MotionListFindByName_1721d0(v, name, b, a);
}

extern "C" void CharaPlayMotion_212590(Self *self, Obj *obj, char *name, s32 flags, f32 f) {
    s32 b2;
    s32 a2;
    s32 b1;
    s32 a1;
    Vec3 v2 __attribute__((aligned(16)));
    Vec3 v1 __attribute__((aligned(16)));
    s32 list[32] __attribute__((aligned(16)));
    Ent *h;
    bool ok;
    bool fresh;
    s32 n;
    s32 i;
    s32 j;
    void *s6;
    void *s7;
    Obj *o;
    s32 id;
    s32 r;
    s32 *lp;
    Self *e;

    if (obj == 0 || name == 0) return;
    if (*name == '#') return;
    if (self->fA2E == 1) {
        h = 0;
        if (((unsigned char)StrEqualNonNull_1ca6c0(name, D_0045C8F0))) h = ActCfgTableFindNameById_223270(self->f428, 200);
        if (h == 0 && ((unsigned char)StrEqualNonNull_1ca6c0(name, D_0045C910))) h = ActCfgTableFindNameById_223270(self->f428, 201);
        if (h != 0) name = h->name;
    }
    if (name != 0 && *name == '#') ok = true;
    else ok = hit(self->p3F4, name, &v1, &a1, &b1) != 0;
    if (!ok) return;
    fresh = ((flags & 2) != 0 || !(self->fA38 != 0)) && ((unsigned char)StrEqualNonNull_1ca6c0(name, CharaGetCurMotionName_238560(self))) != 0;
    if (!(f < 1.0f)) f = 1.0f;
    if (f <= 0.0f) f = 1.0f;
    self->flags = flags;
    strcpy(self->name, name);
    if (fresh) {
        self->f3FC = 0;
        MotionListResetAll_171e00(&obj->pos);
    }
    ModelObjPlayMotionByName_1867a0(obj, self->name, self->flags);
    ModelObjSetMotionBlendSpeed_1add60(obj, f);
    n = 0;
    if (self->fl & 0x800000) {
        r = ObjIdResolveAlias_1ce490(self->id, -10);
        list[n] = r;
        if (r >= 0) n++;
    }
    if (self->fl & 0x400000) {
        r = ObjIdResolveAlias_1ce490(self->id, -11);
        list[n] = r;
        if (r >= 0) n++;
    }
    if (self->fl & 0x200000) {
        r = ObjIdResolveAlias_1ce490(self->id, -20);
        list[n] = r;
        if (r >= 0) n++;
    }
    if (self->fl & 0x100000) {
        r = ObjIdResolveAlias_1ce490(self->id, -21);
        list[n] = r;
        if (r >= 0) n++;
    }
    s6 = GetActionMgr_1fdb50();
    s7 = GetCurrentScene_1f5be0();
    if (self->fl & 0x80000) {
        for (i = self->id + 1; i <= 155; i++) {
            e = ActionMgrFindById_233b50(s6, i);
            if (e == 0) break;
            if (!(((Ent *)e)->fA44 & 0x80000)) break;
            if (((Ent *)e)->fB20 != self->id) break;
            list[n++] = i;
        }
    }
    for (j = 0; j < n; j++) {
        lp = (s32 *)((u32)&list[j]);
        id = *lp;
        o = ObjRecGetLiveObject_1c4a90(s7, id);
        if (o == 0) continue;
        if (!hit(o, self->name, &v2, &a2, &b2)) {
            if (id == 0x24) {
                if (fresh) MotionListResetAll_171e00(&o->pos);
                ModelObjPlayMotionByName_1867a0(o, D_0045CA28, self->flags & ~2);
                ModelObjSetMotionBlendSpeed_1add60(o, f);
            }
        } else {
            e = ActionMgrFindById_233b50(s6, id);
            if (e != 0) {
                CharaPlayMotion_212590(e, o, self->name, self->flags, f);
            } else {
                if (fresh) MotionListResetAll_171e00(&o->pos);
                ModelObjPlayMotionByName_1867a0(o, self->name, self->flags);
                ModelObjSetMotionBlendSpeed_1add60(o, f);
            }
        }
    }
}
