#pragma once

#include <cstdint>

//Emum for all input

enum EButtonKeys : uint8_t
{
	Mouse_Left = 0,
	Mouse_Right = 1,
	Mouse_Middle = 3,
	Mouse_None = 4,

	Mouse_Max = 5
};

enum EKeyboardKeys : uint8_t
{
	// Letter
	Key_A = 0,
	Key_B = 1,
	Key_C = 2,
	Key_D = 3,
	Key_E = 4,
	Key_F = 5,
	Key_G = 6,
	Key_H = 7,
	Key_I = 8,
	Key_J = 9,
	Key_K = 10,
	Key_L = 11,
	Key_M = 12,
	Key_N = 13,
	Key_O = 14,
	Key_P = 15,
	Key_Q = 16,
	Key_R = 17,
	Key_S = 18,
	Key_T = 19,
	Key_U = 20,
	Key_V = 21,
	Key_W = 22,
	Key_X = 23,
	Key_Y = 24,
	Key_Z = 25,

	// Number
	Key_0 = 26,
	Key_1 = 27,
	Key_2 = 28,
	Key_3 = 29,
	Key_4 = 30,
	Key_5 = 31,
	Key_6 = 32,
	Key_7 = 33,
	Key_8 = 34,
	Key_9 = 35,

	// F Key
	Key_F1 = 36,
	Key_F2 = 37,
	Key_F3 = 38,
	Key_F4 = 39,
	Key_F5 = 40,
	Key_F6 = 41,
	Key_F7 = 42,
	Key_F8 = 43,
	Key_F9 = 44,
	Key_F10 = 45,
	Key_F11 = 46,
	Key_F12 = 47,

	// Modifier keys and more
	Key_Shift = 48,
	Key_Control = 49,
	Key_Alt = 50,
	Key_Space = 51,
	Key_Enter = 52,
	Key_Backspace = 53,
	Key_Tab = 54,
	Key_Escape = 55,
	Key_CapsLock = 56,
	Key_NumLock = 57,
	Key_ScrollLock = 58,

	// Direction keys
	Key_UpArrow = 59,
	Key_DownArrow = 60,
	Key_LeftArrow = 61,
	Key_RightArrow = 62,

	// Numeric keypad keys
	Key_Numpad0 = 63,
	Key_Numpad1 = 64,
	Key_Numpad2 = 65,
	Key_Numpad3 = 66,
	Key_Numpad4 = 67,
	Key_Numpad5 = 68,
	Key_Numpad6 = 69,
	Key_Numpad7 = 70,
	Key_Numpad8 = 71,
	Key_Numpad9 = 72,
	Key_NumpadMultiply = 73,
	Key_NumpadAdd = 74,
	Key_NumpadSubtract = 75,
	Key_NumpadDecimal = 76,
	Key_NumpadDivide = 77,

	//End enum
	Key_None = 78,
	Key_Max = 79
};