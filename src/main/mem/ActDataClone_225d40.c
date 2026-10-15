#include "types.h"

typedef struct {
    u8 b[12];
} E12;

typedef struct {
    u8 b[8];
} E8;

typedef struct {
    u64 d0;
    u64 d8;
    s32 id;
    E12 *p14;
    E12 *p18;
    E8 *p1C;
    s16 h20;
    s16 h22;
    s16 h24;
    s16 h26;
} Data;

extern void *ConstructNewArray_100710(void *, void *, s32, s32, s32);
extern void *MemStackNew_14e1b0(s32, s32);
extern u64 ActDataCnctGetCmndMask_2274c0(E8 *);
extern s32 ActDataCnctClone_2274f0(E8 *, E8 *, s32, s32);
extern s32 VariantArrayClone_3027d0(E12 *, E12 *, s32, s32);

s32 ActDataClone_225d40(Data *dst, s32 id, Data *src, s32 heap, s32 arg4)
{
    s32 n;
    s32 i;
    E8 *p;
    u64 x;

    dst->id = 0;
    dst->h26 = 0;
    dst->d0 = 0;
    dst->d8 = 0;
    dst->p14 = 0;
    dst->h20 = 0;
    dst->p18 = 0;
    dst->h22 = 0;
    dst->p1C = 0;
    dst->h24 = 0;
    if (heap == 0 || id == 0 || src == NULL) {
        return 0;
    }
    {
        {
            if (src->p14 != NULL) {
                n = src->h20;
                if (n > 0) {
                    if ((dst->p14 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 12 + 0x10, heap), 0, 0, 12, n)) == NULL) {
                        return 0;
                    }
                    dst->h20 = src->h20;
                }
            }
            if (src->p18 != NULL) {
                n = src->h22;
                if (n > 0) {
                    if ((dst->p18 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 12 + 0x10, heap), 0, 0, 12, n)) == NULL) {
                        return 0;
                    }
                    dst->h22 = src->h22;
                }
            }
            if (src->p1C != NULL) {
                n = src->h24;
                if (n > 0) {
                    if ((dst->p1C = MemStackNew_14e1b0(n * 8, heap)) == NULL) {
                        return 0;
                    }
                    dst->h24 = src->h24;
                }
            }
            for (i = 0; i < dst->h20; i++) {
                if (VariantArrayClone_3027d0(&dst->p14[i], &src->p14[i], heap, arg4) == 0) {
                    return 0;
                }
            }
            for (i = 0; i < dst->h22; i++) {
                if (VariantArrayClone_3027d0(&dst->p18[i], &src->p18[i], heap, arg4) == 0) {
                    return 0;
                }
            }
            for (i = 0; i < dst->h24; i++) {
                if (ActDataCnctClone_2274f0(&dst->p1C[i], &src->p1C[i], heap, arg4) == 0) {
                    return 0;
                }
            }
            dst->id = id;
            dst->h26 = src->h26;
            dst->d0 = src->d0;
            dst->d8 = src->d8;
            p = dst->p1C;
            if (p != NULL) {
                for (i = 0; i < dst->h24; i++, p++) {
                    dst->d8 |= ActDataCnctGetCmndMask_2274c0(p);
                }
            }
            return 1;
        }
    }
    return 0;
}
