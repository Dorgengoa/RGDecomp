#pragma cplusplus on
typedef unsigned int U;
struct S { U flags, size; char *data; };
struct I { char *p; I(char *q):p(q){} };
extern "C" void StringReplace_106f90(S *, U, U, const char *, U, char);
extern "C" I StringEraseRange_107960(S *s, I first, I last) {
 struct C { char c; char pad[3]; C() {} }; C dummy;
 int count = (int)last.p-(int)first.p;
 char *base;
 if (s->flags & 1) base=s->data; else base=(char *)s+1;
 StringReplace_106f90(s,first.p-base,count,0,0,dummy.c);
 return I(first.p);
}
