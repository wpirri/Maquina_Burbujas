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
#include <stdio.h>
#include <stdlib.h>

#include <xc.h>

#include "perif.h"
#include "config.h"
#include "bitmacro.h"

unsigned char gShadow;

/* *************************************************************************** *
 * Globales
 */
unsigned int ContBtn1Delay;
unsigned int ContBtn2Delay;
unsigned int ContBtn3Delay;
unsigned int ContBtn4Delay;
unsigned char StatusBtn;

void InitPerif( void )
{
    ContBtn1Delay = SENSIBILIDAD_BOTON / 2;
    ContBtn2Delay = SENSIBILIDAD_BOTON / 2;
    ContBtn3Delay = SENSIBILIDAD_BOTON / 2;
    ContBtn4Delay = SENSIBILIDAD_BOTON / 2;
    StatusBtn = 0;
}

unsigned char CheckBtn(void)
{
    if( !IsBit(INPUT_PORT, BOTON1) )
    {
        if( ContBtn1Delay < SENSIBILIDAD_BOTON )
        {
            ContBtn1Delay++;
            if( ContBtn1Delay == SENSIBILIDAD_BOTON )
            {
                /* Boton presionado */
                StatusBtn |= BTN1;
            }
        }
    }
    else
    {
        if( ContBtn1Delay > 0 )
        {
            ContBtn1Delay--;
            if( ContBtn1Delay == 0 )
            {
                /* Boton suelto */
                StatusBtn &= (BTN1^0xFF);
            }
        }
    }

    if( !IsBit(INPUT_PORT, BOTON2) )
    {
        if( ContBtn2Delay < SENSIBILIDAD_BOTON )
        {
            ContBtn2Delay++;
            if( ContBtn2Delay == SENSIBILIDAD_BOTON )
            {
                /* Boton presionado */
                StatusBtn |= BTN2;
            }
        }
    }
    else
    {
        if( ContBtn2Delay > 0 )
        {
            ContBtn2Delay--;
            if( ContBtn2Delay == 0 )
            {
                /* Boton suelto */
                StatusBtn &= (BTN2^0xFF);
            }
        }
    }

    if( !IsBit(INPUT_PORT, BOTON3) )
    {
        if( ContBtn3Delay < SENSIBILIDAD_BOTON )
        {
            ContBtn3Delay++;
            if( ContBtn3Delay == SENSIBILIDAD_BOTON )
            {
                /* Boton presionado */
                StatusBtn |= BTN3;
            }
        }
    }
    else
    {
        if( ContBtn3Delay > 0 )
        {
            ContBtn3Delay--;
            if( ContBtn3Delay == 0 )
            {
                /* Boton suelto */
                StatusBtn &= (BTN3^0xFF);
            }
        }
    }

    if( !IsBit(INPUT_PORT, BOTON4) )
    {
        if( ContBtn4Delay < SENSIBILIDAD_BOTON )
        {
            ContBtn4Delay++;
            if( ContBtn4Delay == SENSIBILIDAD_BOTON )
            {
                /* Boton presionado */
                StatusBtn |= BTN4;
            }
        }
    }
    else
    {
        if( ContBtn4Delay > 0 )
        {
            ContBtn4Delay--;
            if( ContBtn4Delay == 0 )
            {
                /* Boton suelto */
                StatusBtn &= (BTN4^0xFF);
            }
        }
    }

    return StatusBtn;
}
