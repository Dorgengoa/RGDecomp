#include "types.h"

extern void *MemStackAllocQw_14d950(void *b, s32 e);
extern void *ResGroupGetStack_42c720(void *a, void *c);
extern void MemStackClear_14dff0(void *q);
extern u32 strlen(const char *s);   /* unsigned: retail's sltiu */
extern char *strcpy(char *d, const char *s);
extern void MemStackInit_14d810(void *q, void *r, s32 e);

s32 ResGroupStackInit_42c600(void *a, void *b, void *c, char *d, s32 e)
{
    void *r;
    void *q;

    r = 0;
    if (b != 0 && e > 0) {
        r = MemStackAllocQw_14d950(b, e);
        if (r == 0) {
            return 0;
        }
    }
    q = ResGroupGetStack_42c720(a, c);
    MemStackClear_14dff0(q);
    if (d != 0 && strlen(d) < 0x10) {
        strcpy(q, d);
    }
    if (r != 0 && e > 0) {
        MemStackInit_14d810(q, r, e);
    }
    return 1;
}
