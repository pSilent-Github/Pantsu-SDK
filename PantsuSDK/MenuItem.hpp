
#pragma once

/* Definitions */
#define CONSOLE_MAX 37
#include <string>

/* MenuItem_t */
struct MenuItem_t {
	std::string m_Name;

	union {
		float* m_Float;
		int* m_Int;
		bool* m_Bool;
	};

	float m_FloatStep;
	int m_IntStep;
	int m_Type;

	union {
		float m_FloatMin;
		int m_IntMin;
	};

	union {
		float m_FloatMax;
		int m_IntMax;
	};
};
