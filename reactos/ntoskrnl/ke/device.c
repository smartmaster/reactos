/* $Id: device.c,v 1.5 2004/10/22 20:07:13 navaraf Exp $
 *
 * FILE:            ntoskrnl/ke/profile.c
 * PURPOSE:         Kernel Device/Settings Functions
 * PROGRAMMER:      Alex Ionescu (alex@relsoft.net)
 * UPDATE HISTORY:
 *                  Created 23/06/04
 */

#include <ntoskrnl.h>
#define NDEBUG
#include <internal/debug.h>

/*
 * @implemented
 */
STDCALL
PVOID
KeFindConfigurationEntry(
    IN PVOID Unknown,
    IN ULONG Class,
    IN CONFIGURATION_TYPE Type,
    IN PULONG RegKey
)
{
	/* Start Search at Root */
	return KeFindConfigurationNextEntry(Unknown, Class, Type, RegKey, NULL);
}

/*
 * @unimplemented
 */
STDCALL
PVOID
KeFindConfigurationNextEntry(
    IN PVOID Unknown,
    IN ULONG Class,
    IN CONFIGURATION_TYPE Type,
    IN PULONG RegKey,
    IN PVOID *NextLink
)
{
	UNIMPLEMENTED;
	return 0;
}

/*
 * @implemented
 */
STDCALL
VOID
KeFlushEntireTb(
    IN BOOLEAN Unknown,
    IN BOOLEAN CurrentCpuOnly
)
{
	KIRQL OldIrql;
	PKPROCESS Process = NULL;
	PKPCR Pcr = NULL;
	
	/* Raise the IRQL for the TB Flush */
	OldIrql = KeRaiseIrqlToSynchLevel();
	
	/* All CPUs need to have the TB flushed. */
	if (CurrentCpuOnly == FALSE) {
		Pcr = KeGetCurrentKPCR();
		
		/* How many CPUs is our caller using? */
		Process = Pcr->PrcbData.CurrentThread->ApcState.Process;
		
		/* More then one, so send an IPI */
		if (Process->ActiveProcessors > 1) {
			/* Send IPI Packet */
		}
	}
	
	/* Flush the TB for the Current CPU */
	KeFlushCurrentTb();
	
	/* Clean up */
	if (CurrentCpuOnly == FALSE) {
		/* Did we send an IPI? If so, wait for completion */
		if (Process->ActiveProcessors > 1) {
			do {
			} while (Pcr->PrcbData.TargetSet != 0);
		} 
	} 
	
	/* FIXME: According to MSKB, we should increment a counter? */
	
	/* Return to Original IRQL */	
	KeLowerIrql(OldIrql);
}


/*
 * @implemented
 */
STDCALL
VOID
KeSetDmaIoCoherency(
    IN ULONG Coherency
)
{
	KiDmaIoCoherency = Coherency;
}

/*
 * @unimplemented
 */
STDCALL
PKDEVICE_QUEUE_ENTRY
KeRemoveByKeyDeviceQueueIfBusy (
    IN PKDEVICE_QUEUE DeviceQueue,
    IN ULONG SortKey
    )
{
	UNIMPLEMENTED;
	return 0;
}

/*
 * @implemented
 */
STDCALL
KAFFINITY
KeQueryActiveProcessors (
    VOID
    )
{
	return KeActiveProcessors;
}


/*
 * @unimplemented
 */
VOID
__cdecl
KeSaveStateForHibernate(
    IN PVOID State
)
{
	UNIMPLEMENTED;
}
