#pragma cplusplus on
typedef unsigned int U;
struct S { U flags, size; char *data; };
union V { float f[3]; unsigned int u[3]; };
extern "C" void StringReserve_107e80(S *, U);
extern "C" void StringReplace_106f90(S *, U, U, const char *, const char *, char);
extern "C" S *StringCopyCtor_107c30(S *s, const S *other) {
 struct C { char c; char pad[3]; C() {} }; C dummy;
 if (!(other->flags&1)) *(V *)s=*(const V *)other;
 else {
 s->flags=0; s->size=0; s->data=0;
 StringReserve_107e80(s,other->size);
 StringReplace_106f90(s,0,0,other->data,other->data+other->size,dummy.c);
 }
 return s;
}
