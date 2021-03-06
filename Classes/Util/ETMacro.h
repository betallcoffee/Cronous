/*
 Author : betallcoffee
 */

#ifndef __ET_MACRO_H__
#define __ET_MACRO_H__

#ifdef WIN32
#include <assert.h>
#endif

#ifdef WIN32
#define ASSERT(cond)    assert(cond)
#define ASSERT_BREAK(cond)  if (!cond) { assert(cond); break; }
#else
#define ASSERT(cond)
#define ASSERT_BREAK(cond) if (!cond) { break; }
#define SOCKET_ERROR (-1)
#endif

#define BREAK_IF(cond) if (cond) break

typedef void (*ET_CallFuncN_t)(void *);
#define callFuncN_point(POINT_) (ET_CallFuncN_t)(&POINT_)

#endif //__ET_MACRO_H__
