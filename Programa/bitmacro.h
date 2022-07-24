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
#ifndef BITMACRO_H
#define	BITMACRO_H

#define SetBit(p, b) ( p |= (0b00000001 << b) )
#define ResetBit(p, b) ( p &= ((0b00000001 << b)^0xff) )
#define InvertBit(p, b) ( p ^= (0b00000001 << b) )
#define IsBit(p, b) ( p & (0b00000001 << b) )

#endif	/* BITMACRO_H */

