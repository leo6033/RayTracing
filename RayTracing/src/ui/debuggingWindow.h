// generated by Fast Light User Interface Designer (fluid) version 1.0010

#ifndef debuggingWindow_h
#define debuggingWindow_h
#include "Fl.H"
#include "Fl_Window.H"
#include "Fl_Menu_Bar.H"
#include "debuggingView.h"

namespace disc0ver {
	class DebuggingWindow {
	public:
		DebuggingWindow();
		Fl_Window* m_debuggingWindow;
		Fl_Menu_Bar* m_debuggingMenuBar;
		static Fl_Menu_Item menu_m_debuggingMenuBar[];
	private:
		inline void cb_Normal_i(Fl_Menu_*, void*);
		static void cb_Normal(Fl_Menu_*, void*);
		inline void cb_Flat_i(Fl_Menu_*, void*);
		static void cb_Flat(Fl_Menu_*, void*);
		inline void cb_Wireframe_i(Fl_Menu_*, void*);
		static void cb_Wireframe(Fl_Menu_*, void*);
		inline void cb_High_i(Fl_Menu_*, void*);
		static void cb_High(Fl_Menu_*, void*);
		inline void cb_Medium_i(Fl_Menu_*, void*);
		static void cb_Medium(Fl_Menu_*, void*);
		inline void cb_Low_i(Fl_Menu_*, void*);
		static void cb_Low(Fl_Menu_*, void*);
		inline void cb_Poor_i(Fl_Menu_*, void*);
		static void cb_Poor(Fl_Menu_*, void*);
		inline void cb_Default_i(Fl_Menu_*, void*);
		static void cb_Default(Fl_Menu_*, void*);
		inline void cb_Scene_i(Fl_Menu_*, void*);
		static void cb_Scene(Fl_Menu_*, void*);
		inline void cb_Use_i(Fl_Menu_*, void*);
		static void cb_Use(Fl_Menu_*, void*);
		inline void cb_Geometry_i(Fl_Menu_*, void*);
		static void cb_Geometry(Fl_Menu_*, void*);
		inline void cb_Lights_i(Fl_Menu_*, void*);
		static void cb_Lights(Fl_Menu_*, void*);
		inline void cb_Camera_i(Fl_Menu_*, void*);
		static void cb_Camera(Fl_Menu_*, void*);
		inline void cb_Axes_i(Fl_Menu_*, void*);
		static void cb_Axes(Fl_Menu_*, void*);
		inline void cb_Normals_i(Fl_Menu_*, void*);
		static void cb_Normals(Fl_Menu_*, void*);
		inline void cb_Visibility_i(Fl_Menu_*, void*);
		static void cb_Visibility(Fl_Menu_*, void*);
		inline void cb_Reflection_i(Fl_Menu_*, void*);
		static void cb_Reflection(Fl_Menu_*, void*);
		inline void cb_Refraction_i(Fl_Menu_*, void*);
		static void cb_Refraction(Fl_Menu_*, void*);
		inline void cb_Shadow_i(Fl_Menu_*, void*);
		static void cb_Shadow(Fl_Menu_*, void*);
	public:
		DebuggingView* m_debuggingView;
		void show();
		void hide();
		void redraw();
	};
}

#endif
