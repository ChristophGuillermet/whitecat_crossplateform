#ifndef WHC_WINDOW_H
#define WHC_WINDOW_H

#include <whc_graphicalObj.h>


class whc_window : public whc_graphicalObj
{
	public:
		whc_window(int Window_Id);
		virtual ~whc_window();

		bool isListening() { return m_IsListening; }
		void isListening(bool val) { m_IsListening = val; }

		bool hasFocus() { return m_hasFocus; }
		void hasFocus(bool val) { m_hasFocus = val; }

		bool isFlyedOver(int pos_x, int pos_y);

		//char[64]* title(){return &m_title;};
		//void title(char val[64]){m_title=val;};

		void Draw();

		void DrawChild ();

	protected:
	private:
		bool m_IsListening; //!< Member variable "m_isActive" - la fenêtre est à l'écoute des évenements
		int  m_window_ID; //!< Member variable "m_window_ID" - Identifiant de la fenêtre
		char m_title[64];
		bool m_hasFocus;

};

#endif // WHC_WINDOW_H
