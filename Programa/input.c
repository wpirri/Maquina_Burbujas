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
#include "input.h"

#include "bitmacro.h"

#define BOTON_DELAY 500

unsigned char btnDiscoUp;
unsigned char btnDiscoDown;
unsigned char btnTurbinaUp;
unsigned char btnTurbinaDown;

unsigned int contDelayBtnDiscoUp;
unsigned int contDelayBtnTurbinaUp;
unsigned int contDelayBtnDiscoDown;
unsigned int contDelayBtnTurbinaDown;

extern unsigned char pwmDisco;
extern unsigned char pwmTurbina;

void ControlBotonInit(void)
{
    contDelayBtnDiscoUp = BOTON_DELAY/2;
    contDelayBtnTurbinaUp = BOTON_DELAY/2;
    contDelayBtnDiscoDown = BOTON_DELAY/2;
    contDelayBtnTurbinaDown = BOTON_DELAY/2;
    btnDiscoUp = 0;
    btnDiscoDown = 0;
    btnTurbinaUp = 0;
    btnTurbinaDown = 0;
}

void ControlBoton1( void )
{
    /* Control de los botones */
    /* Boton 1 - GP5 - Vent + */
    if( !GPIObits.GP5)
    {
        /* Filtro de ruido */
        if(contDelayBtnTurbinaUp < BOTON_DELAY)
        {
            contDelayBtnTurbinaUp++;
            if(contDelayBtnTurbinaUp == BOTON_DELAY)
            {
                /* Anti rebote */
                if( !btnTurbinaUp)
                {
                    btnTurbinaUp = 1;                       
                    if(pwmTurbina < 10) pwmTurbina++;
                }
            }
        }
    }
    else if(contDelayBtnTurbinaUp > 0)
    {
        contDelayBtnTurbinaUp--;
        if(contDelayBtnTurbinaUp == 0)
        {
            btnTurbinaUp = 0;                       
        }
    }
}

void ControlBoton2( void )
{
    /* Boton 2 - GP4 - Vent - */
    if( !GPIObits.GP4)
    {
        /* Filtro de ruido */
        if(contDelayBtnTurbinaDown < BOTON_DELAY)
        {
            contDelayBtnTurbinaDown++;
            if(contDelayBtnTurbinaDown == BOTON_DELAY)
            {
                /* Anti rebote */
                if( !btnTurbinaDown)
                {
                    btnTurbinaDown = 1;                       
                    if(pwmTurbina > 0) pwmTurbina--;
                }
            }
        }
    }
    else if(contDelayBtnTurbinaDown > 0)
    {
        contDelayBtnTurbinaDown--;
        if(contDelayBtnTurbinaDown == 0)
        {
            btnTurbinaDown = 0;                       
        }
    }
}

void ControlBoton3( void )
{
    /* Boton 3 - GP3 - Disco + */
    if( !GPIObits.GP3)
    {
        /* Filtro de ruido */
        if(contDelayBtnDiscoUp < BOTON_DELAY)
        {
            contDelayBtnDiscoUp++;
            if(contDelayBtnDiscoUp == BOTON_DELAY)
            {
                /* Anti rebote */
                if( !btnDiscoUp)
                {
                    btnDiscoUp = 1;                       
                    if(pwmDisco < 10) pwmDisco++;
                }
            }
        }
    }
    else if(contDelayBtnDiscoUp > 0)
    {
        contDelayBtnDiscoUp--;
        if(contDelayBtnDiscoUp == 0)
        {
            btnDiscoUp = 0;                       
        }
    }
}

void ControlBoton4( void )
{
    /* Boton 4 - GP2 - Disco - */
    if( !GPIObits.GP2)
    {
        /* Filtro de ruido */
        if(contDelayBtnDiscoDown < BOTON_DELAY)
        {
            contDelayBtnDiscoDown++;
            if(contDelayBtnDiscoDown == BOTON_DELAY)
            {
                /* Anti rebote */
                if( !btnDiscoDown)
                {
                    btnDiscoDown = 1;                       
                    if(pwmDisco > 0) pwmDisco--;
                }
            }
        }
    }
    else if(contDelayBtnDiscoDown > 0)
    {
        contDelayBtnDiscoDown--;
        if(contDelayBtnDiscoDown == 0)
        {
            btnDiscoDown = 0;                       
        }
    }
}
