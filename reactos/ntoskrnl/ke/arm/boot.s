/*
 * PROJECT:         ReactOS Kernel
 * LICENSE:         GPL - See COPYING in the top level directory
 * FILE:            ntoskrnl/ke/arm/boot.s
 * PURPOSE:         Implements the kernel entry point for ARM machines
 * PROGRAMMERS:     ReactOS Portable Systems Group
 */

    .title "ARM Kernel Entry Point"
    .include "ntoskrnl/include/internal/arm/kxarm.h"
    .include "ntoskrnl/include/internal/arm/ksarm.h"

    TEXTAREA
    NESTED_ENTRY KiSystemStartup
    PROLOG_END KiSystemStartup
    
    //
    // Do stuff!
    //
    b .
    
    ENTRY_END KiSystemStartup
