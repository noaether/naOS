#ifndef STDDEF_H
#define STDDEF_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

  typedef __SIZE_TYPE__ size_t;
  typedef __PTRDIFF_TYPE__ ptrdiff_t;

#ifndef offsetof
#define offsetof(type, member) ((size_t) & (((type *)0)->member))
#endif

#ifdef __cplusplus
}
#endif

#endif /* STDDEF_H */
