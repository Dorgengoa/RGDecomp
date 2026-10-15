/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/InfoCfgParse_1ac1e0.s and build/b_drafts/InfoCfgParse_1ac1e0.txt
   (m2c draft already generated, just not worked). */
/* s49m: MATCH */
#include "types.h"

typedef struct {
    s32 w[8];
} Blk;

typedef struct {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    Blk b40;
    Blk b60;
    s32 f80;
    s32 f84;
} Desc;

typedef struct {
    Desc d;
    u8 *owner;
    s32 f8C;
    s32 f90;
    u8 pad94[8];
    s32 f9C;
    u8 padA0[0xC];
    s32 fAC;
} G;

extern G D_0049D390;
extern char D_0044AC80[];
extern void TextReaderCtor_15f140(u8 *);
extern void BuildKeywordHashTable_15f270(u8 *, char *);
extern void TextReaderOpen_15f1b0(u8 *, u8 *, s32);
extern void TextReaderParseAll_15f3f0(u8 *);
extern u8 *ArchiveGetFileData_181dd0(s32, s32, s32 *);

void InfoCfgParse_1ac1e0(u8 *self, Desc *d)
{
    u8 ctx[0xEDC];
    s32 sz;
    s32 avail;
    u8 *p;

    avail = *(s32 *)(*(u8 **)&d->f08 + 0x34) - *(s32 *)(*(u8 **)&d->f08 + 0x2C);
    TextReaderCtor_15f140(ctx);
    D_0049D390.d.f00 = d->f00;
    D_0049D390.d.f04 = d->f04;
    D_0049D390.d.f08 = d->f08;
    D_0049D390.d.f0C = d->f0C;
    D_0049D390.d.f10 = d->f10;
    D_0049D390.d.f14 = d->f14;
    D_0049D390.d.f18 = d->f18;
    D_0049D390.d.f1C = d->f1C;
    D_0049D390.d.f20 = d->f20;
    D_0049D390.d.f24 = d->f24;
    D_0049D390.d.f28 = d->f28;
    D_0049D390.d.f2C = d->f2C;
    D_0049D390.d.f30 = d->f30;
    D_0049D390.d.f34 = d->f34;
    D_0049D390.d.f38 = d->f38;
    D_0049D390.d.f3C = d->f3C;
    D_0049D390.d.b40 = d->b40;
    D_0049D390.d.b60 = d->b60;
    D_0049D390.d.f80 = d->f80;
    D_0049D390.d.f84 = d->f84;
    D_0049D390.owner = self;
    D_0049D390.f90 = 0;
    D_0049D390.f8C = 0;
    D_0049D390.f9C = 0;
    D_0049D390.fAC = 0;
    if (d->f1C != 0) {
        *(s32 *)(self + 0x474) = d->f1C;
        D_0049D390.f9C = d->f1C;
    }
    p = ArchiveGetFileData_181dd0(d->f00, d->f04, &sz);
    if (p == 0) {
        return;
    }
    BuildKeywordHashTable_15f270(ctx, D_0044AC80);
    TextReaderOpen_15f1b0(ctx, p, sz);
    TextReaderParseAll_15f3f0(ctx);
    *(s32 *)(self + 0x4D4) = avail - (*(s32 *)(*(u8 **)&d->f08 + 0x34) - *(s32 *)(*(u8 **)&d->f08 + 0x2C));
    d->f28 = D_0049D390.d.f28;
    d->f34 = D_0049D390.d.f34;
}
