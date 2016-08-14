#ifndef WHC_GRAPHICALOBJ_H
#define WHC_GRAPHICALOBJ_H

#include <allegro.h>
#include <winalleg.h>
#include <OpenLayer.hpp>

//rien à voir mais en attendant mieux
	#include <MidiShare.h>
	using namespace ol;
	#include <audiere.h>
	//#include <whc_mouse.h>
	//#include "whitecat.h"

class whc_graphicalObj
{
	public:
		/** Default constructor */
		whc_graphicalObj();
		/** Default destructor */
		virtual ~whc_graphicalObj();

		bool isVisible() { return m_IsVisible; }
		void isVisible(bool val) { m_IsVisible = val; }

		int  onScreenPos_x(){return m_OnScreenPos_x;};
		void onScreenPos_x(int val){m_OnScreenPos_x=val;};

		int  onScreenPos_y(){return m_OnScreenPos_y;};
		void onScreenPos_y(int val){m_OnScreenPos_y=val;};

		void Draw();

	protected:
		bool m_IsVisible; //!< Member variable "m_IsVisible" - la fenêtre est visible
		int  m_OnScreenPos_x;
		int  m_OnScreenPos_y;
		int  m_size_x;
		int  m_size_y;
	private:


};

#endif // WHC_GRAPHICALOBJ_H
