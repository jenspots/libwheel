#ifndef LIBWHEEL_MACROS_H
#define LIBWHEEL_MACROS_H

#define LIBWHEEL_CONCAT_(x, y) x##_##y
#define LIBWHEEL_CONCAT(x, y)  LIBWHEEL_CONCAT_(x, y)

#define LIBWHEEL_PREPEND(x)  LIBWHEEL_CONCAT(LIBWHEEL_ALIAS, x)
#define LIBWHEEL_APPEND(x)  LIBWHEEL_CONCAT(x, LIBWHEEL_ALIAS)
#define LIBWHEEL_DEFINE(ns, x)  LIBWHEEL_CONCAT(ns, x)

#endif
