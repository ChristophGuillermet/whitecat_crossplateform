#ifndef WHC_MOUSE_H
#define WHC_MOUSE_H

//Allegro
#include <allegro/mouse.h>
#include <allegro/keyboard.h>
//OpenLayer -  interface to graphical library
#include <OpenLayer.hpp>
//C library
#include <time.h>
//Container C compatible
#include <vector>
//Boost
/*
Boost.DateTime offers an additional class named boost::posix_time::microsec_clock
that returns the current time including microseconds in case a higher resolution is required.
#include "boost/date_time/local_time/local_time.hpp"
time_zone_ptr
  zone(new posix_time_zone("MST-07"));
local_date_time
  ldt((ptime(date(2005,Jan,1),hours(0))), zone);
local_time_period ltp(ldt, hours(2));
ltp.length(); // => 02:00:00
*/

class whc_mouseButton
{
public:
    typedef enum
    {
        left   = 100,
        middle = 010,
        right  = 001,

        leftmiddle   = 110,
        leftright    = 101,
        middleright  = 011,

        leftmiddleright   = 111,

        none   = 000
    } whc_mousebutton ;

    typedef struct whc_eventclic
    {
        whc_mousebutton button;
        clock_t cpu_clock_ticks;
        //float cpu_clock_ticks;
    } whc_eventclic;

    typedef struct whc_mousepos
    {
        short int x, y ;
    } whc_mousepos;


    float static c_gapSecond ; 	//!< Instance variable - gapSecond : max time between two clics to be a double clic
    whc_eventclic static c_mouseLastClic ;	//!< Instance variable - mouseLastClic :
    std::vector<whc_eventclic> static c_mouseClicHistory; //!< Instance variable - mouseClicHistory :
    bool static c_IsThisADoubleClic (whc_mousebutton);
    bool static c_toggle(bool & pushbutton) ;
    whc_mouseButton static c_buttonLeft ;
    whc_mouseButton static c_buttonMiddle ;
    whc_mouseButton static c_buttonRight ;
    void static c_CollectEvent (const int& mousesignal, volatile int& mouse_x, volatile int& mouse_y); //, whc_button& mouseClicLeft, whc_button& mouseClicMiddle, whc_button& mouseClicRight);

    /** Default constructor */
    whc_mouseButton();
    /** Default destructor */
    virtual ~whc_mouseButton();

    /** Evaluate if down over Rectangle
     * \return bool
     * \param x_left, y_top, x_size, y_size, set_processed
     */
    bool toBeProcessed_isDown_isOverRecSize(int x_left, int y_top, int x_size, int y_size, bool set_processed=false)
    {
        if (m_pending)
        {
            bool value = isOverRecSize(x_left, y_top, x_size, y_size);
            if (value and set_processed)
            {
                m_pending = false ;
            };
            return value;
        }
        return false;
    }
    bool toBeProcessed_isDouble_isOverRecSize(int x_left, int y_top, int x_size, int y_size, bool set_processed=false)
    {
        if (m_pending and m_Double)
        {
            bool value = isOverRecSize(x_left, y_top, x_size, y_size);
            if (value and set_processed)
            {
                m_pending = false ;
            };
            return value;
        }
        return false;
    }
    bool isOverRecSize(int x_left, int y_top, int x_size, int y_size)
    {
        return ((mouse_x>=x_left) and (mouse_x<=x_left+x_size) and (mouse_y>=y_top) and (mouse_y<=y_top+y_size));
    }
    /** Evaluate if down over Rectangle
     * \return bool
     * \param x_left, y_top, x_right, y_bottom, set_processed
     */
    bool toBeProcessed_isDown_isOverRecPos(int x_left, int y_top, int x_right, int y_bottom, bool set_processed=false)
    {
        if (m_pending)
        {
            bool value = isOverRecPos(x_left, y_top, x_right, y_bottom);
            if (value and set_processed)
            {
                m_pending = false ;
            };
            return value;
        }
        return false;
    }
    bool toBeProcessed_isDouble_isOverRecPos(int x_left, int y_top, int x_right, int y_bottom, bool set_processed=false)
    {
        if (m_pending and m_Double)
        {
            bool value = isOverRecPos(x_left, y_top, x_right, y_bottom);
            if (value and set_processed)
            {
                m_pending = false ;
            };
            return value;
        }
        return false;
    }
    bool isOverRecPos(int x_left, int y_top, int x_right, int y_bottom)
    {
        return ((mouse_x>=x_left) and (mouse_x<=x_right) and (mouse_y>=y_top) and (mouse_y<=y_bottom));
    }

    /** Access m_Down
     * \return The current value of m_Down
     */
    bool isDown()
    {
        return m_Down;
    }
    bool isUp()
    {
        return (not m_Down);
    }
    bool isDownToBeProcessed()
    {
        return (m_Down && m_pending);
    }
    /** Set m_Down
     * \param val New value to set
     */
    void SetDown(bool val=true)
    {
        m_Down = val;
    }
    void SetUp(bool val=true)
    {
        m_Down = (not val);
    }

    /** Access m_Double
     * \return The current value of m_Double
     */
    bool isDouble()
    {
        return m_Double;
    }
    bool isSimple()
    {
        return (not m_Double);
    }
    /** Set m_Double
     * \param val New value to set
     */
    void SetDouble(bool val=true)
    {
        m_Double = val;
    }

    /** Access m_DragDrop
     * \return The current value of m_DragDrop
     */
    bool isDragDrop()
    {
        return m_DragDrop;
    }
    bool isNotDrop()
    {
        return (not m_DragDrop);
    }
    /** Set m_DragDrop
     * \param val New value to set
     */
    void SetDragDrop(bool val=true)
    {
        m_DragDrop = val;
    }

    /** Access m_dragpos
     * \param val New value to set
     */
    whc_mousepos dragPos()
    {
        return m_dragpos;
    }
    int  dragPosX()
    {
        return m_dragpos.x;
    }
    int  dragPosY()
    {
        return m_dragpos.y;
    }
    /** Set m_dragpos
     * \param val New value to set
     */
    void SetDragPos(volatile int x, volatile int y)
    {
        m_dragpos.x = x ;
        m_dragpos.y = y ;
    }

    /** Access m_Actor
     * \return The current value of m_Actor
     */
    int lastActor()
    {
        return m_Actor ;
    }

    /** Access m_pending
     * \return The current value of m_pending
     */
    bool isProcessed()
    {
        return (not m_pending);
    }
    bool isToBeProcessed()
    {
        return m_pending;
    }
    /** Set m_pending
     * \param val New value to set
     */
    void SetProcessed(int actor=0, bool val=true)
    {
        m_Actor = actor ;
        m_pending = (not val);
    }
    void SetToBeProcessed(int actor=0, bool val=true)
    {
        m_Actor = actor ;
        m_pending = val;
    }

protected:
private:
    whc_mousepos m_dragpos; //!< Member variable "m_dragpos"
    bool m_Down; //!< Member variable "m_Down"
    bool m_Double; //!< Member variable "m_Double"
    bool m_DragDrop; //!< Member variable "m_Double"
    bool m_pending; //!< Member variable "m_pending"
    int m_Actor;
};


//---------------------------------------------------------------------------------------------------------------------------------------


class whc_mouseWheel
{
public:
	typedef enum
    {
        scroll = 1,
        roll   = 2
    } whc_mousewheel ;

	typedef enum
	{
		none   = 0,
		slider = 1,
		rotary = 2
	} whc_wheeledcontrollertype ;

	typedef enum
    {
        nokey  = 0,
        ctlkey = 1,
		altkey = 2
    } whc_mousewheelkey ;

    typedef struct whc_wheeledcontroller
    {
        int* controller;
        whc_wheeledcontrollertype type;
        int minimum;
        int maximum;
        whc_mousewheelkey keypress;
    } whc_wheeledcontroller;

    int static c_mouse_z_prev;
    int static c_mouse_w_prev;
    int static c_loops;

    whc_mouseWheel static c_mouseRoll;
    whc_mouseWheel static c_mouseScroll;

    void static c_Init(volatile int& mouse_z, volatile int& mouse_w);
    void static c_CollectEvent (const int& mousesignal, volatile int& mouse_z, volatile int& mouse_w) ; //, whc_mouseWheel& mouseScroll , whc_mouseWheel& mouseRoll);
    void static c_CollectKeyStatus () ;//(whc_mouseWheel& mouseScroll , whc_mouseWheel& mouseRoll);

    void static c_levelIncrease(const whc_mousewheel &type,        int &i_level,   const int maxlevel,   const int minlevel,   const float increaseFactor=1., const float increaseFactor_onLeftCtl=1.);
    int  static c_levelIncrease(const whc_mousewheel &type,        float &f_level, const float maxlevel, const float minlevel, const float increaseFactor=1., const float increaseFactor_onLeftCtl=1.);
    void static c_levelSpeedupIncrease(const whc_mousewheel &type, int &i_level,   const int maxlevel,   const int minlevel,   const int time_in_number_of_loops);
    int  static c_levelSpeedupIncrease(const whc_mousewheel &type, float &f_level, const float maxlevel, const float minlevel, const float frequency_in_number_of_loops);

    void static c_rotatorLevelIncrease(const whc_mousewheel &type,        int &i_level,   const int maxlevel,   const int minlevel,   const float increaseFactor=1., const float increaseFactor_onLeftCtl=1.);
    int  static c_rotatorLevelIncrease(const whc_mousewheel &type,        float &f_level, const float maxlevel, const float minlevel, const float increaseFactor=1., const float increaseFactor_onLeftCtl=1.);

    /** Default constructor */
    whc_mouseWheel();
    whc_mouseWheel(whc_mousewheel wheel);
    /** Default destructor */
    virtual ~whc_mouseWheel();

    /** Access m_level
     * \param val New value to set
     */
    int level()
    {
        return m_level;
    }
    /** Set m_level
     * \param val New value to set
     */
    void SetLevel(int val)
    {
        m_level=val;
    }

    /** Access m_gain
     * \param val New value to set
     */
    int gain()
    {
        return m_gain;
    }
    /** Set m_gain
     * \param val New value to set
     */
    void SetGain(int val)
    {
        m_gain=val;
        m_yield = m_yield + m_gain;
    }

    /** Access m_yield
     * \param val New value to set
     */
    int yield()
    {
        return m_yield;
    }
    /** Set m_yield
     * \param val New value to set
     */
    void SetYield(int val)
    {
        m_yield = val;
    }

    /** Access m_speed
     * \param val New value to set
     */
    int speed()
    {
        return m_speed;
    }
    /** Set m_speed
     * \param val New value to set
     */
    void SetSpeed(int val)
    {
        m_speed = val;
    }

    /** Access m_pending
     * \return The current value of m_pending
     */
    bool isProcessed()
    {
        return (not m_pending);
    }
    bool isToBeProcessed()
    {
        return m_pending;
    }
    /** Set m_pending
     * \param val New value to set
     */
    void SetProcessed(bool val=true)
    {
        m_pending = (not val);
        if (m_pending == false)
        {
            m_yield = 0;
        }
    }
    void SetToBeProcessed(bool val=true)
    {
        m_pending = val;
        if (m_pending == false)
        {
            m_yield = 0;
        }
    }

    /** \brief Clear all subscription to wheel link
     *
     * \return void
     *
     */
	void unsubscribeAll()
	{
		m_subscriberList.clear();
	}

    /** \brief data is subscripter - it's linked to wheel when control mode is active
     * data est abonné - la variable est liée à celle de la roue quand le mode de contrôle est activé
     * \param data const int&
     * \return bool
     *
     */
	bool isSubscriber(const int &data);

    /** \brief unsubscipte data if is so - défait le lien entre la roue et data si le lien existe
     *
     * \param data const int&
     * \return bool (true if a subsciption did existe - vrai si un abonnement existait)
     *
     */
	bool unsubscribe(const int &data);

    /** \brief link data to wheel when control mode activeted - lien entre data et la roue quand le mode de contrôl est activé
     *
     * \param data int&
     * \param type const whc_wheeledcontrollertype slider or rotary
     * \param minimum const int (data can't be less than mininum ; if rotary from minimum pass to maximum)
     * \param maximum const int (data can't be more than maximum ; if rotary from maximum pass to minimum)
     * \param whc_mousewheelkey keypress défault is nokey (ctl key)
     * \return void
     *
     */
	void addSubscriber(int &data, const whc_wheeledcontrollertype type, const int minimum, const int maximum, whc_mousewheelkey keypress = nokey);

    /** \brief erase all subscription for data
     *
     * \param data const int&
     * \return void
     *
     */
	void pullSubscriber(const int &data);
	void handOverSubscriber(whc_mousewheelkey keypress = nokey);

protected:
private:
    int  m_level;	//!< Member variable m_level
    int  m_gain;	//!< Member variable m_gain (if event quickly catch, gain should be : -1,0, or +1)
    int  m_yield;   //!< Member variable m_yield (sum of gain until event processed : casual use)
    int  m_speed;	//!< Member variable m_speed
    bool m_pending; //!< Member variable "m_pending"
   	whc_mousewheel m_wheel;
   	std::vector<whc_wheeledcontroller>  m_subscriberList;
};


//---------------------------------------------------------------------------------------------------------------------------------------


class whc_mousePointer
{
public:
    typedef enum
    {
        arrow   = 0,
        arrow_down = 1,
        drag    = 2,
        target = 3,
        whc_mouselook_size = 4 // use to define array size : c_arrow[whc_mouselook_size]
    } whc_mouselook ;

    typedef struct
    {
        bool loaded;
        int mouse_x_in_png, mouse_y_in_png;
        ol::Bitmap bmp;
    } whc_pointerbmp;

    whc_pointerbmp static c_arrow[whc_mouselook_size];
    bool static c_Init(whc_mouselook idx,const char *pathtobmp);

    /** Default constructor */
    whc_mousePointer();
    whc_mousePointer(volatile int& mouse_x, volatile int& mouse_y);
    /** Default destructor */
    virtual ~whc_mousePointer();

    /** Access m_x
     * \param val New value to set
     */
    int x()
    {
        return m_x;
    }
    /** Set m_x
     * \param val New value to set
     */
    void SetX(int val)
    {
        m_x=val;
    }

    /** Access m_y
     * \param val New value to set
     */
    int y()
    {
        return m_y;
    }
    /** Set m_y
     * \param val New value to set
     */
    void SetY(int val)
    {
        m_y=val;
    }

    bool isOverRecSize(int x_left, int y_top, int x_size, int y_size)
    {
        return ((mouse_x>=x_left) and (mouse_x<=x_left+x_size) and (mouse_y>=y_top) and (mouse_y<=y_top+y_size));
    }

    bool isOverRecPos(int x_left, int y_top, int x_right, int y_bottom)
    {
        return ((mouse_x>=x_left) and (mouse_x<=x_right) and (mouse_y>=y_top) and (mouse_y<=y_bottom));
    }

    /** Set m_look
     * \param val New value to set
     */
    void SetLook(whc_mouselook val)
    {
        m_look=val;
    }

    /** Draw pointer
    */
    bool Draw();


    /** Set m_x m_y
     * \param val New value to set
     */
    void CollectEvent (volatile int& mouse_x, volatile int& mouse_y)
    {
        m_x = mouse_x;
        m_y = mouse_y;
    }

protected:
private:
    int  m_x;	//!< Member variable m_x
    int  m_y;	//!< Member variable m_y
    whc_mouselook m_look;
};

#endif // WHC_MOUSE_H
