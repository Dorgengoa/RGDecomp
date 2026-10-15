#include "types.h"
typedef struct K00183480 {
    u32 idx : 18;
    u32 rest : 14;
} K00183480;

extern u8 *D_004811C8;
extern void StrCmpU8_1834b0(void *a, void *b);

void CdDatEntryCompareName_183480(K00183480 *a, K00183480 *b)
{
    StrCmpU8_1834b0(D_004811C8 + a->idx, D_004811C8 + b->idx);
}
