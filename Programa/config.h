/***************************************************************************
    Copyright (C) 2018   Walter Pirri

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***************************************************************************/
#ifndef CONFIG_H
#define	CONFIG_H

#define _XTAL_FREQ 4000000 /* Para las funciones de Delay */
#define GetInstructionClock() (_XTAL_FREQ/4)
#define GetPeripheralClock() (_XTAL_FREQ/4)

#define SENSIBILIDAD_BOTON 100

#define SERVO1_OUT  0
#define SERVO1_MAX  11
#define SERVO1_MIN  7
#define SERVO1_INIT 7
#define SERVO1_STEP 1

#define SERVO2_OUT  1
#define SERVO2_MAX  78
#define SERVO2_MIN  26
#define SERVO2_INIT 52
#define SERVO2_STEP 13


#define SHADOW_REG gShadow
#define INPUT_PORT GPIO
#define OUTPUT_PORT GPIO

#endif	/* CONFIG_H */

