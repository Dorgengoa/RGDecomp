#include "types.h"

typedef struct Blk {
    s32 w[8];
} Blk;

typedef struct Cfg {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    s32 x30;
    s32 x34;
    s32 x38;
    s32 x3C;
    Blk x40;
    Blk x60;
    s32 x80;
    s32 x84;
} Cfg;

typedef struct G {
    Cfg c;
    s32 x88;
    s32 x8C;
    s32 x90;
    s32 x94;
    s32 x98;
    s32 x9C;
    s32 xA0;
    s32 xA4;
    s32 xA8;
} G;

void TextReaderCtor_15f140(void *);
void TextReaderOpen_15f1b0(void *, s32, s32);
void BuildKeywordHashTable_15f270(void *, void *);
void TextReaderParseAll_15f3f0(void *);
s32 ArchiveGetFileData_181dd0(s32, s32, s32 *);
extern u8 D_0044AD40[0x400];
extern G D_0049D390;

void InfoCfgParseModels_1abfe0(s32 arg0, Cfg *arg1) {
    u8 sp40[0xEDC];
    s32 spF1C;
    s32 r;

    if (arg0 == 0) {
        return;
    }
    TextReaderCtor_15f140(sp40);
    D_0049D390.c.x0 = arg1->x0;
    D_0049D390.c.x4 = arg1->x4;
    D_0049D390.c.x8 = arg1->x8;
    D_0049D390.c.xC = arg1->xC;
    D_0049D390.c.x10 = arg1->x10;
    D_0049D390.c.x14 = arg1->x14;
    D_0049D390.c.x18 = arg1->x18;
    D_0049D390.c.x1C = arg1->x1C;
    D_0049D390.c.x20 = arg1->x20;
    D_0049D390.c.x24 = arg1->x24;
    D_0049D390.c.x28 = arg1->x28;
    D_0049D390.c.x2C = arg1->x2C;
    D_0049D390.c.x30 = arg1->x30;
    D_0049D390.c.x34 = arg1->x34;
    D_0049D390.c.x38 = arg1->x38;
    D_0049D390.c.x3C = arg1->x3C;
    D_0049D390.c.x40 = arg1->x40;
    D_0049D390.c.x60 = arg1->x60;
    D_0049D390.c.x80 = arg1->x80;
    D_0049D390.c.x84 = arg1->x84;
    D_0049D390.x88 = arg0;
    D_0049D390.x90 = 0;
    D_0049D390.x9C = 0;
    D_0049D390.xA8 = arg1->x24;
    r = ArchiveGetFileData_181dd0(arg1->x0, arg1->x4, &spF1C);
    if (r != 0) {
        BuildKeywordHashTable_15f270(sp40, D_0044AD40);
        TextReaderOpen_15f1b0(sp40, r, spF1C);
        TextReaderParseAll_15f3f0(sp40);
        arg1->x28 = D_0049D390.c.x28;
        arg1->x34 = D_0049D390.c.x34;
    }
}
