//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/set.h>
#include <pool/Pool.h>
#include <gfx/Types.h>
#include <gfx/Prefab.h>
#include <gfx/Gfx.h>
#include <gfx/Assets.h>
#include <gfx/Importer.h>
#include <gfx/GfxSystem.h>
#endif

namespace mud
{
#ifdef MUD_PREFABNODE
	PrefabNode::PrefabNode()
	{}

	void PrefabNode::draw(Gnode& parent)
	{
		Gnode& self = gfx::node(parent, m_object);
		Gnode& item = gfx::node(self, Ref(this), m_transform.m_position, m_transform.m_rotation, m_transform.m_scale);

		if(m_call.m_callable)
			m_call.m_arguments[0] = Ref(&item);
		if(m_call.validate())
			m_call();
		//else
		//	printf("WARNING: invalid prefab node element arguments\n");

		for(PrefabNode& node : m_nodes)
			node.draw(self);
	}
#endif

	Prefab::Prefab(const string& name)
		: m_name(name)
	{}

	Prefab& import_prefab(GfxSystem& gfx_system, ModelFormat format, const string& name, const ImportConfig& config)
	{
		LocatedFile location = gfx_system.locate_file("models/" + name, { format == ModelFormat::obj ? ".obj" : ".gltf" });
		Prefab& prefab = gfx_system.prefabs().create(name);
		gfx_system.importer(format)->import_prefab(prefab, location.path(false), config);
		return prefab;
	}

	void destroy_prefab(GfxSystem& gfx_system, Prefab& prefab)
	{
		set<Model*> models;
		for(Item& item : prefab.m_items)
			models.insert(item.m_model);

		for(Model* model : models)
		{
			for(ModelItem& model_item : model->m_items)
			{
				gfx_system.meshes().destroy(Ref(model_item.m_mesh));
			}

			gfx_system.models().destroy(model->m_name);
		}
	}
}
