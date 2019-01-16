#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-gltf;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/refl/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gltf/Module.h>
#include <meta/gfx-gltf/Module.h>
#endif

#include <gfx-gltf/Api.h>

#ifndef MUD_MODULES
#include <meta/gfx-gltf/Convert.h>
#endif
#define MUD_GFX_GLTF_REFLECTION_IMPL
#include <meta/gfx-gltf/Meta.h>

namespace mud
{
	mud_gfx_gltf::mud_gfx_gltf()
		: Module("mud::gfx-gltf", { &mud_infra::m(), &mud_type::m(), &mud_refl::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m(), &mud_gfx::m(), &mud_gltf::m() })
	{
		// setup reflection meta data
		mud_gfx_gltf_meta(*this);
	}
}

#ifdef MUD_GFX_GLTF_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx_gltf::m();
}
#endif
