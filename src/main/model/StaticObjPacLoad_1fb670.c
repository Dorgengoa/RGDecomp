#include "types.h"

typedef struct {
    void *dst;
    void *aux;
    s32 heap;
    s32 id;
    u8 flag;
} LoadDesc;

typedef struct {
    f32 x, y, z, w;
} Scale4;

void FrameSetScale_14a2c0(void *, Scale4 *);
void MemStackAlign64_14d8e0(s32);
void *MemStackAllocQw_14d950(s32, s32);
void MemStackReturnToOwnerMaybe_14dad0(s32);
void *MemStackHeapAlloc_14db10(s32, s32, s32, s32);
void MemStackHeapFree_14dcb0(s32, void *);
void ModelSetScale_150ff0(void *, Scale4 *);
void NameTableRegisterImArchive_1594d0(s32, void *, s32, s32, s32);
s32 GetDrawCtxNameTable_15de40(void);
void *ArchiveGetFileByPath_1c2800(void *, char *, s32 *);
s32 ResidentFileReadLocalizedMaybe_1c2860(char *, void *, s32 *);
void Character2NewFromInfoCfgWithColl_1fd8f0(LoadDesc *, void *, s32, char *);
s32 GetReadBuffHeap_2025e0(void);
s32 GetSystemMemStack_202600(void);
void ActCfgLoadText_23b1d0(void *, s32, s32);
void ScriptStrTableReset_2ccc30(void);
void CompassHudLoad_371670(void *, void *, s32, s32, s32);
void *memcpy(void *, const void *, u32);
extern char D_0045BD60[];
extern char D_0045BD78[];
extern char D_0045BD90[];
extern char D_0045BDA0[];
extern char D_0045BDB8[];
extern char D_0045BDC8[];
extern char D_0045BDE0[];
extern char D_0045BDF8[];
extern char D_0045BE08[];
extern char D_0045BE18[];
extern char D_0045BE28[];
extern char D_0045BE38[];
extern char D_0045BE48[];
extern void *D_00481A54;
extern void *D_00481A58;
extern void *D_00481A5C;
extern void *D_00481A60;
extern void *D_00481A64;
extern void *D_00481A68;
extern void *D_00481A6C;
extern void *D_00481A70;
extern void *D_00481A74;
extern u8 D_004B8800[];

static inline void ldEntry(void *arc, s32 cnt, char *name, LoadDesc *d, char *x) {
    s32 sz;
    if (arc != 0 && cnt > 0) {
        void *p = ArchiveGetFileByPath_1c2800(arc, name, &sz);
        Character2NewFromInfoCfgWithColl_1fd8f0(d, p, sz, x);
    }
}

#define ZERO16(b) { u8 *p_ = (u8 *)(b); u32 n_ = 16; if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

void StaticObjPacLoad_1fb670(void) {
    s32 cnt;
    LoadDesc d;
    s32 sz;
    Scale4 s1;
    Scale4 s2;
    Scale4 s3;
    s32 heap;
    s32 h2;
    void *arc;
    s32 mdl;

    heap = GetSystemMemStack_202600();
    h2 = GetReadBuffHeap_2025e0();
    arc = MemStackHeapAlloc_14db10(h2, 2, 0, 0x40);
    if (arc != 0) {
        MemStackAlign64_14d8e0(h2);
        mdl = GetDrawCtxNameTable_15de40();
        if (ResidentFileReadLocalizedMaybe_1c2860(D_0045BD60, arc, &cnt) != 0) {
            d.dst = &D_00481A54;
            d.aux = 0;
            d.heap = heap;
            d.id = 0x283;
            d.flag = 1;
            ldEntry(arc, cnt, D_0045BD78, &d, 0);
            d.dst = &D_00481A58;
            d.aux = 0;
            d.heap = heap;
            d.id = 0x284;
            d.flag = 0;
            ldEntry(arc, cnt, D_0045BD90, &d, 0);
            d.dst = &D_00481A5C;
            d.aux = 0;
            d.heap = heap;
            d.id = 0x283;
            d.flag = 0;
            ldEntry(arc, cnt, D_0045BDA0, &d, 0);
            d.dst = &D_00481A60;
            d.aux = 0;
            d.heap = heap;
            d.id = 0x282;
            d.flag = 0;
            ldEntry(arc, cnt, D_0045BDB8, &d, 0);
            d.dst = &D_00481A64;
            d.aux = &D_00481A68;
            d.heap = heap;
            d.id = 0x285;
            d.flag = 0;
            ldEntry(arc, cnt, D_0045BDC8, &d, D_0045BDE0);
            {
                void *m = D_00481A68;
                if (m != 0) {
                    ZERO16(&s1);
                    s1.x = 1.0f;
                    s1.y = 1.0f;
                    s1.z = 1.0f;
                    FrameSetScale_14a2c0(m, &s1);
                }
            }
            d.dst = &D_00481A6C;
            d.aux = &D_00481A70;
            d.heap = heap;
            d.id = 0x287;
            d.flag = 0;
            ldEntry(arc, cnt, D_0045BDF8, &d, D_0045BE08);
            {
                void *m = D_00481A70;
                if (m != 0) {
                    ZERO16(&s2);
                    s2.x = 1.0f;
                    s2.y = 1.0f;
                    s2.z = 1.0f;
                    FrameSetScale_14a2c0(m, &s2);
                }
            }
            d.dst = &D_00481A74;
            d.aux = 0;
            d.heap = heap;
            d.id = 0x287;
            d.flag = 0;
            ldEntry(arc, cnt, D_0045BE18, &d, 0);
            {
                void *m = D_00481A74;
                if (m != 0) {
                    ZERO16(&s3);
                    s3.x = 1.0f;
                    s3.y = 1.0f;
                    s3.z = 1.0f;
                    ModelSetScale_150ff0(m, &s3);
                }
            }
            {
                void *p = ArchiveGetFileByPath_1c2800(arc, D_0045BE28, &sz);
                if (p != 0) {
                    CompassHudLoad_371670(D_004B8800, p, sz, heap, 0x286);
                }
            }
            {
                void *p;
                if ((p = ArchiveGetFileByPath_1c2800(arc, D_0045BE38, &sz)) != 0) {
                    void *buf = MemStackAllocQw_14d950(heap, sz / 16 + 1);
                    memcpy(buf, p, sz);
                    NameTableRegisterImArchive_1594d0(mdl, buf, 0x2A5, heap, 0);
                    MemStackAlign64_14d8e0(heap);
                }
            }
            {
                void *p = ArchiveGetFileByPath_1c2800(arc, D_0045BE48, &sz);
                if (p != 0) {
                    ActCfgLoadText_23b1d0(p, sz, 0x7FFF);
                }
            }
        }
        MemStackReturnToOwnerMaybe_14dad0(h2);
        MemStackHeapFree_14dcb0(h2, arc);
    }
    ScriptStrTableReset_2ccc30();
}
