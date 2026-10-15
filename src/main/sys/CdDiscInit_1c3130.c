#include "types.h"

typedef struct Elem {
    u8 flag;
    u8 pad1[0x1F];
} Elem;

typedef struct S {
    Elem items[2];
    s32 counts[2];
    u8 pad48[0x50 - 0x48];
} S;

extern void CdDataSetNamesInit_1c31a0(S *);
extern void CdDatArchivesInit_182e70(S *);
extern s32 D_0048155C;
extern s32 D_00481560;

void CdDiscInit_1c3130(void)
{
    S sp10;
    s32 i;

    D_00481560 = 0;
    i = 0;
    do {
        sp10.items[i].flag = 0;
        sp10.counts[i] = 0;
        i += 1;
    } while (i < 2);
    CdDataSetNamesInit_1c31a0(&sp10);
    CdDatArchivesInit_182e70(&sp10);
    if (D_0048155C != 2) {
        D_0048155C = D_00481560;
    }
}
