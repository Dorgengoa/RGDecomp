/* SPDX-License-Identifier: CC0-1.0 */
/* Reference (pre-rewrite) VU float helpers, tests only: vu_float_ref.c. */
#ifndef RG_VU_FLOAT_REF_H
#define RG_VU_FLOAT_REF_H
#include <stdint.h>
double ref_f_to_d(uint32_t a);
uint32_t ref_f_from_d(double v, unsigned *cond);
uint32_t ref_f_add(uint32_t a, uint32_t b, unsigned *cond);
uint32_t ref_f_sub(uint32_t a, uint32_t b, unsigned *cond);
uint32_t ref_f_mul(uint32_t a, uint32_t b, unsigned *cond);
uint32_t ref_ftoi(uint32_t a, int frac_bits);
uint32_t ref_itof(uint32_t a, int frac_bits);
int ref_f_cmp(uint32_t a, uint32_t b);
uint32_t ref_clip(const uint32_t fs[4], uint32_t ftw);
uint32_t ref_efu(int op, const uint32_t s[4], int fsf);
uint32_t ref_fdiv(int op, uint32_t a, uint32_t b, uint32_t *fl);
#endif
