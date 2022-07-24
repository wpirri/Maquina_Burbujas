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
#ifndef PERIF_H
#define	PERIF_H

/* Define I/O */
#define BOTON1  5
#define BOTON2  4
#define BOTON3  3
#define BOTON4  2

/* Define flags */
#define BTN1    0x01
#define BTN2    0x02
#define BTN3    0x04
#define BTN4    0x08

#define IS_BTN1( x ) ( x & BTN1 )
#define IS_BTN2( x ) ( x & BTN2 )
#define IS_BTN3( x ) ( x & BTN3 )
#define IS_BTN4( x ) ( x & BTN4 )

void InitPerif( void );

unsigned char CheckBtn(void);

#endif	/* PERIF_H */

