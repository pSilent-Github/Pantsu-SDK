
#include "Includes.hpp"
#include "render.h"

CMenu* g_pMenu;


MenuItem_t Items[120];
bool m_bLegitBotTab = false;
bool m_bRageBotTab = false;
bool m_bVisualsTab = false;
bool m_bMiscTab = false;
bool m_bHvHTab = false;
bool m_bColorTab = false;
int m_iTotalItems = 0, m_iCurrentPos = 0, m_iMenuX = 350, m_iMenuY = 350;


int AddMenuEntry(int n, std::string sName, bool* bValue) {
	Items[n].m_Name = sName;
	Items[n].m_Bool = bValue;
	Items[n].m_Type = 0;
	return (n + 1);
}

int AddMenuEntry(int n, std::string sName, int* iValue, int iMin, int iMax, int iStep) {
	Items[n].m_Name = sName;
	Items[n].m_Int = iValue;
	Items[n].m_IntMin = iMin;
	Items[n].m_IntMax = iMax;
	Items[n].m_IntStep = iStep;
	Items[n].m_Type = 1;
	return (n + 1);
}


int AddMenuEntry(int n, std::string sName, float* flValue, float flMin, float flMax, float flStep) {
	Items[n].m_Name = sName;
	Items[n].m_Float = flValue;
	Items[n].m_FloatMin = flMin;
	Items[n].m_FloatMax = flMax;
	Items[n].m_FloatStep = flStep;
	Items[n].m_Type = 2;
	return (n + 1);
}


void CMenu::InsertMenuItems() {

	int i = 0;

		i = AddMenuEntry(i, "ESP", &Settings::m_bESP);
		i = AddMenuEntry(i, "Bunnyhop", &Settings::m_bAutoHop);
	
	

	m_iTotalItems = i;

}

/* DrawMenu */
void CMenu::DrawMenu() {

	// FontSize 
	int FontSize = 14;
	Render->DrawInlineRect(m_iMenuX - 5, m_iMenuY + (FontSize * m_iCurrentPos) + 3, 190, FontSize + 2, CColor(123, 123, 123, 220));

	for (int i = 0; i < m_iTotalItems; ++i) {

		if (!strncmp(Items[i].m_Name.c_str(), "[+]", 3))
		{
			Render->DrawFAlt(m_iMenuX, m_iMenuY + 2 + (FontSize * i) + 4, CColor(255, 255, 255, 255), 5, false, Items[i].m_Name.c_str());
		}

		else if (!strncmp(Items[i].m_Name.c_str(), "[-]", 3))
		{
			Render->DrawFAlt(m_iMenuX, m_iMenuY + 2 + (FontSize * i) + 4, CColor(255, 255, 255, 255), 5, false, Items[i].m_Name.c_str());
		}

		else {

			switch (Items[i].m_Type) {
			case 0:
				Render->DrawFAlt(m_iMenuX, m_iMenuY + 2 + (FontSize * i) + 4, CColor(255, 255, 255, 255), 5, false, Items[i].m_Name.c_str());
				Render->DrawF(m_iMenuX + 150, m_iMenuY + 2 + (FontSize * i) + 4, CColor(255, 255, 255, 255), 5, false, "%s", (*Items[i].m_Bool) ? "true" : "false");
				break;
			case 1:
				Render->DrawFAlt(m_iMenuX, m_iMenuY + 2 + (FontSize * i) + 4, CColor(255, 255, 255, 255), 5, false, Items[i].m_Name.c_str());
				Render->DrawF(m_iMenuX + 150, m_iMenuY + 2 + (FontSize * i) + 4, CColor(255, 255, 255, 255), 5, false, "%i", *Items[i].m_Int);
				break;
			case 2:
				Render->DrawFAlt(m_iMenuX, m_iMenuY + 2 + (FontSize * i) + 4, CColor(255, 255, 255, 255), 5, false, Items[i].m_Name.c_str());
				Render->DrawF(m_iMenuX + 150, m_iMenuY + 2 + (FontSize * i) + 4, CColor(255, 255, 255, 255), 5, false, "%.2f", *Items[i].m_Float);
				break;
			default:
				break;
			}
		}
	}

	if (GetAsyncKeyState(VK_UP) & 1) {
		if (m_iCurrentPos > 0)
			m_iCurrentPos--;
		else
			m_iCurrentPos = m_iTotalItems - 1;
	}

	else if (GetAsyncKeyState(VK_DOWN) & 1) {
		if (m_iCurrentPos < m_iTotalItems - 1)
			m_iCurrentPos++;
		else
			m_iCurrentPos = 0;
	}

	else if (GetAsyncKeyState(VK_LEFT) & 1) {
		switch (Items[m_iCurrentPos].m_Type) {
		case 0:
			*Items[m_iCurrentPos].m_Bool = !*Items[m_iCurrentPos].m_Bool;
			break;
		case 1:
			*Items[m_iCurrentPos].m_Int -= Items[m_iCurrentPos].m_IntStep;
			if (*Items[m_iCurrentPos].m_Int < Items[m_iCurrentPos].m_IntMin)
				*Items[m_iCurrentPos].m_Int = Items[m_iCurrentPos].m_IntMax;
			break;
		case 2:
			*Items[m_iCurrentPos].m_Float -= Items[m_iCurrentPos].m_FloatStep;
			if (*Items[m_iCurrentPos].m_Float < Items[m_iCurrentPos].m_FloatMin)
				*Items[m_iCurrentPos].m_Float = Items[m_iCurrentPos].m_FloatMax;
			break;
		default:
			break;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 1) {
		switch (Items[m_iCurrentPos].m_Type) {
		case 0:
			*Items[m_iCurrentPos].m_Bool = !*Items[m_iCurrentPos].m_Bool;
			break;
		case 1:
			*Items[m_iCurrentPos].m_Int += Items[m_iCurrentPos].m_IntStep;
			if (*Items[m_iCurrentPos].m_Int > Items[m_iCurrentPos].m_IntMax)
				*Items[m_iCurrentPos].m_Int = Items[m_iCurrentPos].m_IntMin;
			break;
		case 2:
			*Items[m_iCurrentPos].m_Float += Items[m_iCurrentPos].m_FloatStep;
			if (*Items[m_iCurrentPos].m_Float > Items[m_iCurrentPos].m_FloatMax)
				*Items[m_iCurrentPos].m_Float = Items[m_iCurrentPos].m_FloatMin;
			break;
		default:
			break;
		}
	}
}