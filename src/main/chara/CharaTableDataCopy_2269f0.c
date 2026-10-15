#include "types.h"

typedef struct { u8 b[8]; } E8;
typedef struct { u8 b[16]; } E16;
typedef struct { u8 b[32]; } E32;
typedef struct { u8 b[20]; } E20;

typedef struct {
    void *x0;
    E8 *p4;
    E16 *p8;
    E32 *pC;
    E16 *p10;
    E20 *p14;
    E16 *p18;
    E20 *p1C;
    E20 *p20;
    s16 n24;
    s16 n26;
    s16 n28;
    s16 n2A;
    s16 n2C;
    s16 n2E;
    s16 n30;
    s16 n32;
} MdlData;

void *ConstructNewArray_100710(void *, s32, s32, s32, s32);
void *MemStackNew_14e1b0(s32, s32);
void CharaTableDataClear_227090(MdlData *);
s32 ActTimeCnctClone_227370(E20 *, E20 *, s32, s32);
s32 ActTimePrmtClone_227590(E20 *, E20 *, s32, s32);
s32 ActTimeAttrClone_227680(E16 *, E16 *, s32, s32);
s32 ActTimeMoveClone_2278d0(E20 *, E20 *, s32, s32);
s32 ActTimeAcclClone_227a10(E16 *, E16 *, s32, s32);
s32 ActTimeClsnClone_227ad0(E32 *, E32 *, s32, s32);
s32 ActTimeEvntClone_228260(E16 *, E16 *, s32, s32);
s32 ActReferenceClone_2285a0(E8 *, E8 *, s32, s32);
void *StrPoolIntern_302fd0(s32, void *, s32);

#define DUP(P, N, T) \
    if (src->P != 0) { \
        n = src->N; \
        if (n > 0) { \
            if ((dst->P = ConstructNewArray_100710(MemStackNew_14e1b0(n * sizeof(T) + 0x10, heap), 0, 0, sizeof(T), n)) == 0) { \
                return 0; \
            } \
            dst->N = src->N; \
        } \
    }

#define COPY(P, N, F) \
    for (i = 0; i < dst->N; i++) { \
        if (F(&dst->P[i], &src->P[i], heap, ctx) == 0) { \
            return 0; \
        } \
    }

s32 CharaTableDataCopy_2269f0(MdlData *dst, MdlData *src, s32 heap, s32 ctx) {
    s32 n;
    s32 i;

    CharaTableDataClear_227090(dst);
    if (heap == 0 || ctx == 0 || src == 0 || src->x0 == 0) {
        return 0;
    }
    if (src->p4 != 0) {
        if (src->n24 > 0) {
            if ((dst->p4 = MemStackNew_14e1b0(src->n24 * 8, heap)) == 0) {
                return 0;
            }
            dst->n24 = src->n24;
        }
    }
    DUP(p8, n26, E16)
    DUP(pC, n28, E32)
    DUP(p10, n2A, E16)
    DUP(p14, n2C, E20)
    DUP(p18, n2E, E16)
    DUP(p1C, n30, E20)
    DUP(p20, n32, E20)
    COPY(p4, n24, ActReferenceClone_2285a0)
    COPY(p8, n26, ActTimeEvntClone_228260)
    COPY(pC, n28, ActTimeClsnClone_227ad0)
    COPY(p10, n2A, ActTimeAcclClone_227a10)
    COPY(p14, n2C, ActTimeMoveClone_2278d0)
    COPY(p18, n2E, ActTimeAttrClone_227680)
    COPY(p1C, n30, ActTimePrmtClone_227590)
    COPY(p20, n32, ActTimeCnctClone_227370)
    dst->x0 = StrPoolIntern_302fd0(ctx, src->x0, heap);
    return 1;
}
