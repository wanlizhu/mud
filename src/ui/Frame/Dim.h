//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>

#ifndef MUD_CPP_20
#include <cstddef>
#endif

#if defined _WIN32
#undef OPAQUE
#endif

namespace mud
{
	export_ enum refl_ Dim : unsigned int
	{
		DIM_X = 0,
		DIM_Y = 1,
		DIM_NONE = 2
	};

	inline Dim flip_dim(Dim dim) { return dim == DIM_X ? DIM_Y : DIM_X; }

	export_ enum refl_ FlowAxis : unsigned int
	{
		READING = 0,
		PARAGRAPH = 1,
		PARALLEL = 2,
		ORTHOGONAL = 3,
		AXIS_NONE = 4,
	};

	export_ enum refl_ Pivot : unsigned int
	{
		FORWARD = 0,
		REVERSE = 1
	};

	export_ enum refl_ Align : unsigned int
	{
		Left = 0,
		CENTER = 1,
		Right = 2,
		OUT_LEFT = 3,
		OUT_RIGHT = 4
	};

	extern float AlignExtent[5];
	extern float AlignSpace[5];

	export_ enum refl_ LayoutSolver : unsigned int
	{
		FRAME_SOLVER = 0,
		ROW_SOLVER = 1,
		GRID_SOLVER = 2,
		TABLE_SOLVER = 3,
	};

	export_ enum refl_ AutoLayout : unsigned int
	{
		NO_LAYOUT = 0,
		AUTO_SIZE = 1,
		AUTO_LAYOUT = 2
	};

	export_ enum refl_ Flow : unsigned int
	{
		FLOW = 0,			// AUTO_LAYOUT
		OVERLAY = 1,		// AUTO_SIZE
		ALIGN = 2,			// AUTO_POSITION
		FREE = 3			// NO_LAYOUT
	};

	export_ enum refl_ Sizing : unsigned int
	{
		FIXED,
		SHRINK,
		WRAP,
		EXPAND
	};

	export_ enum refl_ SpacePreset : unsigned int
	{
		SHEET,               // PARAGRAPH   direction, WRAP   length, WRAP   depth
		FLEX,			     // PARALLEL    direction, WRAP   length, WRAP   depth
		ITEM,                // READING     direction, SHRINK length, SHRINK depth
		UNIT,                // PARAGRAPH   direction, SHRINK length, SHRINK depth
		BLOCK,               // PARAGRAPH   direction, FIXED  length, FIXED  depth
		LINE,	             // READING     direction, WRAP   length, SHRINK depth
		STACK,               // PARAGRAPH   direction, SHRINK length, WRAP   depth 
		DIV,	             // ORTHOGONAL  direction, WRAP   length, SHRINK depth
		SPACER,              // PARALLEL    direction, WRAP   length, SHRINK depth
		BOARD,               // READING     direction, EXPAND length, EXPAND depth
		LAYOUT               // PARAGRAPH   direction, EXPAND length, EXPAND depth
	};

	export_ struct refl_ MUD_UI_EXPORT Space
	{
		attr_ FlowAxis direction;
		attr_ Sizing sizingLength;
		attr_ Sizing sizingDepth;

		Space(FlowAxis dir, Sizing length, Sizing depth) : direction(dir), sizingLength(length), sizingDepth(depth) {}
		Space(SpacePreset preset = FLEX) { *this = Space::preset(preset); }

		bool operator==(const Space& other) const { return direction == other.direction && sizingLength == other.sizingLength && sizingDepth == other.sizingDepth; }

		static Space preset(SpacePreset preset);
	};

	extern Space SpacePresets[11];

	export_ enum refl_ Clipping : unsigned int
	{
		NOCLIP = 0,
		CLIP = 1,
		UNCLIP = 2
	};

	export_ enum refl_ Opacity : unsigned int
	{
		OPAQUE = 0,
		CLEAR = 1,
		HOLLOW = 2
	};
	
	export_ template <class T>
	struct refl_ struct_ Dim2
	{
	public:
		constr_ Dim2(T a, T b) : d_values{ a, b } {}
		constr_ Dim2() : Dim2(T(), T()) {}

		T operator[](size_t i) const { return d_values[i]; }
		T& operator[](size_t i) { return d_values[i]; }

	public:
		union {
			T d_values[2];
			struct { attr_ T x; attr_ T y; };
			struct { T w; T h; };
		};
	};

	export_ extern template struct refl_ array_ struct_ Dim2<bool>;
	export_ extern template struct refl_ array_ struct_ Dim2<size_t>;
	export_ extern template struct refl_ array_ struct_ Dim2<AutoLayout>;
	export_ extern template struct refl_ array_ struct_ Dim2<Sizing>;
	export_ extern template struct refl_ array_ struct_ Dim2<Align>;
	export_ extern template struct refl_ array_ struct_ Dim2<Pivot>;
}
