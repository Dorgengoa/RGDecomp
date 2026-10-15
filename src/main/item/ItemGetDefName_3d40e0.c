#include "types.h"

struct A3D40E0 { u8 pad000[0xC]; const char *f0C; };
struct T3D40E0 { u8 pad000[0x10]; struct A3D40E0 *f10; };

extern char *strcpy(char *d, const char *s);

char *ItemGetDefName_3d40e0(struct T3D40E0 *p, char *dst)
{
    struct A3D40E0 *a;

    if (dst == 0) return 0;
    a = p->f10;
    if (a == 0) return 0;
    strcpy(dst, a->f0C);
    return dst;
}
