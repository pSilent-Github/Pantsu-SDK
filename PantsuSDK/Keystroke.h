/* Paper-Key-Stroke */
#pragma once
#include "Includes.hpp"
/* KeyStroke */
typedef struct {
	char szDef[5];
	char szShiftDef[5];
	char szAltDef[5];
}KeyStroke_t;
extern KeyStroke_t m_KeyStroke[KEY_MAX];
