#ifndef LIBWHEEL_TYPE
#error "LIBWHEEL_TYPE is not defined."
#endif

#ifndef LIBWHEEL_ALIAS
#error "LIBWHEEL_ALIAS is not defined."
#endif

/*
 * Step 1: include all the preprocessor definitions for source code expansion.
 */
#include <wheel/wheel/def.h>

/*
 * Step 2: include the actual implementations.
 */
#include <wheel/wheel/impl.h>

/*
 * Step 3: Remove all preprocessor definitions. We do so to prevent leakage
 * into both subsequent usages and the source code of the user themselves.
 */
#include <wheel/wheel/undef.h>

/*
 * We undefine any traits which may be used in order to prevent unintended
 * side effects for any subsequent usages.
 */
#undef LIBWHEEL_TRAIT_COMPARE
#undef LIBWHEEL_TRAIT_DESTROY
#undef LIBWHEEL_TRAIT_HASHABLE
#undef LIBWHEEL_TRAIT_SHALLOW_COPY
#undef LIBWHEEL_TRAIT_DEEP_COPY
#undef LIBWHEEL_TRAIT_STRINGIFY
#undef LIBWHEEL_TRAIT_SERIALIZE_JSON

/*
 * Remove the type and alias definitions. End users should not be able to
 * use these definitions in their own code.
 */
#undef LIBWHEEL_TYPE
#undef LIBWHEEL_ALIAS
