//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <infra/Reverse.h>
#include <ui/Style/Style.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>
#include <ui/UiWindow.h>
#include <ui/Widget.h>
#include <ui/Input.h>
#endif

namespace mud
{
	struct StyleSelector
	{
		template <class T_Decl>
		StyleSelector& declare(T_Decl decl);

		template <class T_Decl>
		StyleSelector& decline(const vector<uint32_t>& states, T_Decl decl);

		vector<Style*> styles;
	};

	template <class T_Decl>
	StyleSelector& StyleSelector::declare(T_Decl decl)
	{
		for(Style* style : styles)
			decl(style->layout(), style->skin());
		return *this;
	}

	template <class T_Decl>
	StyleSelector& StyleSelector::decline(const vector<uint32_t>& states, T_Decl decl)
	{
		for(Style* style : styles)
			for(uint32_t state : states)
			{
				decl(style->decline_skin(WidgetState(state)));
			}
		return *this;
	}

	StyleSelector select(const vector<string> styles)
	{
		StyleSelector selector;
		for(const string& name : styles)
			if(UiWindow::s_styles.find(name) != UiWindow::s_styles.end())
				selector.styles.push_back(UiWindow::s_styles[name]);
			else
				printf("WARNING: style %s not found\n", name.c_str());
		return selector;
	}

	void layout_minimal(UiWindow& ui_window)
	{
		UNUSED(ui_window);

		select({ "Label", "Title", "Message", "Tooltip", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(4.f);
		});

		select({ "Title" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(8.f);
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(4.f);
		});

		select({ "Item", "DropdownToggle", "ExpandboxToggle", "TreeNodeToggle", "TreeNodeNoToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(4.f);
		});

		select({ "TabHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(6.f);
		});

		select({ "Tooltip", "ToolButton", "ExpandboxBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(4.f);
		});

		select({ "Dockspace", "Toolbar", "Header", "Popup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(6.f);
		});

		select({ "Modal" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(12.f);
		});

		select({ "ExpandboxBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(ivec4(32, 6, 8, 6));
		});

		select({ "ExpandboxBody", "WindowBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(4.f);
		});

		select({ "Dockbar", "Toolbar", "Menubar", "Header" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(6.f);
		});
		
		select({ "NodePlugs" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(ivec4(-5, 0, -5, 0));
		});
	}

	void style_minimal(UiWindow& ui_window)
	{
		layout_minimal(ui_window);

		Colour white = { 1.f };
		Colour black = { 0.f };
		Colour transparent = { 0.f, 0.f };
		Colour clearGreyText = { 0.627f };
		Colour grey600 = { 0.600f };
		Colour grey400 = { 0.400f };
		Colour grey312 = { 0.312f };
		Colour grey248 = { 0.248f };
		Colour grey204 = { 0.204f };
		Colour grey176 = { 0.176f };
		Colour grey145 = { 0.145f };
		Colour grey117 = { 0.117f };
		Colour grey86  = { 0.086f };
		Colour grey69  = { 0.069f };
		Colour grey52  = { 0.052f };
		Colour activeBlue = { 0.145f, 0.5f, 1.f, 1.f };

		select({ "Label", "Title", "Message", "Tooltip", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_text_colour = grey248;
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i = styles().label.skin();
			i.m_background_colour = grey204;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey312;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		});

		select({ "CloseButton", "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i = styles().button.skin();
		});

		select({ "Element", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey86;
		});

		select({ "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_align = { CENTER, CENTER };
		});

		select({ "SliderKnob", "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i = styles().button.skin();
			i.m_background_colour = grey176;
		});

		select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey312;
			l.m_size = vec2(8, 22);
		});

		select({ "ScrollUp", "ScrollDown" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(10, 0);
		});

		select({ "ScrollLeft", "ScrollRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(0, 10);
		});

		/*select({ "ExpandboxToggle", "TreeNodeToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("toggle_closed");
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("toggle_open");
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("empty_15");
		});*/

		select({ "DropdownToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("drop_down");
		});

		select({  "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_size = vec2(15.f);
			i.m_padding = vec4(1.f);
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("check_15");
		});

		select({ "Slider", "Fillbar", "TypeIn", "Input<string>"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey145;
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1.f);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey204;
			i.m_border_colour = grey400;
			i.m_border_width = vec4(1.f);
		})
		.decline({ FOCUSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
		});

		select({ "Filler" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey248;
		});

		select({ "List", "Tree", "TabberHead", "TableHead", "Dockbar", "Header", "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey117;
		});

		select({ "Window", "WindowFooter", "DockWindow", "Dockbox", "Tab", "TextEdit", "Node", "Section", "Popup", "Modal", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey52;
			i.m_border_colour = grey204;
			i.m_border_width = vec4(1.f);
		});

		select({ "Window", "Dockbox", "Node" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_shadow = { 2, 2, 7, 2 };
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_shadow = { 0, 0, 0, 1, grey600 };
		});

		select({ "WindowHeader", "WindowHeaderMovable", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey204;
		});

		select({  "WindowSizer", "WindowSizerLeft", "WindowSizerRight"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("handle_x");
			i.m_padding = vec4(2.f);
		});

		select({ "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_align = { Right, Right };
		});

		select({  "Toolbar", "Tooldock"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey145;
		});

		select({ "Canvas" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});

		select({  "Tooltip", "Popdown", "DropdownList", "MenuList", "SubMenuList"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = { 0.098f, 0.802f };
			i.m_text_colour = clearGreyText;
		});

		select({ "DropdownChoice" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = transparent;
		});

		select({ "TableRow", "TableRowOdd", "TableRowEven"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l); UNUSED(i);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1.f);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
			i.m_border_width = vec4(1.f);
		});

		select({ "TableRowOdd" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey117;
		});

		select({ "TableRowEven" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});

		for(auto name_style : UiWindow::s_styles)
			name_style.second->prepare();
	}
}
