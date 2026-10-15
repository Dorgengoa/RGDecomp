#pragma opt_propagation off
#include "types.h"

struct Handle {
    s32 id;
};

static inline bool valid(s32 id)
{
    return id != 0;
}

static inline bool isNull(s32 id)
{
    return !(id != 0);
}

typedef struct Inner {
    char name[8];
    s32 a;
    s32 b;
    char *p;
    s32 c;
} Inner;

typedef struct Thing {
    u8 pad0[0x40];
    void *vt;
    s32 m44;
    s32 m48;
    s32 m4C;
    u8 m50;
    u8 m51;
    u8 m52;
    s32 m54;
    s32 m58;
    s32 m5C;
    s32 m60;
    s32 m64;
    s32 m68;
    s32 m6C;
    s32 m70;
    s32 m74;
    s32 m78;
    s32 m7C;
    s32 m80;
    s32 m84;
    s32 m88;
    s32 m8C;
    s32 m90;
    s32 m94;
    s32 m98;
} Thing;

typedef struct Outer {
    void *o;
    s32 ctx;
    Inner in;
    s32 heap;
    Thing *obj;
    u8 pad[0x58 - 0x28];
} Outer;

typedef struct Obj { u8 pad[8]; s32 heap; u8 pad2[0xB0 - 0xC]; u8 mB0[4]; } Obj;

extern "C" {
extern char D_0044AA30[];
extern char D_0045A640[];
extern char D_0045A648[];
extern char D_0045A818[];
extern u8 D_00470998[];
char *strcpy(char *d, const char *s);
s32 strcmp(const char *a, const char *b);
void *memset(void *p, s32 c, u32 n);
void MemStackReturnToOwnerMaybe_14dad0(s32 heap);
s32 MemStackHeapAlloc_14db10(s32 heap, s32 a, s32 b, s32 c);
void MemStackHeapFree_14dcb0(s32 heap, s32 m);
void *MemStackNew_14e230(u32 size, s32 heap);
void TextReaderCtor_15f140(void *b);
void TextReaderOpen_15f1b0(void *b, s32 id, s32 v);
void TextReaderSetKeywords_15f230(void *b, char *s, Outer *o);
void TextReaderParseAll_15f3f0(void *b);
s32 ArchiveFindByExt_181be0(s32 ctx, char *s, s32 *out, s32 a, s32 *out2, s32 b);
s32 ArchiveGetFileData_181dd0(s32 ctx, char *s, s32 *out);
void EffHdlAddByName_1a39c0(Handle *out, void *list, s32 a, Thing **t);
void EffObjBaseCtor_1a9ed0(Thing *t);
}

extern "C" void EffDefLoad_19fc30(Handle *out, Obj *o, s32 ctx, Inner *d)
{
    volatile Handle h;
    s32 id;
    s32 id2;
    volatile Handle res;
    Handle tmp;
    u8 big[0xEDC];
    Outer ou;
    s32 id3;
    s32 m;
    s32 heap;
    Thing *t;

    h.id = 0;
    heap = o->heap;
    if (heap == 0) {
        s32 z = 0;
        out->id = z;
        return;
    }
    TextReaderCtor_15f140(big);
    ou.in.a = 0;
    ou.in.b = 0;
    ou.in.c = 0;
    strcpy(ou.in.name, D_0045A818);
    ou.in.p = ou.in.name;
    memset(&ou, 0, sizeof(ou));
    ou.o = o;
    ou.ctx = ctx;
    ou.in = *d;
    id3 = 0;
    if (d->p == 0) {
        out->id = h.id;
        return;
    }
    if (strcmp(d->p, D_0045A640) == 0) {
        if (ArchiveFindByExt_181be0(ctx, D_0045A648, &id2, 1, &id, 0) > 0) {
            id3 = id2;
        }
    } else {
        id3 = ArchiveGetFileData_181dd0(ctx, d->p, &id);
    }
    if (id3 == 0) {
        out->id = h.id;
        return;
    }
    m = MemStackHeapAlloc_14db10(heap, 2, 0, 0x40);
    if (m == 0) {
        out->id = h.id;
        return;
    }
    res.id = 0;
    t = (Thing *)MemStackNew_14e230(0xA4, heap);
    if (t != 0) {
        EffObjBaseCtor_1a9ed0(t);
        t->vt = D_00470998;
        t->m44 = 0;
        t->m64 = 0;
        t->m60 = 0;
        t->m6C = 0;
        t->m68 = 0;
        t->m74 = 0;
        t->m70 = 0;
        t->m80 = 0;
        t->m7C = 0;
        t->m88 = 0;
        t->m84 = 0;
        t->m90 = 0;
        t->m8C = 0;
        t->m94 = 0;
        t->m98 = 0;
        t->m48 = 0;
        t->m54 = 0;
        t->m58 = 0;
        t->m5C = 0;
        t->m4C = -1;
        t->m78 = 0;
        t->m50 = 0;
        t->m51 = 0;
        t->m52 = 0;
    }
    ou.obj = t;
    if (t != 0) {
        ou.heap = heap;
        if (d->c != 0) {
            ou.heap = d->c;
        }
        ou.obj->m48 = m;
        TextReaderSetKeywords_15f230(big, D_0044AA30, &ou);
        TextReaderOpen_15f1b0(big, id3, id);
        TextReaderParseAll_15f3f0(big);
        EffHdlAddByName_1a39c0(&tmp, o->mB0, d->a, &ou.obj);
        res.id = tmp.id;
        ou.obj->m44 = tmp.id;
        ou.obj->m4C = ou.in.b;
    }
    MemStackReturnToOwnerMaybe_14dad0(heap);
    if (ou.obj == 0) {
        MemStackHeapFree_14dcb0(heap, m);
    }
    if (isNull(res.id)) {
        MemStackHeapFree_14dcb0(heap, m);
    }
    out->id = res.id;
}
