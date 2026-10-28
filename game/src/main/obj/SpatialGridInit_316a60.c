/* rgp:protos */
#define RGP_SELF_SpatialGridInit_316a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct T316a60 {
    s32 f00;
    char name[0x5C];
    f32 f60;
    f32 f64;
    f32 f68;
    f32 f6C;
    f32 f70;
    f32 f74;
    f32 f78;
    f32 f7C;
    s32 f80;
    s32 f84;
    s32 f88;
    f32 f8C;
    s32 *f90;
} T316a60;

extern char D_00462368[];

/*rgp*/
/*rgp*/
extern u32 strlen(const char *);
extern char *strcpy(char *, const char *);
/*rgp*/

void SpatialGridInit_316a60(T316a60 *self, void *b, void *c, u128 *src)
{
    s32 i;
    f32 dx;
    f32 dy;

    MemStackClear_14dff0(self->name);
    MemStackInit_14d810(self->name, b, c);
    if (strlen(D_00462368) < 0x10) {
        strcpy(self->name, D_00462368);
    }
    *(u128 *)&self->f60 = src[0];
    *(u128 *)&self->f70 = src[1];
    self->f8C = 300.0f;
    dx = self->f60 - self->f70;
    dy = self->f68 - self->f78;
    self->f84 = (s32)(1.0f + dx / self->f8C);
    self->f88 = (s32)(1.0f + dy / self->f8C);
    self->f80 = self->f84 * self->f88;
    self->f90 = ((s32 *)MemStackNew_14e1b0(self->f80 * 4, self->name));
    for (i = 0; i < self->f80; i++) {
        self->f90[i] = 0;
    }
}
