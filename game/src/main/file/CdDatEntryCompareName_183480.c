/* rgp:protos */
#define RGP_SELF_CdDatEntryCompareName_183480 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct K00183480 {
    __extension__ unsigned int idx : 18;
    unsigned int rest : 14;
} __attribute__((aligned(4))) K00183480;

extern u8 *D_004811C8;
/*rgp*/

void CdDatEntryCompareName_183480(K00183480 *a, K00183480 *b)
{
    StrCmpU8_1834b0(D_004811C8 + a->idx, D_004811C8 + b->idx);
}
