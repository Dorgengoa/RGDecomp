#include "types.h"

extern s32 SoundSeqUpdate_1b5540(void *arg0, f32 arg1);
extern void SoundMasterVolumeFadeUpdate_1bb4d0(void);
extern u8 D_0049EB10[];
extern u8 D_004A0910[];

static inline u8 *getA(s32 i) {
    if (i < 0 || 0x11 <= i) return NULL;
    return D_0049EB10 + i * 0x1E0;
}

static inline u8 *getB(s32 i) {
    if (i < 0 || i >= 0x20) return NULL;
    return D_004A0910 + i * 0x90;
}

void SoundSeqPlayersUpdateAll_1bb110(f32 fparg0)
{
    s32 i;
    u8 *a;
    s32 j;
    s16 *e;
    u8 *b;

    i = 0;
    do {
        if (i < 0 || i > 0x10) {
            a = NULL;
        } else {
            a = D_0049EB10 + i * 0x1E0;
        }
        if (a != NULL) {
            j = 0;
            do {
                e = (s16 *)(a + j * 8 + 0x160);
                if (*e >= 0) {
                    b = getB(*e);
                    if (b != NULL && SoundSeqUpdate_1b5540(b, fparg0) != 0) {
                        *e = -1;
                    }
                }
                j++;
            } while (j < 0x10);
        }
        i++;
    } while (i < 0x10);
    SoundMasterVolumeFadeUpdate_1bb4d0();
}
