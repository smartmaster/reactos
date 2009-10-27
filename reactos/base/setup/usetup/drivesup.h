/*
 *  ReactOS kernel
 *  Copyright (C) 2002 ReactOS Team
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
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
/* $Id$
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS text-mode setup
 * FILE:            subsys/system/usetup/drivesup.h
 * PURPOSE:         Drive support functions
 * PROGRAMMER:      Eric Kohl
 */

#ifndef __DRIVESUP_H__
#define __DRIVESUP_H__

NTSTATUS
GetSourcePaths(PUNICODE_STRING SourcePath,
	       PUNICODE_STRING SourceRootPath,
	       PUNICODE_STRING SourceRootDir);

#endif /* __DRIVESUP_H__ */

/* EOF */
