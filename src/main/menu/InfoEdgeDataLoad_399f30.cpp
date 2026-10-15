#pragma optimization_level 3
#include "types.h"

struct Rec {
    s16 h0;
    s16 h1;
    s16 h2;
    s16 h3;
    s16 h4;
    s8 name[0x40];
};

extern "C" {
extern s32 D_004835A4;
extern  s32 D_004835A8;
extern Rec * D_004835AC;
extern u8 D_00454540[];
void TextReaderCtor_15f140(void *);
void BuildKeywordHashTable_15f270(void *, void *);
void TextReaderOpen_15f1b0(void *, s32, s32);
void TextReaderParseAll_15f3f0(void *);
}

extern "C" void InfoEdgeDataLoad_399f30(s32 a0, s32 a1)
{
    u8 ctx[0xED0];
    s32 i;
    s32 j;

    D_004835A4 = 0;
    D_004835AC = 0;
    TextReaderCtor_15f140(ctx);
    BuildKeywordHashTable_15f270(ctx, D_00454540);
    TextReaderOpen_15f1b0(ctx, a0, a1);
    TextReaderParseAll_15f3f0(ctx);
    for (i = 0; i < D_004835A8 - 1; i++) {
        for (j = i + 1; j < D_004835A8; j++) {
            if (D_004835AC[i].h1 > D_004835AC[j].h1) {
                Rec tmp = D_004835AC[i];
                D_004835AC[i] = D_004835AC[j];
                D_004835AC[j] = tmp;
            }
        }
    }

}
