/*
 *  FreeLoader
 *  Copyright (C) 1998-2002  Brian Palmer  <brianp@sginet.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <freeldr.h>
#include <disk.h>
#include <rtl.h>
#include <mm.h>


BOOL DiskGetDriveGeometry(ULONG DriveNumber, PGEOMETRY DriveGeometry)
{
	// For now just return the geometry as the BIOS reports it
	// BytesPerSector is always set to 512 by BiosInt13GetDriveParameters()
	if (!BiosInt13GetDriveParameters(DriveNumber, DriveGeometry))
	{
		DiskError("Drive geometry unknown.");
		return FALSE;
	}

	return TRUE;
}
