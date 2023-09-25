#pragma once

// TODO: Use an enum class instead
namespace Engine
{
    // Keyboard
    #define ENG_KEY_UNKNOWN            -1
    #define ENG_KEY_SPACE              32
    #define ENG_KEY_APOSTROPHE         39  /* ' */
    #define ENG_KEY_COMMA              44  /* , */
    #define ENG_KEY_MINUS              45  /* - */
    #define ENG_KEY_PERIOD             46  /* . */
    #define ENG_KEY_SLASH              47  /* / */
    #define ENG_KEY_0                  48
    #define ENG_KEY_1                  49
    #define ENG_KEY_2                  50
    #define ENG_KEY_3                  51
    #define ENG_KEY_4                  52
    #define ENG_KEY_5                  53
    #define ENG_KEY_6                  54
    #define ENG_KEY_7                  55
    #define ENG_KEY_8                  56
    #define ENG_KEY_9                  57
    #define ENG_KEY_SEMICOLON          59  /* ; */
    #define ENG_KEY_EQUAL              61  /* = */
    #define ENG_KEY_A                  65
    #define ENG_KEY_B                  66
    #define ENG_KEY_C                  67
    #define ENG_KEY_D                  68
    #define ENG_KEY_E                  69
    #define ENG_KEY_F                  70
    #define ENG_KEY_G                  71
    #define ENG_KEY_H                  72
    #define ENG_KEY_I                  73
    #define ENG_KEY_J                  74
    #define ENG_KEY_K                  75
    #define ENG_KEY_L                  76
    #define ENG_KEY_M                  77
    #define ENG_KEY_N                  78
    #define ENG_KEY_O                  79
    #define ENG_KEY_P                  80
    #define ENG_KEY_Q                  81
    #define ENG_KEY_R                  82
    #define ENG_KEY_S                  83
    #define ENG_KEY_T                  84
    #define ENG_KEY_U                  85
    #define ENG_KEY_V                  86
    #define ENG_KEY_W                  87
    #define ENG_KEY_X                  88
    #define ENG_KEY_Y                  89
    #define ENG_KEY_Z                  90
    #define ENG_KEY_LEFT_BRACKET       91  /* [ */
    #define ENG_KEY_BACKSLASH          92  /* \ */
    #define ENG_KEY_RIGHT_BRACKET      93  /* ] */
    #define ENG_KEY_GRAVE_ACCENT       96  /* ` */
    #define ENG_KEY_WORLD_1            161 /* non-US #1 */
    #define ENG_KEY_WORLD_2            162 /* non-US #2 */
    #define ENG_KEY_ESCAPE             256
    #define ENG_KEY_ENTER              257
    #define ENG_KEY_TAB                258
    #define ENG_KEY_BACKSPACE          259
    #define ENG_KEY_INSERT             260
    #define ENG_KEY_DELETE             261
    #define ENG_KEY_RIGHT              262
    #define ENG_KEY_LEFT               263
    #define ENG_KEY_DOWN               264
    #define ENG_KEY_UP                 265
    #define ENG_KEY_PAGE_UP            266
    #define ENG_KEY_PAGE_DOWN          267
    #define ENG_KEY_HOME               268
    #define ENG_KEY_END                269
    #define ENG_KEY_CAPS_LOCK          280
    #define ENG_KEY_SCROLL_LOCK        281
    #define ENG_KEY_NUM_LOCK           282
    #define ENG_KEY_PRINT_SCREEN       283
    #define ENG_KEY_PAUSE              284
    #define ENG_KEY_F1                 290
    #define ENG_KEY_F2                 291
    #define ENG_KEY_F3                 292
    #define ENG_KEY_F4                 293
    #define ENG_KEY_F5                 294
    #define ENG_KEY_F6                 295
    #define ENG_KEY_F7                 296
    #define ENG_KEY_F8                 297
    #define ENG_KEY_F9                 298
    #define ENG_KEY_F10                299
    #define ENG_KEY_F11                300
    #define ENG_KEY_F12                301
    #define ENG_KEY_F13                302
    #define ENG_KEY_F14                303
    #define ENG_KEY_F15                304
    #define ENG_KEY_F16                305
    #define ENG_KEY_F17                306
    #define ENG_KEY_F18                307
    #define ENG_KEY_F19                308
    #define ENG_KEY_F20                309
    #define ENG_KEY_F21                310
    #define ENG_KEY_F22                311
    #define ENG_KEY_F23                312
    #define ENG_KEY_F24                313
    #define ENG_KEY_F25                314
    #define ENG_KEY_KP_0               320
    #define ENG_KEY_KP_1               321
    #define ENG_KEY_KP_2               322
    #define ENG_KEY_KP_3               323
    #define ENG_KEY_KP_4               324
    #define ENG_KEY_KP_5               325
    #define ENG_KEY_KP_6               326
    #define ENG_KEY_KP_7               327
    #define ENG_KEY_KP_8               328
    #define ENG_KEY_KP_9               329
    #define ENG_KEY_KP_DECIMAL         330
    #define ENG_KEY_KP_DIVIDE          331
    #define ENG_KEY_KP_MULTIPLY        332
    #define ENG_KEY_KP_SUBTRACT        333
    #define ENG_KEY_KP_ADD             334
    #define ENG_KEY_KP_ENTER           335
    #define ENG_KEY_KP_EQUAL           336
    #define ENG_KEY_LEFT_SHIFT         340
    #define ENG_KEY_LEFT_CONTROL       341
    #define ENG_KEY_LEFT_ALT           342
    #define ENG_KEY_LEFT_SUPER         343
    #define ENG_KEY_RIGHT_SHIFT        344
    #define ENG_KEY_RIGHT_CONTROL      345
    #define ENG_KEY_RIGHT_ALT          346
    #define ENG_KEY_RIGHT_SUPER        347
    #define ENG_KEY_MENU               348
    #define ENG_KEY_LAST               ENG_KEY_MENU

    // Mouse
    #define ENG_MOUSE_BUTTON_1         0
    #define ENG_MOUSE_BUTTON_2         1
    #define ENG_MOUSE_BUTTON_3         2
    #define ENG_MOUSE_BUTTON_4         3
    #define ENG_MOUSE_BUTTON_5         4
    #define ENG_MOUSE_BUTTON_6         5
    #define ENG_MOUSE_BUTTON_7         6
    #define ENG_MOUSE_BUTTON_8         7
    #define ENG_MOUSE_BUTTON_LAST      ENG_MOUSE_BUTTON_8
    #define ENG_MOUSE_BUTTON_LEFT      ENG_MOUSE_BUTTON_1
    #define ENG_MOUSE_BUTTON_RIGHT     ENG_MOUSE_BUTTON_2
    #define ENG_MOUSE_BUTTON_MIDDLE    ENG_MOUSE_BUTTON_3
}