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
#include "output.h"

#include "bitmacro.h"

extern unsigned char powerStatus;
extern unsigned char pwmDisco;
extern unsigned char pwmTurbina;

unsigned char countDisco;
unsigned char countTurbina;

void OutputInit( void )
{
    countDisco = 0;
    countTurbina = 0;
}

unsigned char OutputTurbina( unsigned char g )
{
    /* Control de la turbina */
    if(powerStatus == 0)
    {
        ResetBit(g, 0);
    }
    else
    {
        if(countTurbina <= pwmTurbina && pwmTurbina < 10)
        {
            ResetBit(g, 0);
        }
        else
        {
            SetBit(g, 0);
        }
        if(countTurbina == 10)
        {
            countTurbina = 0;
        }
        else
        {
            countTurbina++;
        }
    }
    return g;
}

unsigned char OutputDisco( unsigned char g )
{
    /* Control del disco */
    if(powerStatus == 0)
    {
        ResetBit(g, 1);
    }
    else
    {
        if(countDisco <= pwmDisco && pwmDisco < 10)
        {
            ResetBit(g, 1);
        }
        else
        {
            SetBit(g, 1);
        }
        if(countDisco == 10)
        {
            countDisco = 0;
        }
        else
        {
            countDisco++;
        }
    }
    return g;
}
