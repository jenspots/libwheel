#ifndef LIBWHEEL_MACROS_H
#define LIBWHEEL_MACROS_H

#define CONCAT(x, y)  x##y
#define CONCAT_(x, y) CONCAT(x, y)
#define PREFIX(X)     CONCAT_(X, CONCAT_(_, LIBWHEEL_ALIAS))

#endif
