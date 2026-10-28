/* rgp:protos */
#define RGP_SELF_CharaDataNodeFromLoadInfo_1ef7b0 1
#define RGP_SELF_Find 1
#define RGP_SELF_Find2 1
#define RGP_SELF_Lookup 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0xC];
    s32 wC;
    s32 w10;
    s32 w14;
    char *w18;
    s32 w1C;
    u8 pad20[4];
    s32 w24;
    s32 w28;
    s32 w2C;
    s32 w30;
    s32 w34;
} Src;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s32 wC;
    s32 w10;
    u8 pad14[0xA];
    s8 b1E;
    u8 pad1F;
    s32 w20;
    s32 w24;
    s16 h28;
    s16 h2A;
    u8 pad2C[8];
    s16 h34;
    u8 pad36[2];
    s32 w38;
} Dst;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(const char *, const char *);

static inline s32 Find(u8 *base, char *name)
{
    s32 i;
    for (i = 0; i < 16; i++) {
        if (strcmp(name, (char *)(base + (i << 8))) == 0) {
            return i;
        }
    }
    return -1;
}

static inline s32 Find2(char *name, u8 *base)
{
    s32 i;
    for (i = 0; i < 16; i++) {
        if (strcmp(name, (char *)(base + (i << 8))) == 0) {
            return i;
        }
    }
    return -1;
}

static inline s32 Lookup(u8 *base, s32 i)
{
    if (i < 0 || i >= 16) {
        return -1;
    }
    return ((s32 *)(base + 0x1000))[i];
}

s32 CharaDataNodeFromLoadInfo_1ef7b0(Dst *arg0, Src *arg1)
{
    s32 ctx;
    s32 v;
    u8 *base;
    char *name;
    s32 i;

    ctx = ((s32)GetLoaderMgr_1f59d0());
    arg0->h8 = arg1->wC;
    arg0->hA = arg1->w10;
    arg0->w10 = arg1->w1C;
    arg0->w24 = arg1->w14;
    arg0->h28 = arg1->w24;
    arg0->h2A = arg1->w28;
    arg0->h34 = arg1->w2C;
    arg0->w38 = arg1->w34;
    switch (arg0->h8) {
    case 5:
        arg0->w20 = -1;
        break;
    case 0:
        arg0->w20 = 0;
        break;
    case 4:
        arg0->w20 = 0;
        break;
    }
    v = arg1->w30;
    if (v < 0) {
        base = ((u8 *)GetFileNameSlotTable_1ed0c0());
        if (base != NULL) {
            name = arg1->w18;
            i = Find(base, name);
            arg0->wC = Lookup(base, i);
        }
        if (arg0->wC < 0) {
            arg0->wC = LoaderRequestFile_1cd870(ctx, arg1->w18, 0);
        }
    } else {
        arg0->wC = v;
    }
    if (arg0->wC < 0) {
        arg0->b1E = CharaDataNodeFailStatus_1ef9a0(arg0->h8);
        return 0;
    }
    arg0->b1E = 1;
    return 1;
}
