#include "whc_mouse.h"

/*Initialisation des variables de classe*/

//Buttons
float whc_button::c_gapSecond = 0.25; // Default Initialisation of  max time between two clics to be a double clic
whc_button::whc_eventclic whc_button::c_mouseLastClic = {none,clock()} ; /*{none,whc_button::c_milliseconds};*/

std::vector<whc_button::whc_eventclic> whc_button::c_mouseClicHistory;

//Wheels
int whc_wheel::c_mouse_z_prev = 0;
int whc_wheel::c_mouse_w_prev = 0;
int whc_wheel::c_loops = 0;

//Pointer
whc_pointer::whc_pointerbmp  whc_pointer::c_arrow[whc_mouselook_size] = {{false,0,0},{false,0,0},{false,0,0},{false,0,0}};

//
whc_button::whc_button() : m_Down(false), m_Double(false), m_DragDrop(false), m_pending(false), m_Actor(0)
{
    //ctor
    m_dragpos.x = 0;
    m_dragpos.y = 0;
    whc_button::c_mouseClicHistory.clear();
    whc_button::c_mouseClicHistory.push_back (whc_button::c_mouseLastClic);
}

whc_button::~whc_button()
{
    //dtor
}

bool whc_button::c_toggle(bool & pushbutton)
{
	pushbutton = (not pushbutton);
}

bool whc_button::c_IsThisADoubleClic (whc_mousebutton button)
{
    bool result = false ;
    whc_button::c_mouseLastClic = {button,clock()} ;  //{button,whc_button::c_milliseconds};

    if (whc_button::c_mouseClicHistory.size()>0)
    {
        if (whc_button::c_mouseClicHistory[0].button == whc_button::c_mouseLastClic.button)
        {

            clock_t present  = whc_button::c_mouseLastClic.cpu_clock_ticks ; 			// present  down
            clock_t past     = whc_button::c_mouseClicHistory[0].cpu_clock_ticks ; 	// previous down
            //
            //float present  = whc_button::c_mouseLastClic.cpu_clock_ticks ; 			// present  down
            //float past     = whc_button::c_mouseClicHistory[0].cpu_clock_ticks ; 	// previous down
            //

            float nbr_ticks_per_sec = CLOCKS_PER_SEC * 1.0 ;
            //float nbr_ticks_per_sec = 0.01 ;
            clock_t gap_in_ticks = (present - past) ;
            float gap_in_sec = gap_in_ticks / nbr_ticks_per_sec ;

            if (gap_in_sec < whc_button::c_gapSecond)
            {
                result = true ;
            }
        }
    }

    whc_button::c_mouseClicHistory.clear();
    whc_button::c_mouseClicHistory.push_back (whc_button::c_mouseLastClic);

    return result ;
}

void whc_button::c_CollectEvent (int& mouseSignal, volatile int& mouse_x, volatile int& mouse_y, whc_button& mouseClicLeft, whc_button& mouseClicMiddle, whc_button& mouseClicRight)
{
    if (mouseSignal & MOUSE_FLAG_LEFT_DOWN)
    {
        mouseClicLeft.m_Down = true ;
        mouseClicLeft.m_pending = true ;
        mouseClicLeft.m_Double = c_IsThisADoubleClic(left);
        mouseClicLeft.m_DragDrop = false;
        mouseClicLeft.m_dragpos.x = mouse_x;
        mouseClicLeft.m_dragpos.y = mouse_y ;
    }

    if (mouseSignal & MOUSE_FLAG_LEFT_UP)
    {
        mouseClicLeft.m_Down = false ;
        mouseClicLeft.m_DragDrop = ((mouseClicLeft.m_dragpos.x == mouse_x) && (mouseClicLeft.m_dragpos.y == mouse_y));
    }

    if (mouseSignal & MOUSE_FLAG_MIDDLE_DOWN)
    {
        mouseClicMiddle.m_Down = true ;
        mouseClicMiddle.m_pending = true ;
        mouseClicMiddle.m_Double = c_IsThisADoubleClic(middle);
        mouseClicMiddle.m_DragDrop = false;
        mouseClicMiddle.m_dragpos.x = mouse_x;
        mouseClicMiddle.m_dragpos.y = mouse_y ;
    }

    if (mouseSignal & MOUSE_FLAG_MIDDLE_UP)
    {
        mouseClicMiddle.m_Down = false ;
        mouseClicMiddle.m_DragDrop = ((mouseClicMiddle.m_dragpos.x == mouse_x) && (mouseClicMiddle.m_dragpos.y == mouse_y));
    }

    if (mouseSignal & MOUSE_FLAG_RIGHT_DOWN)
    {
        mouseClicRight.m_Down = true ;
        mouseClicRight.m_pending = true ;
        mouseClicRight.m_Double = c_IsThisADoubleClic(right);
        mouseClicRight.m_DragDrop = false;
        mouseClicRight.m_dragpos.x = mouse_x;
        mouseClicRight.m_dragpos.y = mouse_y ;
    }

    if (mouseSignal & MOUSE_FLAG_RIGHT_UP)
    {
        mouseClicRight.m_Down = false ;
        mouseClicRight.m_DragDrop = ((mouseClicRight.m_dragpos.x == mouse_x) && (mouseClicRight.m_dragpos.y == mouse_y));
    }
}


//------------------------------------------------------------------------------------------------------------------------------


whc_wheel::whc_wheel() : m_level(0), m_gain(0), m_yield(0), m_speed(0), m_pending(false)
{
    //ctor
}

whc_wheel::~whc_wheel()
{
    //dtor
}

void whc_wheel::c_Init (volatile int& mouse_z, volatile int& mouse_w)
{
    whc_wheel::c_mouse_z_prev = mouse_z ;
    whc_wheel::c_mouse_w_prev = mouse_w ;
}
void whc_wheel::c_CollectKeyStatus (whc_wheel& mouseScroll , whc_wheel& mouseRoll)
{
    if (not (key[KEY_LCONTROL]))
    {
        whc_wheel::c_loops = 0;

        if (not (mouseScroll.m_speed==0))
        {
            mouseScroll.m_speed = 0;
            mouseScroll.m_yield = 0;
            mouseScroll.m_pending = false;
        }
        if (not (mouseScroll.m_speed==0))
        {
            mouseRoll.m_speed = 0;
            mouseRoll.m_yield = 0;
            mouseRoll.m_pending = false;
        }
    }
}

void whc_wheel::c_CollectEvent (int& mouseSignal, volatile int& mouse_z, volatile int& mouse_w, whc_wheel& mouseScroll , whc_wheel& mouseRoll)
{
    mouseRoll.m_gain = 0 ;
    mouseScroll.m_gain = 0 ;

    if (mouseSignal & MOUSE_FLAG_MOVE_Z)
    {
        //Scroll
        if (key[KEY_LSHIFT]) 	//emulate Roll with Scroll (Z)
        {
            mouseRoll.m_pending=true;
            mouseRoll.SetGain(mouse_z - whc_wheel::c_mouse_z_prev); //Instant mouvement of the wheel : -1, 0, +1 // Yield is updated in the same time
            mouseRoll.SetLevel(mouseRoll.level() + mouseRoll.gain()); // level is not automatically set to 0 when event processed (mouse_w will be : see case default)
            whc_wheel::c_mouse_z_prev = mouse_z;

            if ((key[KEY_LCONTROL]))
            {
                mouseRoll.SetSpeed(mouseRoll.speed() + mouseRoll.gain());	//Instant acceleration
            }
            else
            {
                mouseRoll.SetSpeed(0);
            }
        }
        else					//Scroll
        {
            mouseScroll.m_pending=true;
            mouseScroll.SetGain(mouse_z - whc_wheel::c_mouse_z_prev); //Instant mouvement of the wheel : -1, 0, +1 // Yield is updated in the same time
            mouseScroll.SetLevel( mouseScroll.level() + mouseScroll.gain()); // level is not automatically set to 0 when event processed (mouse_z will be : see case default)
            whc_wheel::c_mouse_z_prev = mouse_z;

            if ((key[KEY_LCONTROL]))
            {
                mouseScroll.SetSpeed(mouseScroll.speed() + mouseScroll.gain());	//Instant acceleration
            }
            else
            {
                mouseScroll.SetSpeed(0);
            }
        }
    }

    if (mouseSignal & MOUSE_FLAG_MOVE_W)
    {
        //Roll
        mouseRoll.m_pending=true;
        mouseRoll.SetGain(mouse_w - whc_wheel::c_mouse_w_prev); //Instant mouvement of the wheel : -1, 0, +1 // Yield is updated in the same time
        mouseRoll.SetLevel(mouseRoll.level() + mouseRoll.gain()); // level is not automatically set to 0 when event processed (mouse_w will be : see case default)
        whc_wheel::c_mouse_w_prev = mouse_w;

        if ((key[KEY_LCONTROL]))
        {
            mouseRoll.SetSpeed(mouseRoll.speed() + mouseRoll.gain());	//Instant acceleration
        }
        else
        {
            mouseRoll.SetSpeed(0);
        }
    }

    if (mouseScroll.isProcessed() && (not (mouse_z==0)))
    {
        //position_mouse_z(0);
        //whc_wheel::c_mouse_z_prev = 0 ;
        mouseScroll.m_yield = 0;
        whc_wheel::c_loops = 0;
    }

    if (mouseRoll.isProcessed() && (not (mouse_w==0)))
    {
        //position_mouse_w(0);
        //whc_wheel::c_mouse_w_prev = 0;
        mouseRoll.m_yield = 0;
        whc_wheel::c_loops = 0;
    }
}

// SANS ACCELERATION
void whc_wheel::c_levelIncrease(whc_wheel & wheel, int & i_level, const int maxlevel, const int minlevel, const float increaseFactor, const float increaseFactor_onLeftCtl)
{
    if ((key[KEY_LCONTROL]))
	{
		i_level = i_level + int(wheel.gain() * increaseFactor_onLeftCtl) ;
	}
	else
	{
		i_level = i_level + int(wheel.gain() * increaseFactor) ;
	}

    wheel.SetProcessed();

    if (i_level > maxlevel)
    {
        i_level=maxlevel;
    }
    if (i_level<minlevel)
    {
        i_level=minlevel ;
    }
}

int whc_wheel::c_levelIncrease(whc_wheel & wheel, float & f_level, const float maxlevel, const float minlevel, const float increaseFactor, const float increaseFactor_onLeftCtl)
{
    if ((key[KEY_LCONTROL]))
	{
		f_level = f_level + (wheel.gain() * increaseFactor_onLeftCtl) ;
	}
	else
	{
		f_level = f_level + (wheel.gain() * increaseFactor) ;
	}

    wheel.SetProcessed();

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

void whc_wheel::c_rotatorLevelIncrease(whc_wheel & wheel, int & i_level, const int maxlevel, const int minlevel, const float increaseFactor, const float increaseFactor_onLeftCtl)
{
     if ((key[KEY_LCONTROL]))
	{
		i_level = i_level + int(wheel.gain() * increaseFactor_onLeftCtl) ;
	}
	else
	{
			i_level = i_level + int(wheel.gain() * increaseFactor) ;
	}

    wheel.SetProcessed();

    if (i_level > maxlevel)
    {
        i_level=minlevel;
    }
    if (i_level<minlevel)
    {
        i_level=maxlevel ;
    }
}

int whc_wheel::c_rotatorLevelIncrease(whc_wheel & wheel, float & f_level, const float maxlevel, const float minlevel, const float increaseFactor, const float increaseFactor_onLeftCtl)
{
        if ((key[KEY_LCONTROL]))
	{
		f_level = f_level + (wheel.gain() * increaseFactor_onLeftCtl) ;
	}
	else
	{
		f_level = f_level + (wheel.gain() * increaseFactor) ;
	}

    wheel.SetProcessed();

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

// Modifie la valeur de la variable float fournie par r�f�rence : f_level
// et retourne la part enti�re sign�e (int)

// AUGMENTATION selon SPEED et TIME le nombre de passage dans la boucle --
// Apr�s un nombre de passage dans la boucle (loopsbystep) le niveau (level) est augmentation/diminu� selon (speed) courant
void whc_wheel::c_levelSpeedupIncrease(whc_wheel & wheel, int & i_level, const int maxlevel, const int minlevel, const int time_in_number_of_loops)
{

    whc_wheel::c_loops ++;

    if (whc_wheel::c_loops>=time_in_number_of_loops)
    {
        whc_wheel::c_loops = 1;
        i_level = i_level + wheel.speed();

        if (i_level > maxlevel)
        {
            i_level=maxlevel;
        }
        if (i_level<minlevel)
        {
            i_level=minlevel ;
        }
        wheel.isProcessed();
    }
}

int whc_wheel::c_levelSpeedupIncrease(whc_wheel & wheel, float & f_level, const float maxlevel, const float minlevel, const float frequency_in_number_of_loops)
{
    float speedratio_per_loop = wheel.speed() / frequency_in_number_of_loops ;
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


//---------------------------------------------------------------------------------------------------------------------------------------


whc_pointer::whc_pointer() : m_x(0), m_y(0)
{
    //ctor
}

whc_pointer::whc_pointer(volatile int& mouse_x, volatile int& mouse_y)
{
    //ctor
    m_x = mouse_x ;
    m_y = mouse_y ;
}
whc_pointer::~whc_pointer()
{
    //dtor
}

bool whc_pointer::c_Init(whc_mouselook idx, const char *pathtobmp)
{
    whc_pointer::c_arrow[idx].loaded = whc_pointer::c_arrow[idx].bmp.Load( pathtobmp );
    return whc_pointer::c_arrow[idx].loaded ;
}

bool whc_pointer::Draw()
{

	try
	{
		if (whc_pointer::c_arrow[m_look].loaded)
		{
			int xx = mouse_x + c_arrow[m_look].mouse_x_in_png;
			int yy = mouse_y + c_arrow[m_look].mouse_y_in_png;
			whc_pointer::c_arrow[m_look].bmp.Blit(xx, yy);
			return true;
		}
		else
		{
			return false ;  //pas d'image charg�e
		}
	}
	catch ( const std::exception & e )
	{
			return false;
	}
    return false;
}

