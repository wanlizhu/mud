#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/vector.h>
#include <stl/map.h>
#include <type/Type.h>
#include <gfx/Importer.h>
#endif
#include <gfx-obj/Forward.h>

namespace mud
{
	using MaterialMap = map<string, Material*>;

	export_ class MUD_GFX_OBJ_EXPORT ImporterOBJ : public Importer
	{
	public:
		ImporterOBJ(GfxSystem& gfx_system);

		GfxSystem& m_gfx_system;

		virtual void import(Import& import, const string& filepath, const ImportConfig& config) override;
		virtual void import_model(Model& model, const string& filepath, const ImportConfig& config) override;
		virtual void import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config) override;
		virtual void repack(const string& filepath, const ImportConfig& config) override;
	};
}
