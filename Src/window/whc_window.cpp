#include "whc_window.h"
static Rgba CouleurFond;
static Rgba CouleurFader;
static Rgba CouleurLigne;
static TextRenderer neuro;

whc_window::whc_window(int Window_Id)
{
	//ctor
	m_window_ID = Window_Id;
	//pourrait avoir une fonction statique + liste statique pour s'assurer que c'est un identifiant unique

	m_IsListening = false ;
	m_IsVisible = false ;
}

whc_window::~whc_window()
{
	//dtor
}

bool whc_window::isFlyedOver(int pos_x, int pos_y)
{
	//périmètre d'un carré/rectangle orienté selon les axes de l'écran
	if ((pos_x >= m_OnScreenPos_x) && (pos_x <= m_OnScreenPos_x + m_size_x)
	  &&(pos_y >= m_OnScreenPos_y) && (pos_y <= m_OnScreenPos_y + m_size_y))
	{
		return true;
	}
}

void whc_window::Draw()
{

    m_IsVisible = true; //the fact is that we are drawing it now !


//la fenêtre en elle même: un rectangle
    Rect windowFrame(Vec2D(m_OnScreenPos_x,m_OnScreenPos_y),
                     Vec2D( m_size_x,m_size_y));
//facteur d'arrondissement du rectangle
    windowFrame.SetRoundness(15);
    float double_epaisseur_ligne_fader=2.0*2;
    windowFrame.SetLineWidth(double_epaisseur_ligne_fader);
//fond
    windowFrame.Draw(CouleurFond);
//pourtour
    if(m_hasFocus)//si elle est sélectionnée bord orange
    {
        windowFrame.DrawOutline(CouleurFader);
    }
    else
    {
        windowFrame.DrawOutline(CouleurLigne);
    }
    neuro.Print( m_title,
                 m_OnScreenPos_x+250,
                 m_OnScreenPos_y+10);

//position des boutons Move/Close
    /*MoveCloseBox( m_OnScreenPos_x+10,
                  m_OnScreenPos_y+10,
                  m_window_ID);
*/

	DrawChild ();
}

void whc_window::DrawChild()
{

}
