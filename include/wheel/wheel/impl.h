// clang-format off
#include "wheel/containers/optional/impl.h"
#include "wheel/containers/rc/impl.h"

#ifdef LIBWHEEL_TRAIT_COMPARE
#include "wheel/containers/bst/impl.h"
#endif // LIBWHEEL_TRAIT_COMPARE

#include "wheel/containers/vec/impl.h"

#ifdef LIBWHEEL_TRAIT_HASHABLE
#include "wheel/containers/eht/impl.h"
#endif // LIBWHEEL_TRAIT_HASHABLE

#include "wheel/containers/stack/impl.h"
#include "wheel/containers/trie/impl.h"
#include "wheel/containers/linked_list/impl.h"
// clang-format on
