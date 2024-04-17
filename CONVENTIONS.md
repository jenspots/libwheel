# Conventions

## API

Many functions implement the same functionality, but for different data structures. For example, initialization is
typically done using the `init` function. To assure consistency and clarity across the API, we define a set of
conventions that should be followed. We take the complete function signature into account, including the return type and
the parameters.

The conventions below will use the `type` datatype as a placeholder and omit the function prefix.

### Traits

Some functionality is optional and can be enabled by defining a trait. Some require the implementation of specific
functions.

| Trait                           | Description                             | Required functions     |
|---------------------------------|-----------------------------------------|------------------------|
| `LIBWHEEL_TRAIT_SHALLOW_COPY`   | Shallow copies an instance              | `trait_shallow_copy`   |
| `LIBWHEEL_TRAIT_DEEP_COPY`      | Deep copies an instance                 | `trait_deep_copy`      |
| `LIBWHEEL_TRAIT_EQUAL`          | Compares two instances by equality      | `trait_equal`          |
| `LIBWHEEL_TRAIT_COMPARE`        | Compares two instances by order         | `trait_compare`        |
| `LIBWHEEL_TRAIT_HASH`           | Calculate the hash value of an instance | `trait_hash`           |
| `LIBWHEEL_TRAIT_STRINGIFY`      | Convert an instance to a `char*`        | `trait_stringify`      |
| `LIBWHEEL_TRAIT_SERIALIZE_JSON` | Serialize an instance to JSON           | `trait_serialize_json` |

### Constructors, destructors

The preferred way to create instances is the stack.

| Function signature    | Description                                                                                           |
|-----------------------|-------------------------------------------------------------------------------------------------------|
| `type init()`         | Initialize an empty instance on the stack                                                             |
| `void destroy(type*)` | Remove an empty data structure on the stack, i.e. without calling `free` on the data structure itself |

However, allocating data on the heap is supported.

| Function signature         | Description                                                                           |
|----------------------------|---------------------------------------------------------------------------------------|
| `type* init_ptr()`         | Initialize an empty instance on the heap                                              | 
| `void destroy_ptr(type**)` | Remove an empty data structure on the heap and set the accompanying pointer to `NULL` |

### Retrieving elements

#### Position based

| Function signature     | Description                                                                           | Required traits               |
|------------------------|---------------------------------------------------------------------------------------|-------------------------------|
| `optional head(type*)` | Retrieve the first element of the container. Returns `optional_empty` if it is empty. | `LIBWHEEL_TRAIT_SHALLOW_COPY` | 
| `T* head_ptr(type*)`   | Retrieve the first element of the container. Returns `NULL` if it is empty.           | None                          |
| `optional last(type*)` | Retrieve the last element of the container. Returns `optional_empty` if it is empty.  | `LIBWHEEL_TRAIT_SHALLOW_COPY` |   
| `T* last_ptr(type*)`   | Retrieve the last element of the container. Returns `NULL` if it is empty.            | None                          |             

#### Index based

| Function signature                    | Description                                                                                                     | Required traits               |
|---------------------------------------|-----------------------------------------------------------------------------------------------------------------|-------------------------------|
| `optional get(type*, uint64_t index)` | Copies an element based on index. Returns `optional_empty` when not present or when the index is out-of-bounds. | `LIBWHEEL_TRAIT_SHALLOW_COPY` |
| `T* get_ptr(type*, uint64_t index)`   | Retrieve an element based on index, and returns `NULL` if not present or the index is out-of-bounds             | None                          |

### Serialization

#### JSON

| Function signature                            | Description                                                                                                             | Required traits                 |
|-----------------------------------------------|-------------------------------------------------------------------------------------------------------------------------|---------------------------------|
| `uint64t serialize_json(type*, char* target)` | Serialize an instance to JSON and write into the target string. If the target is `NULL`, the required size is returned. | `LIBWHEEL_TRAIT_SERIALIZE_JSON` |

### Algorithms

| Function signature                     | Description                                                                                                                                                                                                  | Required traits               |
|----------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------|
| `optional binary_search(type*, T key)` | Search for a key in a container. Returns `optional_empty` if not found. If the container does not inherently sort it's elements, the operation may return a false negative if not preceded by a `sort` call. | `LIBWHEEL_TRAIT_COMPARE`      |
| `void sort(type*)`                     | Sort the elements of a container in-place.                                                                                                                                                                   | `LIBWHEEL_TRAIT_COMPARE`      |

### Iterators

In Wheel, iterators are simple structs that represent the state of an iteration. The functionality itself is fully implemented by containers themselves. For example, the iterator of a vector only requires a pointer to a vector, the current index, and it's direction.

```c
typedef struct {
  vector* vec;
  uint64_t index;
  bool forward;
} vec_iter;
```

| Function signature     | Description                                                                                          | Required traits               |
|------------------------|------------------------------------------------------------------------------------------------------|-------------------------------|
| `iter begin(type*)`    | TODO                                                                                                 | None                          |
| `iter rbegin(type*)`   | TODO                                                                                                 | None                          |
| `iter end(type*)`      | TODO                                                                                                 | None                          | 
| `iter rend(type*)`     | TODO                                                                                                 | None                          |
| `optional iget(iter*)` | TODO                                                                                                 | `LIBWHEEL_TRAIT_SHALLOW_COPY` |   
| `T* iget_ptr(iter*)`   | TODO                                                                                                 | None                          |
| `bool next(iter*)`     | Advance the iterator to the next element. The returned boolean indicates whether an element remains. | None                          |
