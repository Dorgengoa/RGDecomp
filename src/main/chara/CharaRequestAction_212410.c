#include "types.h"

struct T212410 { u8 pad000[0xA68]; char fA68[0x20]; f32 fA88; };

extern char *strcpy(char *d, const char *s);

void CharaRequestAction_212410(struct T212410 *p, const char *s, f32 x)
{
    p->fA68[0] = 0;
    p->fA88 = 1.0f;
    if (s == 0) return;
    strcpy(p->fA68, s);
    p->fA88 = x;
}
