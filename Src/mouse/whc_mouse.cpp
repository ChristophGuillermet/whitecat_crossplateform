/*-------------------------------------------------------------------------------------------------------------
                                 |
          CWWWWWWWW              | Copyright (C) 2009-2016  Christoph Guillermet
       WWWWWWWWWWWWWWW           |
     WWWWWWWWWWWWWWWWWWW         | This file is part of White Cat.
    WWWWWWWWWWWWWWWWWCWWWW       |
   WWWWWWWWWWWWWWWWW tWWWWW      | White Cat is free software: you can redistribute it and/or modify
  WWWW   WWWWWWWWWW  tWWWWWW     | it under the terms of the GNU General Public License as published by
 WWWWWt              tWWWWWWa    | the Free Software Foundation, either version 2 of the License, or
 WWWWWW               WWWWWWW    | (at your option) any later version.
WWWWWWWW              WWWWWWW    |
WWWWWWWW               WWWWWWW   | White Cat is distributed in the hope that it will be useful,
WWWWWWW               WWWWWWWW   | but WITHOUT ANY WARRANTY; without even the implied warranty of
WWWWWWW      CWWW    W WWWWWWW   | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
WWWWWWW            aW  WWWWWWW   | GNU General Public License for more details.
WWWWWWWW           C  WWWWWWWW   |
 WWWWWWWW            CWWWWWWW    | You should have received a copy of the GNU General Public License
 WWWWWWWWW          WWWWWWWWW    | along with White Cat.  If not, see <http://www.gnu.org/licenses/>.
  WWWWWWWWWWC    CWWWWWWWWWW     |
   WWWWWWWWWWWWWWWWWWWWWWWW      |
    WWWWWWWWWWWWWWWWWWWWWW       |
      WWWWWWWWWWWWWWWWWWa        |
        WWWWWWWWWWWWWWW          |
           WWWWWWWWt             |
                                 |
---------------------------------------------------------------------------------------------------------------*/

/**

* \file whc_mouse.cpp
* \brief {mouse services}
* \author Rui Serge Azevedo Brooks
* \version {1.0.0}
* \date {14/08/2016}

 White Cat - gui - mouse

*
*	Fonctions se basant sur les positions et états de la souris
*
*/
#include "whc_mouse.h"

/*Initialisation des variables de classe*/

//Buttons
float whc_mouseButton::c_gapSecond = 0.25; // Default Initialisation of  max time between two clics to be a double clic
whc_mouseButton::whc_eventclic whc_mouseButton::c_mouseLastClic = {none,clock()} ; /*{none,whc_button::c_milliseconds};*/
whc_mouseButton  whc_mouseButton::c_buttonLeft ;
whc_mouseButton  whc_mouseButton::c_buttonMiddle ;
whc_mouseButton  whc_mouseButton::c_buttonRight ;

std::vector<whc_mouseButton::whc_eventclic> whc_mouseButton::c_mouseClicHistory;

//Wheels
int whc_mouseWheel::c_mouse_z_prev = 0;
int whc_mouseWheel::c_mouse_w_prev = 0;
int whc_mouseWheel::c_loops = 0;
whc_mouseWheel whc_mouseWheel::c_mouseRoll(whc_mouseWheel::roll);
whc_mouseWheel whc_mouseWheel::c_mouseScroll(whc_mouseWheel::scroll);

//Pointer
whc_mousePointer::whc_pointerbmp  whc_mousePointer::c_arrow[whc_mouselook_size] = {{false,0,0},{false,0,0},{false,0,0},{false,0,0}};

//
whc_mouseButton::whc_mouseButton() : m_Down(false), m_Double(false), m_DragDrop(false), m_pending(false), m_Actor(0)
{
    //ctor
    m_dragpos.x = 0;
    m_dragpos.y = 0;
    whc_mouseButton::c_mouseClicHistory.clear();
    whc_mouseButton::c_mouseClicHistory.push_back (whc_mouseButton::c_mouseLastClic);
}

whc_mouseButton::~whc_mouseButton()
{
    //dtor
}

bool whc_mouseButton::c_toggle(bool & pushbutton)
{
    return pushbutton = (not pushbutton);
}

bool whc_mouseButton::c_IsThisADoubleClic (whc_mousebutton button)
{
    bool result = false ;
    whc_mouseButton::c_mouseLastClic = {button,clock()} ;  //{button,whc_button::c_milliseconds};

    if (whc_mouseButton::c_mouseClicHistory.size()>0)
    {
        if (whc_mouseButton::c_mouseClicHistory[0].button == whc_mouseButton::c_mouseLastClic.button)
        {

            clock_t present  = whc_mouseButton::c_mouseLastClic.cpu_clock_ticks ; 			// present  down
            clock_t past     = whc_mouseButton::c_mouseClicHistory[0].cpu_clock_ticks ; 	// previous down
            //
            //float present  = whc_button::c_mouseLastClic.cpu_clock_ticks ; 			// present  down
            //float past     = whc_button::c_mouseClicHistory[0].cpu_clock_ticks ; 	// previous down
            //

            float nbr_ticks_per_sec = CLOCKS_PER_SEC * 1.0 ;
            //float nbr_ticks_per_sec = 0.01 ;
            clock_t gap_in_ticks = (present - past) ;
            float gap_in_sec = gap_in_ticks / nbr_ticks_per_sec ;

            if (gap_in_sec < whc_mouseButton::c_gapSecond)
            {
                result = true ;
            }
        }
    }

    whc_mouseButton::c_mouseClicHistory.clear();
    whc_mouseButton::c_mouseClicHistory.push_back (whc_mouseButton::c_mouseLastClic);

    return result ;
}



void whc_mouseButton::c_CollectEvent (const int& mouseSignal, volatile int& mouse_x, volatile int& mouse_y)   //, whc_button& mouseClicLeft, whc_button& mouseClicMiddle, whc_button& mouseClicRight)
{
    if (mouseSignal & MOUSE_FLAG_LEFT_DOWN)
    {
        c_buttonLeft.m_Down = true ;
        c_buttonLeft.m_pending = true ;
        c_buttonLeft.m_Double = c_IsThisADoubleClic(left);
        c_buttonLeft.m_DragDrop = false;
        c_buttonLeft.m_dragpos.x = mouse_x;
        c_buttonLeft.m_dragpos.y = mouse_y ;
    }

    if (mouseSignal & MOUSE_FLAG_LEFT_UP)
    {
        c_buttonLeft.m_Down = false ;
        c_buttonLeft.m_DragDrop = ((c_buttonLeft.m_dragpos.x == mouse_x) && (c_buttonLeft.m_dragpos.y == mouse_y));
    }

    if (mouseSignal & MOUSE_FLAG_MIDDLE_DOWN)
    {
        c_buttonMiddle.m_Down = true ;
        c_buttonMiddle.m_pending = true ;
        c_buttonMiddle.m_Double = c_IsThisADoubleClic(middle);
        c_buttonMiddle.m_DragDrop = false;
        c_buttonMiddle.m_dragpos.x = mouse_x;
        c_buttonMiddle.m_dragpos.y = mouse_y ;
    }

    if (mouseSignal & MOUSE_FLAG_MIDDLE_UP)
    {
        c_buttonMiddle.m_Down = false ;
        c_buttonMiddle.m_DragDrop = ((c_buttonMiddle.m_dragpos.x == mouse_x) && (c_buttonMiddle.m_dragpos.y == mouse_y));
    }

    if (mouseSignal & MOUSE_FLAG_RIGHT_DOWN)
    {
        c_buttonRight.m_Down = true ;
        c_buttonRight.m_pending = true ;
        c_buttonRight.m_Double = c_IsThisADoubleClic(right);
        c_buttonRight.m_DragDrop = false;
        c_buttonRight.m_dragpos.x = mouse_x;
        c_buttonRight.m_dragpos.y = mouse_y ;
    }

    if (mouseSignal & MOUSE_FLAG_RIGHT_UP)
    {
        c_buttonRight.m_Down = false ;
        c_buttonRight.m_DragDrop = ((c_buttonRight.m_dragpos.x == mouse_x) && (c_buttonRight.m_dragpos.y == mouse_y));
    }
}


//------------------------------------------------------------------------------------------------------------------------------


whc_mouseWheel::whc_mouseWheel() : m_level(0), m_gain(0), m_yield(0), m_speed(0), m_pending(false)
{
    //ctor
}
whc_mouseWheel::whc_mouseWheel(whc_mousewheel wheel) : m_level(0), m_gain(0), m_yield(0), m_speed(0), m_pending(false)
{
    m_wheel = wheel;
}

whc_mouseWheel::~whc_mouseWheel()
{
    //dtor
}

void whc_mouseWheel::c_Init (volatile int& mouse_z, volatile int& mouse_w)
{
    whc_mouseWheel::c_mouse_z_prev = mouse_z ;
    whc_mouseWheel::c_mouse_w_prev = mouse_w ;
}

void whc_mouseWheel::c_CollectKeyStatus () //(whc_mouseWheel& mouseScroll , whc_mouseWheel& mouseRoll)
{
    if (not (key[KEY_LCONTROL]))
    {
        c_loops = 0;

        if (not (c_mouseScroll.m_speed==0))
        {
            c_mouseScroll.m_speed = 0;
            c_mouseScroll.m_yield = 0;
            c_mouseScroll.m_pending = false;
        }
        if (not (c_mouseScroll.m_speed==0))
        {
            c_mouseRoll.m_speed = 0;
            c_mouseRoll.m_yield = 0;
            c_mouseRoll.m_pending = false;
        }
    }
    else
    {
        if (c_mouseScroll.m_speed==0 && c_mouseRoll.m_speed==0)
        {
            c_loops = 0;
        }
    }
}

void whc_mouseWheel::c_CollectEvent (const int& mouseSignal, volatile int& mouse_z, volatile int& mouse_w) //, whc_mouseWheel& mouseScroll , whc_mouseWheel& mouseRoll)
{
    c_mouseRoll.m_gain = 0 ;
    c_mouseScroll.m_gain = 0 ;

    if (mouseSignal & MOUSE_FLAG_MOVE_Z)
    {
        //Scroll
        if (key[KEY_LSHIFT]) 	//emulate Roll with Scroll (Z)
        {
            c_mouseRoll.m_pending=true;
            c_mouseRoll.SetGain(mouse_z - c_mouse_z_prev); //Instant mouvement of the wheel : -1, 0, +1 // Yield is updated in the same time
            c_mouseRoll.SetLevel(c_mouseRoll.level() + c_mouseRoll.gain()); // level is not automatically set to 0 when event processed (mouse_w will be : see case default)
            c_mouse_z_prev = mouse_z;

            if ((key[KEY_LCONTROL]))
            {
                c_mouseRoll.SetSpeed(c_mouseRoll.speed() + c_mouseRoll.gain());	//Instant acceleration
            }
            else
            {
                c_mouseRoll.SetSpeed(0);
            }
        }
        else					//Scroll
        {
            c_mouseScroll.m_pending=true;
            c_mouseScroll.SetGain(mouse_z - c_mouse_z_prev); //Instant mouvement of the wheel : -1, 0, +1 // Yield is updated in the same time
            c_mouseScroll.SetLevel(c_mouseScroll.level() + c_mouseScroll.gain()); // level is not automatically set to 0 when event processed (mouse_z will be : see case default)
            c_mouse_z_prev = mouse_z;

            if ((key[KEY_LCONTROL]))
            {
                c_mouseScroll.SetSpeed(c_mouseScroll.speed() + c_mouseScroll.gain());	//Instant acceleration
            }
            else
            {
                c_mouseScroll.SetSpeed(0);
            }
        }
    }

    if (mouseSignal & MOUSE_FLAG_MOVE_W)
    {
        //Roll
        c_mouseRoll.m_pending=true;
        c_mouseRoll.SetGain(mouse_w - c_mouse_w_prev); //Instant mouvement of the wheel : -1, 0, +1 // Yield is updated in the same time
        c_mouseRoll.SetLevel(c_mouseRoll.level() + c_mouseRoll.gain()); // level is not automatically set to 0 when event processed (mouse_w will be : see case default)
        c_mouse_w_prev = mouse_w;

        if ((key[KEY_LCONTROL]))
        {
            c_mouseRoll.SetSpeed(c_mouseRoll.speed() + c_mouseRoll.gain());	//Instant acceleration
        }
        else
        {
            c_mouseRoll.SetSpeed(0);
        }
    }

    if (c_mouseScroll.isProcessed() && (not (mouse_z==0)))
    {
        c_mouseScroll.m_yield = 0;
        c_loops = 0;
    }

    if (c_mouseRoll.isProcessed() && (not (mouse_w==0)))
    {
        c_mouseRoll.m_yield = 0;
        c_loops = 0;
    }
}

// SANS ACCELERATION
void whc_mouseWheel::c_levelIncrease(const whc_mousewheel & type, int & i_level, const int maxlevel, const int minlevel, const float increaseFactor, const float increaseFactor_onLeftCtl)
{
    whc_mouseWheel * wheel ;
    if (type == roll)
    {
        wheel = &c_mouseRoll;
    }
    else
    {
        wheel = &c_mouseScroll;
    }

    if ((key[KEY_LCONTROL]))
    {
        i_level = i_level + int(wheel->gain() * increaseFactor_onLeftCtl) ;
    }
    else
    {
        i_level = i_level + int(wheel->gain() * increaseFactor) ;
    }

    wheel->SetProcessed();

    if (i_level > maxlevel)
    {
        i_level=maxlevel;
    }
    if (i_level<minlevel)
    {
        i_level=minlevel ;
    }
}

int whc_mouseWheel::c_levelIncrease(const whc_mousewheel & type, float & f_level, const float maxlevel, const float minlevel, const float increaseFactor, const float increaseFactor_onLeftCtl)
{
    whc_mouseWheel * wheel ;
    if (type == roll)
    {
        wheel = &c_mouseRoll;
    }
    else
    {
        wheel = &c_mouseScroll;
    }

    if ((key[KEY_LCONTROL]))
    {
        f_level = f_level + (wheel->gain() * increaseFactor_onLeftCtl) ;
    }
    else
    {
        f_level = f_level + (wheel->gain() * increaseFactor) ;
    }

    wheel->SetProcessed();

    if (f_level > maxlevel)
    {
        f_level=maxlevel;
    }
    if (f_level<minlevel)
    {
        f_level=minlevel ;
    }
    return (int) f_level;
}

void whc_mouseWheel::c_rotatorLevelIncrease(const whc_mousewheel & type, int & i_level, const int maxlevel, const int minlevel, const float increaseFactor, const float increaseFactor_onLeftCtl)
{
    whc_mouseWheel * wheel ;
    if (type == roll)
    {
        wheel = &c_mouseRoll;
    }
    else
    {
        wheel = &c_mouseScroll;
    }

    if ((key[KEY_LCONTROL]))
    {
        i_level = i_level + int(wheel->gain() * increaseFactor_onLeftCtl) ;
    }
    else
    {
        i_level = i_level + int(wheel->gain() * increaseFactor) ;
    }

    wheel->SetProcessed();

    if (i_level > maxlevel)
    {
        i_level=minlevel;
    }
    if (i_level<minlevel)
    {
        i_level=maxlevel ;
    }
}

int whc_mouseWheel::c_rotatorLevelIncrease(const whc_mousewheel & type, float & f_level, const float maxlevel, const float minlevel, const float increaseFactor, const float increaseFactor_onLeftCtl)
{
    whc_mouseWheel * wheel ;
    if (type == roll)
    {
        wheel = &c_mouseRoll;
    }
    else
    {
        wheel = &c_mouseScroll;
    }

    if ((key[KEY_LCONTROL]))
    {
        f_level = f_level + (wheel->gain() * increaseFactor_onLeftCtl) ;
    }
    else
    {
        f_level = f_level + (wheel->gain() * increaseFactor) ;
    }

    wheel->SetProcessed();

    if (f_level > maxlevel)
    {
        f_level=minlevel;
    }
    if (f_level<minlevel)
    {
        f_level=maxlevel ;
    }
    return (int) f_level;
}

// Modifie la valeur de la variable float fournie par référence : f_level
// et retourne la part entière signée (int)

// AUGMENTATION selon SPEED et TIME le nombre de passage dans la boucle --
// Après un nombre de passage dans la boucle (loopsbystep) le niveau (level) est augmentation/diminué selon (speed) courant
void whc_mouseWheel::c_levelSpeedupIncrease(const whc_mousewheel & type, int & i_level, const int maxlevel, const int minlevel, const int time_in_number_of_loops)
{

    whc_mouseWheel * wheel ;
    if (type == roll)
    {
        wheel = &c_mouseRoll;
    }
    else
    {
        wheel = &c_mouseScroll;
    }

    whc_mouseWheel::c_loops ++;

    if (whc_mouseWheel::c_loops>=time_in_number_of_loops)
    {
        whc_mouseWheel::c_loops = 1;
        i_level = i_level + wheel->speed();

        if (i_level > maxlevel)
        {
            i_level=maxlevel;
        }
        if (i_level<minlevel)
        {
            i_level=minlevel ;
        }
        wheel->isProcessed();
    }
}

int whc_mouseWheel::c_levelSpeedupIncrease(const whc_mousewheel & type, float & f_level, const float maxlevel, const float minlevel, const float frequency_in_number_of_loops)
{
    whc_mouseWheel * wheel ;
    if (type == roll)
    {
        wheel = &c_mouseRoll;
    }
    else
    {
        wheel = &c_mouseScroll;
    }

    float speedratio_per_loop = wheel->speed() / frequency_in_number_of_loops ;
    f_level = f_level + speedratio_per_loop;

    if (f_level > maxlevel)
    {
        f_level=maxlevel;
    }
    if (f_level<minlevel)
    {
        f_level=minlevel ;
    }
    return (int) f_level;
}

bool whc_mouseWheel::isSubscriber(const int & data)
{
    if (m_subscriberList.size() > 0)
    {
        whc_mouseWheel::whc_wheeledcontroller controleur;
        for (std::vector<whc_mouseWheel::whc_wheeledcontroller>::iterator it = m_subscriberList.begin() ;
                it != m_subscriberList.end();
                ++it)
        {
            controleur = *it;
            if (controleur.controller == &data)
            {
                return true;
            }
        }
    }
    return false;
}

void whc_mouseWheel::addSubscriber(int &data, const whc_wheeledcontrollertype type, const int minimum, const int maximum, whc_mousewheelkey keypress)
{
    whc_mouseWheel::whc_wheeledcontroller controleur;
    controleur.controller 	= &data ;
    controleur.type 		= type ;
    controleur.maximum 		= maximum ;
    controleur.minimum 		= minimum ;
    controleur.keypress     = keypress ;
    m_subscriberList.push_back(controleur);
}

bool whc_mouseWheel::unsubscribe(const int & data)
{
	if (isSubscriber(data))
	{
		pullSubscriber(data);
		return true;
	}
	return false ;
}

void whc_mouseWheel::pullSubscriber(const int & data)
{
	whc_mouseWheel::whc_wheeledcontroller controleur;
	std::vector<whc_mouseWheel::whc_wheeledcontroller>::iterator it_to_del;

    while (isSubscriber(data))
    {
        for (std::vector<whc_mouseWheel::whc_wheeledcontroller>::iterator it = m_subscriberList.begin() ;
                it != m_subscriberList.end();
                ++it)
        {
            controleur = *it;
            if (controleur.controller == &data)
            {
                it_to_del = it;
            }
        }
        m_subscriberList.erase(it_to_del);
    }
}

void whc_mouseWheel::handOverSubscriber(whc_mousewheelkey keypress)
{
    if (m_subscriberList.size() > 0)
	{
		whc_mouseWheel::whc_wheeledcontroller controleur;
		for (std::vector<whc_mouseWheel::whc_wheeledcontroller>::iterator it = m_subscriberList.begin() ; it != m_subscriberList.end(); ++it)
	   {
			controleur = *it;
			if (controleur.keypress==keypress)
			{
				if (controleur.type==whc_mouseWheel::slider)
				{
					whc_mouseWheel::c_levelIncrease(this->m_wheel, *controleur.controller,   controleur.maximum, controleur.minimum);
				}
				else // rotary
				{
					whc_mouseWheel::c_rotatorLevelIncrease(this->m_wheel, *controleur.controller,   controleur.maximum, controleur.minimum);
				}
			}
	   }
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------

whc_mousePointer::whc_mousePointer() : m_x(0), m_y(0)
{
    //ctor
}

whc_mousePointer::whc_mousePointer(volatile int& mouse_x, volatile int& mouse_y)
{
    //ctor
    m_x = mouse_x ;
    m_y = mouse_y ;
}
whc_mousePointer::~whc_mousePointer()
{
    //dtor
}

bool whc_mousePointer::c_Init(whc_mouselook idx, const char *pathtobmp)
{
    whc_mousePointer::c_arrow[idx].loaded = whc_mousePointer::c_arrow[idx].bmp.Load( pathtobmp );
    return whc_mousePointer::c_arrow[idx].loaded ;
}

bool whc_mousePointer::Draw()
{

    try
    {
        if (whc_mousePointer::c_arrow[m_look].loaded)
        {
            int xx = mouse_x + c_arrow[m_look].mouse_x_in_png;
            int yy = mouse_y + c_arrow[m_look].mouse_y_in_png;
            whc_mousePointer::c_arrow[m_look].bmp.Blit(xx, yy);
            return true;
        }
        else
        {
            return false ;  //pas d'image chargée
        }
    }
    catch ( const std::exception & e )
    {
        return false;
    }
    return false;
}
