#include "types.h"

typedef struct A1_001afb30 {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x88 - 0x8];
    s32 unk88;
    s32 unk8C;
} A1_001afb30;

extern void TextReaderCtor_15f140(void *arg0);
extern void TextReaderOpen_15f1b0(void *arg0, s32 arg1, s32 arg2);
extern void BuildKeywordHashTable_15f270(void *arg0, void *arg1);
extern void TextReaderParseAll_15f3f0(void *arg0);
extern s32 ArchiveGetFileData_181dd0(s32 arg0, s32 arg1, s32 *arg2);
extern void ParamScriptReqCopy_1afc10(void *arg0, A1_001afb30 *arg1);
extern u8 D_0044AD70[];
extern u8 D_0049D450[];
extern s32 D_0049D4D8[];
extern s32 D_0049D4DC[];
extern s32 D_0049D4E0[];
extern s32 D_0049D4E4[];
extern s32 D_0049D4E8[];
extern s32 D_0049D4EC[];
extern s32 D_0049D4F8[];
extern s32 D_0049D4FC[];
extern s32 D_0049D500[];

void ParamScriptParse_1afb30(s32 arg0, A1_001afb30 *arg1)
{
    s32 spF0C;
    u8 sp30[0xEDC];
    s32 r;

    TextReaderCtor_15f140(sp30);
    ParamScriptReqCopy_1afc10(D_0049D450, arg1);
    D_0049D4D8[0] = arg1->unk88;
    D_0049D4DC[0] = arg1->unk8C;
    D_0049D4E0[0] = arg0;
    D_0049D4E4[0] = -1;
    D_0049D4E8[0] = 0;
    D_0049D4EC[0] = 0;
    D_0049D4F8[0] = 0;
    D_0049D4FC[0] = 0;
    D_0049D500[0] = 0;
    r = ArchiveGetFileData_181dd0(arg1->unk0, arg1->unk4, &spF0C);
    if (r != 0) {
        BuildKeywordHashTable_15f270(sp30, D_0044AD70);
        TextReaderOpen_15f1b0(sp30, r, spF0C);
        TextReaderParseAll_15f3f0(sp30);
    }
}
