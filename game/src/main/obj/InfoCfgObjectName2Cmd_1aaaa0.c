/* rgp:protos */
#define RGP_SELF_InfoCfgObjectName2Cmd_1aaaa0 1
#define RGP_SELF_ObjAttachPointCtor_1aae00 1
#define RGP_SELF_getEntry 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Entry {
    s32 id;
    f32 f;
    s32 type;
    s32 flag;
    f32 v[4];
} Entry;

typedef struct Mgr {
    u8 pad000[0x20C];
    s32 count;
    Entry *list;
    u8 pad214[0x258];
    s32 x46C[2];
} Mgr;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
char *strcpy(char *, const char *);
extern Mgr *D_0049D418[];
extern s32 D_0049D398[];
extern s32 D_0049D430[];
extern u8 ObjAttachPointCtor_1aae00[];

static inline Entry *getEntry(Mgr *m) {
    Entry *list;
    s32 cur;
    cur = D_0049D430[0];
    list = m->list;
    if (list == 0) {
        return 0;
    }
    if (cur < 0 || cur >= m->count) {
        return 0;
    }
    return &list[cur];
}

s32 InfoCfgObjectName2Cmd_1aaaa0(s64 *args, s32 argc) {
    char buf[64] __attribute__((aligned(16)));
    Mgr *m;
    s32 heap;
    s32 type;
    s32 i;
    s32 n;
    Entry *e;
    s32 id;
    f32 f;
    s32 *slot;
    Entry *e2;
    s32 n2;

    m = D_0049D418[0];
    heap = D_0049D398[0];
    if (m == 0 || heap == 0) {
        return 0;
    }
    if (m->list == 0) {
        m->count = 0x18;
        m->list = (Entry *)((s32)ConstructNewArray_100710(MemStackNew_14e1b0(0x310, heap), ObjAttachPointCtor_1aae00, 0, 0x20, 0x18));
        if (m->list == 0) {
            m->count = 0;
        } else {
            for (i = 0; i < m->count; i++) {
                m->list[i].id = -1;
            }
        }
        D_0049D430[0] = 0;
    }
    type = VariantGetInt_15f780(args++);
    if (ModelGetRootFrame_1511a0(m) == 0) {
        return 0;
    }
    if (type < 5) {
        n = (argc - 1) / 2;
        if (argc < 3) {
            n = 1;
        }
        for (i = 0; i < n; i++) {
            e = getEntry(m);
            if (e == 0) {
                return 0;
            }
            strcpy(buf, ((char *)SlotGetInt_15f720(args++)));
            id = ModelFindFrameIndexByName_151220(m, buf);
            f = 0.0f;
            if (type >= 2) {
                f = VariantGetFloat_15f740(args++);
            } else if (argc >= 3) {
                f = VariantGetFloat_15f740(args++);
            }
            if (id >= 0) {
                if (type < 2) {
                    m->x46C[type] = id;
                }
                e->id = id;
                e->f = f;
                e->type = type;
                e->flag = 1;
                D_0049D430[0]++;
            }
        }
        return 1;
    }
    id = ModelFindFrameIndexByName_151220(m, ((char *)SlotGetInt_15f720(args++)));
    if (id < 0) {
        return 0;
    }
    e2 = getEntry(m);
    if (e2 == 0) {
        return 0;
    }
    n2 = argc - 2;
    e2->id = -1;
    e2->f = 0.0f;
    e2->type = 0;
    e2->flag = 1;
    e2->v[3] = 0.0f;
    e2->v[2] = 0.0f;
    e2->v[1] = 0.0f;
    e2->v[0] = 0.0f;
    e2->id = id;
    e2->type = type;
    e2->flag = 1;
    if (n2 > 4) {
        n2 = 4;
    }
    for (i = 0; i < n2; i++) {
        e2->v[i] = VariantGetFloat_15f740(args++);
    }
    D_0049D430[0]++;
    return 1;
}
