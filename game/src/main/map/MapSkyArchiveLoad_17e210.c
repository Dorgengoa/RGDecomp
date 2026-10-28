/* rgp:protos */
#define RGP_SELF_MapSkyArchiveLoad_17e210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct Desc {
    s32 f0;
    char names[4][0x20];    /* 0x004 */
    char names2[4][0x20];   /* 0x084 */
    f32 f104[4];            /* 0x104 */
    char names3[4][0x20];   /* 0x114 */
    char names4[4][0x20];   /* 0x194 */
    f32 f214[4];            /* 0x214 */
    char name5[0x20];       /* 0x224 */
    f32 f244;               /* 0x244 */
    s32 idx248[16];         /* 0x248 */
    char str288[16][0x20];  /* 0x288 */
    f32 f488[16];           /* 0x488 */
    s32 idx4C8[16];         /* 0x4C8 */
    char str508[16][0x20];  /* 0x508 */
    f32 f708[16];           /* 0x708 */
} Desc;

typedef struct Grp {
    u8 d[0x1C0];
} Grp;

typedef struct Blk {
    u128 q[5];
} Blk;

typedef struct Pair {
    s32 p;
    f32 v;
} Pair;

typedef struct Self {
    s32 f0;
    u8 pad4[0xC];
    Grp grpA[4];            /* 0x010 */
    u8 pad710[0x10];
    f32 f720[4];            /* 0x720 */
    Grp grpB[4];            /* 0x730 */
    u8 padE30[0x10];
    f32 fE40[4];            /* 0xE40 */
    Grp grpC[4];            /* 0xE50 */
    s32 f1550[4];           /* 0x1550 */
    s32 f1560;              /* 0x1560 */
    u8 pad1564[0x11C];
    Blk blk;                /* 0x1680 */
    u8 pad16D0[0x50];
    s32 f1720;              /* 0x1720 */
    f32 f1724;              /* 0x1724 */
    Pair pairs[16];         /* 0x1728 */
} Self;

typedef struct Lst {
    s32 a;
    s32 b;
} Lst;

typedef struct Ent {
    u8 pad[0x4D];
    s8 f4D;
    s8 f4E;
    u8 pad4F[2];
    s8 f51;
} Ent;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void *memcpy(void *, const void *, u32);
void *memset(void *, s32, u32);
extern char D_004596D8[];

#pragma opt_propagation off
void MapSkyArchiveLoad_17e210(Self *self, s32 arc, volatile s32 base, s32 heap) {
    u32 size0;
    u32 size;
    Lst l860 __attribute__((aligned(16)));
    Lst l858 __attribute__((aligned(16)));
    Lst l850 __attribute__((aligned(16)));
    Lst l848 __attribute__((aligned(16)));
    Desc d __attribute__((aligned(16)));
    Blk buf __attribute__((aligned(16)));
    s32 w2;
    void *p;
    s32 w;
    s32 i;
    s32 j;
    s32 n;
    s32 n_3;
    void *mem;
    void *data;
    void *a;
    void *b;
    void *c;
    Ent *e;
    Grp *g;
    s32 r;
    char *q;

    if (arc == 0) {
        return;
    }
    MapSkyResetModels_17f8a0((void *)self);
    size0 = 0;
    p = ArchiveGetFileData_181dd0(arc, D_004596D8, &size0);
    memset(&d, 0, 0x748);
    SkyCfgParse_17e190(&d, p, size0);
    if (d.f0 != 0) {
        self->f0 = 0;
    }
    if (!(d.f244 <= 0.0f)) {
        self->f1724 = d.f244;
    }
    w = GetDrawCtx_15de80();
    w2 = GetDrawCtxNameTable_15de40();
    i = 0;
    do {
        NameTableFreeGroup_158ac0(w2, base + i);
        { s32 k_ = i; char *q0 = (char *)&d + k_ * 0x20; data = ArchiveGetFileData_181dd0(arc, q0 + 4, &size); }
        mem = MemStackAllocQw_14d950(heap, (size & 0xF) ? (size >> 4) + 1 : size >> 4);
        memcpy(mem, data, size);
        q = (char *)&d + i * 0x20;
        a = ArchiveGetFileData_181dd0(arc, q + 0x84, 0);
        b = ArchiveGetFileData_181dd0(arc, q + 0x194, 0);
        c = ArchiveGetFileData_181dd0(arc, q + 0x114, 0);
        self->f720[i] = d.f104[i];
        self->fE40[i] = d.f214[i];
        if (mem != 0) {
            { s32 bi = base + i;
            self->f1550[i] = bi;
            NameTableRegisterImArchive_1594d0(w2, mem, bi, heap, 0); }
        }
        if (a != 0) {
            l860.a = 0;
            ModelResRelocate_14bfd0(&l860, a);
            n = ModelResGetMaterialCount_14c640(&l860);
            for (j = 0; j < n; j++) {
                e = ((Ent *)ArrayGetChecked_14c5e0(&l860, j));
                if (e == 0) {
                    break;
                }
                e->f51 = 1;
                e->f4D = 5;
                e->f4E = 1;
            }
            ModelBuildFrames_1506c0(&self->grpA[i], &l860, w, heap);
        }
        if (b != 0) {
            l858.a = 0;
            ModelResRelocate_14bfd0(&l858, b);
            n = ModelResGetMaterialCount_14c640(&l858);
            for (j = 0; j < n; j++) {
                e = ((Ent *)ArrayGetChecked_14c5e0(&l858, j));
                if (e == 0) {
                    break;
                }
                e->f51 = 1;
                e->f4D = 5;
                e->f4E = 1;
            }
            ModelBuildFrames_1506c0(&self->grpB[i], &l858, w, heap);
        }
        if (c != 0) {
            l850.a = 0;
            ModelResRelocate_14bfd0(&l850, c);
            n = ModelResGetMaterialCount_14c640(&l850);
            for (j = 0; j < n; j++) {
                e = ((Ent *)ArrayGetChecked_14c5e0(&l850, j));
                if (e == 0) {
                    break;
                }
                e->f51 = 1;
                e->f4D = 5;
                e->f4E = 1;
            }
            ModelBuildFrames_1506c0(&self->grpC[i], &l850, w, heap);
        }
        i++;
    } while (i < 4);
    p = ArchiveGetFileData_181dd0(arc, d.name5, 0);
    if (p != 0) {
        l848.a = 0;
        ModelResRelocate_14bfd0(&l848, p);
        ModelBuildFrames_1506c0((Grp *)&self->f1560, &l848, w, heap);
        if (self->f1560 != 0) {
            buf = self->blk;
            self->f1720 = ArrayGetCheckedIndirect_1527e0(&buf, 0);
        }
    }
    n_3 = 0;
    i = 0;
    do {
        if (d.str288[i][0] != 0 && n_3 < 16) {
            g = &self->grpA[d.idx248[i]];
            if (g != 0) {
                r = ModelGetRootFrame_1511a0(g);
                if (r != 0) {
                    r = ((s32)FrameFindByName_149ed0(r, d.str288[i]));
                }
                if (r != 0) {
                    self->pairs[n_3].p = r;
                    self->pairs[n_3].v = d.f488[i];
                    n_3++;
                }
            }
        }
        i++;
    } while (i < 16);
    i = 0;
    do {
        if (d.str508[i][0] != 0 && n_3 < 16) {
            g = &self->grpB[d.idx4C8[i]];
            if (g != 0) {
                r = ModelGetRootFrame_1511a0(g);
                if (r != 0) {
                    r = ((s32)FrameFindByName_149ed0(r, d.str508[i]));
                }
                if (r != 0) {
                    self->pairs[n_3].p = r;
                    self->pairs[n_3].v = d.f708[i];
                    n_3++;
                }
            }
        }
        i++;
    } while (i < 16);
}
