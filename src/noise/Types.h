#pragma once

#include <noise/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <cstdint>
#endif

#include <noise/Structs.h>

namespace mud
{
    // Exported types
    export_ template <> MUD_NOISE_EXPORT Type& type<mud::Noise::CellularDistanceFunction>();
    export_ template <> MUD_NOISE_EXPORT Type& type<mud::Noise::CellularReturnType>();
    export_ template <> MUD_NOISE_EXPORT Type& type<mud::Noise::FractalType>();
    export_ template <> MUD_NOISE_EXPORT Type& type<mud::Noise::Interp>();
    export_ template <> MUD_NOISE_EXPORT Type& type<mud::Noise::NoiseType>();
    
    export_ template <> MUD_NOISE_EXPORT Type& type<mud::Noise>();
    export_ template <> MUD_NOISE_EXPORT Type& type<mud::array3d<float>>();
    
    export_ template <> MUD_NOISE_EXPORT Type& type<vector<mud::Noise*>>();
    export_ template <> MUD_NOISE_EXPORT Type& type<vector<mud::array3d<float>*>>();
}
