/**
 * \file VNC_config.h
 * \brief Contains compile-time configuration "knobs" for the VNC server
 *
 * \version		1.3.1
 * \date		March 2020
 * \author		Gerad Munsch <gmunsch@unforgivendevelopment.com>
 * \date		07.01.2016
 * \author		Markus Sattler
 *
 * \copyright \parblock
 * Copyright (c) 2015 Markus Sattler. All rights reserved.
 * This file is part of the VNC client for Arduino.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, a copy can be downloaded from
 * http://www.gnu.org/licenses/gpl.html, or obtained by writing to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 * \endparblock
 */

#ifndef VNC_CONFIG_H_
#define VNC_CONFIG_H_



/// Display
#define VNC_ILI9341

// RA8875 not fully implemented
//#define VNC_RA8875


#if !defined(VNC_ILI9341) && !defined(VNC_RA8875)
#error 'At least one display device must be defined at the time of preprocessing: VNC_ILI9341 or VNC_RA8875'
#elif defined(VNC_ILI9341) && defined(VNC_RA8875)
#error 'Only one display device may be defined at the time of preprocessing.'

#elif defined(VNC_ILI9341)

#define VNC_DISPLAY VNC_ILI9341

#elif defined(VNC_RA8875)

#warning 'There are still some known issues with the RA8875 display; use of the ILI9341 is recommended.'

#define VNC_DISPLAY VNC_RA8875

#else

#error 'Unknown error while trying to set VNC display!'

#endif


/// TCP layer
#define USE_ARDUINO_TCP
#define VNC_TCP_TIMEOUT 5000

/// VNC Encodes
#define VNC_RRE
#define VNC_CORRE
#define VNC_HEXTILE

// not implemented
//#define VNC_TIGHT
//#define VNC_ZLIB
//#define VNC_RICH_CURSOR
//#define VNC_SEC_TYPE_TIGHT

/// Buffers
#define VNC_FRAMEBUFFER

/// Testing
//#define FPS_BENCHMARK
//#define FPS_BENCHMARK_FULL

//#define SLOW_LOOP 250

/// Memory Options
//#define VNC_SAVE_MEMORY

#ifndef VNC_SAVE_MEMORY
// 15KB raw input buffer
#define VNC_RAW_BUFFER 15360
#endif


/**
 * \name Textual Debug Prints
 *
 * We make use of platform-specific preprocesor definitions here to ensure that the debug prints are routed to the ideal
 * output device for a given platform.
 *
 * @{
 */

#ifdef ESP32

/**
 * \brief Prints a text string for the purpose of debugging the VNC server on the ESP32 platform
 *
 * \param[in]	...		Utilizes the same syntax as the standard \c printf() function
 */
#define DEBUG_VNC(...) Serial.printf(__VA_ARGS__)

#else	/* ESP32 */

#ifdef DEBUG_ESP_PORT

/**
 * \brief Prints a text string for the purpose of debugging the VNC server on the certain ESP platforms
 *
 * \param[in]	...		Utilizes the same syntax as the standard \c printf() function
 */
#define DEBUG_VNC(...) DEBUG_ESP_PORT.printf(__VA_ARGS__)

#else	/* DEBUG_ESP_PORT */

/**
 * \brief Prints a text string for the purpose of debugging the VNC server utilizing the OS-level printf function
 *
 * The argument to \c DEBUG_VNC() is passwd along to the argument of the \c os_printf() function
 *
 * \param[in]	...		Utilizes the same syntax as the standard \c printf() function
 */
#define DEBUG_VNC(...) os_printf(__VA_ARGS__)

#endif	/* !DEBUG_ESP_PORT */
#endif	/* !ESP32 */


/**
 * \name Additional debug print macrosa
 *
 * These empty macros facilitate debug prints from other components of the VNC server.
 *
 * \note The code, as elaborated below, will cause debug prints to be discarded. Checks for the availablity of the base
 *       \c DEBUG_VNC(...) macro is tested for functionality later on; these macros utilize that base-level macro as to
 *       perform their duties.
 *
 * @{
 */

#define DEBUG_VNC_RAW(...)
#define DEBUG_VNC_HEXTILE(...)
#define DEBUG_VNC_RICH_CURSOR(...)

/**
 * @}
 */


#if !defined(DEBUG_VNC) || defined(__DOXYGEN__)
/* \brief This macro checks for the availablity of a functional \c DEBUG_VNC(...) macro; lacking such, discard msgs */
#define DEBUG_VNC(...)
#endif


/**
 * \name Finer-grained debug output macros
 *
 * @{
 */

#ifndef DEBUG_VNC_RAW
#define DEBUG_VNC_RAW(...) DEBUG_VNC( __VA_ARGS__ )
#endif

#ifndef DEBUG_VNC_HEXTILE
#define DEBUG_VNC_HEXTILE(...) DEBUG_VNC( __VA_ARGS__ )
#endif

#ifndef DEBUG_VNC_RICH_CURSOR
#define DEBUG_VNC_RICH_CURSOR(...) DEBUG_VNC( __VA_ARGS__ )
#endif

/**
 * @}
 */

/**
 * @}
 */

#endif	/* !VNC_CONFIG_H_ */
