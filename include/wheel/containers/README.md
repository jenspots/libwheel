## About

The following data structures are implemented. Note that some require the use of traits to function properly. Not all data structures are stable, and may contain bugs or unexpected behaviour.

| Data Structure        | Abbreviation | Required Traits          | Status   |
|-----------------------|--------------|--------------------------|----------|
| Binary Search Tree    | `bst`        | `LIBWHEEL_TRAIT_COMPARE` | Unstable |
| Extendable Hash Table | `eht`        | `LIBWHEEL_TRAIT_HASH`    | Unstable |
| Linked List           | `ll`         | None                     | Unstable |
| Optional              | `optional`   | None                     | Stable   |
| Reference Counter     | `rc`         | None                     | Unstable |
| Stack                 | `stack`      | None                     | Unstable |
| Trie                  | `trie`       | None                     | Unstable |
| Vector                | `vec`        | None                     | Unstable |

### Structure

All container implementation follow the same file structure.

| File       | Description                                                                                   |
|------------|-----------------------------------------------------------------------------------------------|
| `def.h`    | Introduce the keywords into the global namespace.                                             |
| `header.h` | Header file for the specific data structure which may be included multiple times.             |
| `impl.h`   | Implementation of the data structure. This file may only be included once per `LIBWHEEL_TYPE` |
| `undef.h`  | Undefine the keywords introduced by `def.h`.                                                  |
