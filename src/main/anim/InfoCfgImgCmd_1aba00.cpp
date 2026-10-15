#include "types.h"

typedef struct Node1aba00 {
    struct Node1aba00 *next;
    struct Node1aba00 *prev;
    s32 m8;
    s32 mC;
    void *m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    void *vt;
} Node1aba00;

class VN1aba00 {
public:
    u8 pad0[0x24];
    virtual void init();
};

typedef struct {
    u8 pad0[0x40];
    void *m40;
    s32 m44;
} Ent1aba00;

typedef struct {
    u8 pad0[0x220];
    Node1aba00 *m220;
} Mgr1aba00;

extern "C" {
void *memcpy(void *, const void *, u32);
s32 Strcasecmp_1345b8(Ent1aba00 *, s32);
void *MemStackAllocAligned64_14da10(s32, s32);
Node1aba00 *MemStackNew_14e230(s32, s32);
s32 TexAnimeTableLoadFromImg_159340(s32, void *, s32);
void NameTableRegisterImArchiveFwd_1594c0(s32, void *, s32, s32);
s32 GetDrawCtxNameTable_15de40(void);
s32 SlotGetInt_15f720(u8 *);
s32 VariantGetInt_15f780(void);
void *ArchiveGetFileData_181dd0(s32, s32, s32 *);
void ModelObjTexAnimBuildNameIndexMaybe_1abcd0(void *, s32, s32);
extern u8 D_00470F40[0x400];
extern u8 D_0049D390[0x400];
extern u8 D_0049D3A0[0x400];
extern u8 D_0049D3A4[0x400];
extern u8 D_0049D410[0x400];
extern u8 D_0049D414[0x400];
extern u8 D_0049D418[0x400];
}

static inline Node1aba00 *newNode1aba00(s32 heap)
{
    Node1aba00 *o = MemStackNew_14e230(0x28, heap);
    if (o != NULL) {
        o->vt = D_00470F40;
        o->m10 = 0;
        o->m14 = 0;
        o->m1C = 0;
        o->m20 = 0;
        o->m18 = 1;
        ((VN1aba00 *)o)->init();
    }
    return o;
}

static inline void *find1aba00(s32 id, s32 *psz)
{
    Ent1aba00 *e = *(Ent1aba00 **)D_0049D414;
    s32 i;

    if (e == NULL || *(s32 *)D_0049D410 == 0) {
        return NULL;
    }
    for (i = 0; i < *(s32 *)D_0049D410; i++, e++) {
        if (Strcasecmp_1345b8(e, id) == 0) {
            *psz = e->m44;
            return e->m40;
        }
    }
    return NULL;
}

extern "C" s32 InfoCfgImgCmd_1aba00(u8 *arg0)
{
    s32 sz;
    Mgr1aba00 *m;
    s32 heap;
    s32 x;
    s32 y;
    s32 t;
    s32 id;
    Ent1aba00 *e;
    s32 flag;
    void *data;
    s32 i;
    Node1aba00 *n;
    Node1aba00 *p;
    void **q;
    void *buf;
    s32 g;

    m = *(Mgr1aba00 **)D_0049D418;
    heap = *(s32 *)D_0049D3A0;
    x = *(s32 *)D_0049D3A4;
    y = *(s32 *)D_0049D390;
    if (heap == 0 || m == NULL) {
        return 0;
    }
    arg0 = (u8 *)((u32)arg0 + 8);
    t = VariantGetInt_15f780();
    id = SlotGetInt_15f720(arg0);
    sz = 0;
    flag = 0;
    data = find1aba00(id, &sz);
    if (data == NULL) {
        data = ArchiveGetFileData_181dd0(y, id, &sz);
        if (data == NULL) {
            return 0;
        }
        flag = 1;
    }
    n = newNode1aba00(heap);
    if (n == NULL) {
        q = 0;
    } else {
        n->m10 = 0;
        n->m14 = 0;
        n->m1C = 0;
        n->m20 = 0;
        n->m18 = 1;
        n->mC = t;
        q = &n->m10;
        if (m->m220 == NULL) {
            m->m220 = n;
        } else {
            p = m->m220;
            while (p != NULL) {
                if (p->next == NULL) {
                    break;
                }
                p = p->next;
            }
            p->next = n;
            if (n != NULL) {
                n->prev = p;
            }
        }
    }
    if (q == 0) {
        return 0;
    }
    if (flag != 0) {
        buf = MemStackAllocAligned64_14da10(heap, sz / 16 + 1);
        *q = buf;
        if (buf == NULL) {
            return 0;
        }
        memcpy(buf, data, sz);
    } else {
        *q = data;
    }
    g = GetDrawCtxNameTable_15de40();
    NameTableRegisterImArchiveFwd_1594c0(g, *q, x, 0);
    ((s32 *)q)[1] = TexAnimeTableLoadFromImg_159340(g, *q, heap);
    ModelObjTexAnimBuildNameIndexMaybe_1abcd0(q, x, heap);
    return 1;
}
