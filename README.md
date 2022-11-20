# Wheel

This repository provides a "generic datastructures in C" proof-of-concept. Wheel heavily relies on the C preprocessor and resolves at compile time, allowing for generics with (near) zero overhead.

### Example

One of the provided datastructures is `optional`, which either contains a value or doesn't. The definition in `<wheel/optional.h>` is as followed.

```c
typedef struct optional {
    bool present;
    T value;
} optional;
```

Here, the type `T` is a generic. We can instantiate it to a string, in essence a `char*` in the C language. When your application uses Wheel, you may define the header file `optional_string.h` as shown below.

```c
#ifndef OPTIONAL_STRING_H
#define OPTIONAL_STRING_H

#define LIBWHEEL_TYPE  char*
#define LIBWHEEL_ALIAS string

#include <wheel/optional.h>

#undef LIBWHEEL_ALIAS
#undef LIBWHEEL_TYPE

#endif // OPTIONAL_STRING_H
```

If you are unfamiliar with the `#ifndef OPTIONAL_STRING_H` convention, this simply makes sure this specific header file isn't send to the compiler more than once. It is not in any way specific to Wheel itself. 

We define `LIBWHEEL_TYPE` which is what the preprocessor will fill in for every instance of `T` in `<wheel/optional.h>`. Here, we want it to be `char*`. 

The name of a struct cannot contain asterisks, so a type definition like `struct optional_char*` would be invalid. This means will also have to pass a second argument which will dictate the suffix given to every function and struct, since those still have to be unique. This is where `LIBWHEEL_ALIAS` comes in, here mapped to `string`. The resulting type will be `optional_string`.

Since you most likely will use these macros multiple times in your program, we remove their definition using `#undef` at the bottom of `optional_string.h`.

Now, `optional_string.h` will take the following form at compile time.

```c
#ifndef OPTIONAL_STRING_H
#define OPTIONAL_STRING_H

typedef struct optional_string {
    bool present;
    char* value;
} optional_string;


optional_string optional_empty_string() {
    optional_string result;
    result.present = false;
    return result;
}

// etc

#endif // OPTIONAL_STRING_H
```

Creating a generic datastructure and its procedures is now as simple as defining some macro's and including a header file! 
