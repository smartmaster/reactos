#include <windows.h>
#include <ddk/ntddk.h>
#include <ddk/ntddbeep.h>

// #define NDEBUG
#include <kernel32/kernel32.h>


static DWORD LastError=0;

DWORD RtlNtStatusToDosError(NTSTATUS Status)
{
   switch (Status)
   {
      case STATUS_SUCCESS:
         return NO_ERROR;

      case STATUS_NOT_IMPLEMENTED:
      case STATUS_ILLEGAL_FUNCTION:
      case STATUS_INVALID_DEVICE_REQUEST:
      case STATUS_INVALID_SYSTEM_SERVICE:
         return ERROR_INVALID_FUNCTION;

      case STATUS_NO_SUCH_DEVICE:
      case STATUS_NO_SUCH_FILE:
      case STATUS_OBJECT_NAME_NOT_FOUND:
         return ERROR_FILE_NOT_FOUND;

      case STATUS_OBJECT_PATH_NOT_FOUND:
      case STATUS_DFS_EXIT_PATH_FOUND:
         return ERROR_PATH_NOT_FOUND;

      case STATUS_TOO_MANY_OPENED_FILES:
         return ERROR_TOO_MANY_OPEN_FILES;

      case STATUS_THREAD_IS_TERMINATING:
      case STATUS_PROCESS_IS_TERMINATING:
      case STATUS_INVALID_LOCK_SEQUENCE:
      case STATUS_INVALID_VIEW_SIZE:
      case STATUS_ALREADY_COMMITTED:
      case STATUS_ACCESS_DENIED:
      case STATUS_FILE_IS_A_DIRECTORY:
      case STATUS_CANNOT_DELETE:
      case STATUS_FILE_DELETED:
      case STATUS_DELETE_PENDING:
      case STATUS_PORT_CONNECTION_REFUSED:
         return ERROR_ACCESS_DENIED;

      case STATUS_HANDLE_NOT_WAITABLE:
      case STATUS_PORT_DISCONNECTED:
      case RPC_NT_SS_IN_NULL_CONTEXT:
      case RPC_NT_INVALID_BINDING:
      case STATUS_INVALID_HANDLE:
      case STATUS_OBJECT_TYPE_MISMATCH:
      case STATUS_FILE_CLOSED:
      case STATUS_INVALID_PORT_HANDLE:
         return ERROR_INVALID_HANDLE;

      /* ERROR_ARENA_TRASHED */

      case STATUS_PAGEFILE_QUOTA:
      case STATUS_COMMITMENT_LIMIT:
      case STATUS_SECTION_TOO_BIG:
      case STATUS_WORKING_SET_QUOTA:
      case STATUS_NO_MEMORY:
      case STATUS_CONFLICTING_ADDRESSES:
      case STATUS_TOO_MANY_PAGING_FILES:
      case STATUS_INSUFFICIENT_RESOURCES:
         return ERROR_NOT_ENOUGH_MEMORY;


      case STATUS_SECTION_NOT_EXTENDED:
         return ERROR_OUTOFMEMORY;

      case STATUS_NOT_SAME_DEVICE:
         return ERROR_NOT_SAME_DEVICE;

      case STATUS_NO_MORE_FILES:
         return ERROR_NO_MORE_FILES;

      case STATUS_MEDIA_WRITE_PROTECTED:
      case STATUS_TOO_LATE:
         return ERROR_WRITE_PROTECT;

      case STATUS_NO_MEDIA_IN_DEVICE:
      case STATUS_DEVICE_POWERED_OFF:
      case STATUS_DEVICE_OFF_LINE:
      case STATUS_DEVICE_NOT_READY:
      case STATUS_DEVICE_NOT_CONNECTED:
      case STATUS_DEVICE_POWER_FAILURE:
         return ERROR_NOT_READY;

      case STATUS_INVALID_DEVICE_STATE:
         return ERROR_BAD_COMMAND;

      case STATUS_DATA_ERROR:
      case STATUS_CRC_ERROR:
      case STATUS_DEVICE_DATA_ERROR:
         return ERROR_CRC;

      case STATUS_INFO_LENGTH_MISMATCH:
         return ERROR_BAD_LENGTH;

      case STATUS_NONEXISTENT_SECTOR:
         return ERROR_SECTOR_NOT_FOUND;

      case STATUS_DEVICE_PAPER_EMPTY:
         return ERROR_OUT_OF_PAPER;



      case STATUS_UNSUCCESSFUL:
         return ERROR_GEN_FAILURE;

      case STATUS_SHARING_VIOLATION:
         return ERROR_SHARING_VIOLATION;

      case STATUS_LOCK_NOT_GRANTED:
      case STATUS_FILE_LOCK_CONFLICT:
         return ERROR_LOCK_VIOLATION;

      case STATUS_WRONG_VOLUME:
         return ERROR_WRONG_DISK;



      case STATUS_END_OF_FILE:
      case STATUS_FILE_FORCED_CLOSED:
         return ERROR_HANDLE_EOF;


      case STATUS_CTL_FILE_NOT_SUPPORTED:
      case STATUS_NOT_SUPPORTED:
//      case STATUS_NOT_SERVER_SESSION:
//      case STATUS_NOT_CLIENT_SESSION:
         return ERROR_NOT_SUPPORTED;

      case STATUS_REMOTE_NOT_LISTENING:
         return ERROR_REM_NOT_LIST;




/* not fixed */

      case STATUS_NO_MORE_EAS:
      case STATUS_NO_MORE_ENTRIES:
      case STATUS_GUIDS_EXHAUSTED:
      case STATUS_AGENTS_EXHAUSTED:
         return ERROR_NO_MORE_ITEMS;

      case STATUS_DATATYPE_MISALIGNMENT:
      case STATUS_ACCESS_VIOLATION:
         return ERROR_NOACCESS;


      case STATUS_PORT_ALREADY_SET:
      case STATUS_SECTION_NOT_IMAGE:
      case STATUS_BAD_WORKING_SET_LIMIT:
      case STATUS_INCOMPATIBLE_FILE_MAP:
      case STATUS_UNABLE_TO_FREE_VM:
      case STATUS_UNABLE_TO_DELETE_SECTION:
      case STATUS_INVALID_CID:
      case STATUS_INVALID_INFO_CLASS:
      case STATUS_INVALID_PARAMETER:
      case STATUS_INVALID_PARAMETER_1:
      case STATUS_INVALID_PARAMETER_2:
      case STATUS_INVALID_PARAMETER_3:
      case STATUS_INVALID_PARAMETER_4:
      case STATUS_INVALID_PARAMETER_5:
      case STATUS_INVALID_PARAMETER_6:
      case STATUS_INVALID_PARAMETER_7:
      case STATUS_INVALID_PARAMETER_8:
      case STATUS_INVALID_PARAMETER_9:
      case STATUS_INVALID_PARAMETER_10:
      case STATUS_INVALID_PARAMETER_11:
      case STATUS_INVALID_PARAMETER_12:
      case STATUS_INVALID_PARAMETER_MIX:
      case STATUS_INVALID_PAGE_PROTECTION:
      case STATUS_SECTION_PROTECTION:
         return ERROR_INVALID_PARAMETER;


      case STATUS_NOT_LOCKED:
         return ERROR_NOT_LOCKED;

#if 0
STATUS_MORE_PROCESSING_REQUIRED      ERROR_MORE_DATA
STATUS_BAD_INITIAL_STACK             ERROR_STACK_OVERFLOW
STATUS_INVALID_VOLUME_LABEL          ERROR_LABEL_TOO_LONG

STATUS_NOT_COMMITTED                 ERROR_INVALID_ADDRESS
STATUS_NOT_MAPPED_VIEW               ERROR_INVALID_ADDRESS
STATUS_NOT_MAPPED_DATA               ERROR_INVALID_ADDRESS
STATUS_UNABLE_TO_DECOMMIT_VM         ERROR_INVALID_ADDRESS
STATUS_FREE_VM_NOT_AT_BASE           ERROR_INVALID_ADDRESS
STATUS_MEMORY_NOT_ALLOCATED          ERROR_INVALID_ADDRESS

STATUS_SUSPEND_COUNT_EXCEEDED        ERROR_SIGNAL_REFUSED
STATUS_NOTIFY_ENUM_DIR               ERROR_NOTIFY_ENUM_DIR
STATUS_REGISTRY_RECOVERED            ERROR_REGISTRY_RECOVERED
STATUS_REGISTRY_IO_FAILED            ERROR_REGISTRY_IO_FAILED
STATUS_NOT_REGISTRY_FILE             ERROR_NOT_REGISTRY_FILE
STATUS_KEY_DELETED                   ERROR_KEY_DELETED
STATUS_NO_LOG_SPACE                  ERROR_NO_LOG_SPACE
STATUS_KEY_HAS_CHILDREN              ERROR_KEY_HAS_CHILDREN

STATUS_CHILD_MUST_BE_VOLATILE        ERROR_CHILD_MUST_BE_VOLATILE
STATUS_REGISTRY_CORRUPT              ERROR_BADDB
STATUS_DLL_NOT_FOUND                 ERROR_MOD_NOT_FOUND
STATUS_DLL_INIT_FAILED               ERROR_DLL_INIT_FAILED
STATUS_ORDINAL_NOT_FOUND             ERROR_INVALID_ORDINAL
STATUS_ENTRYPOINT_NOT_FOUND          ERROR_PROC_NOT_FOUND
STATUS_PENDING                       ERROR_IO_PENDING
STATUS_MORE_ENTRIES                  ERROR_MORE_DATA
STATUS_BUFFER_OVERFLOW               ERROR_MORE_DATA
STATUS_INTEGER_OVERFLOW              ERROR_ARITHMETIC_OVERFLOW

STATUS_NO_INHERITANCE                ERROR_NO_INHERITANCE
STATUS_IN_PAGE_ERROR                 ERROR_SWAPERROR


STATUS_RESOURCE_DATA_NOT_FOUND       ERROR_RESOURCE_DATA_NOT_FOUND
STATUS_RESOURCE_TYPE_NOT_FOUND       ERROR_RESOURCE_TYPE_NOT_FOUND
STATUS_RESOURCE_NAME_NOT_FOUND       ERROR_RESOURCE_NAME_NOT_FOUND
STATUS_RESOURCE_LANG_NOT_FOUND       ERROR_RESOURCE_LANG_NOT_FOUND
STATUS_NO_MEDIA                      ERROR_NO_MEDIA_IN_DRIVE

STATUS_INVALID_COMPUTER_NAME         ERROR_INVALID_COMPUTERNAME
STATUS_NO_SUCH_PRIVILEGE             ERROR_NO_SUCH_PRIVILEGE
STATUS_PRIVILEGE_NOT_HELD            ERROR_PRIVILEGE_NOT_HELD
STATUS_CANNOT_IMPERSONATE            ERROR_CANNOT_IMPERSONATE
STATUS_LOGON_FAILURE                 ERROR_LOGON_FAILURE

STATUS_ACCOUNT_RESTRICTION           ERROR_ACCOUNT_RESTRICTION
STATUS_INVALID_LOGON_HOURS           ERROR_INVALID_LOGON_HOURS
STATUS_INVALID_WORKSTATION           ERROR_INVALID_WORKSTATION
STATUS_BUFFER_TOO_SMALL              ERROR_INSUFFICIENT_BUFFER
STATUS_DISK_CORRUPT_ERROR            ERROR_DISK_CORRUPT
STATUS_OBJECT_NAME_INVALID           ERROR_INVALID_NAME
STATUS_OBJECT_NAME_COLLISION         ERROR_ALREADY_EXISTS
STATUS_OBJECT_PATH_INVALID           ERROR_BAD_PATHNAME

STATUS_OBJECT_PATH_SYNTAX_BAD        ERROR_BAD_PATHNAME
STATUS_DATA_OVERRUN                  ERROR_IO_DEVICE
STATUS_DATA_LATE_ERROR               ERROR_IO_DEVICE
STATUS_QUOTA_EXCEEDED                ERROR_NOT_ENOUGH_QUOTA
STATUS_MUTANT_NOT_OWNED              ERROR_NOT_OWNER

STATUS_SEMAPHORE_LIMIT_EXCEEDED      ERROR_TOO_MANY_POSTS
STATUS_DISK_FULL                     ERROR_DISK_FULL
STATUS_NOT_A_DIRECTORY               ERROR_DIRECTORY
STATUS_UNKNOWN_REVISION              ERROR_UNKNOWN_REVISION
STATUS_REVISION_MISMATCH             ERROR_REVISION_MISMATCH
STATUS_INVALID_OWNER                 ERROR_INVALID_OWNER
STATUS_INVALID_PRIMARY_GROUP         ERROR_INVALID_PRIMARY_GROUP
STATUS_NO_IMPERSONATION_TOKEN        ERROR_NO_IMPERSONATION_TOKEN

STATUS_CANT_DISABLE_MANDATORY        ERROR_CANT_DISABLE_MANDATORY
STATUS_NO_LOGON_SERVERS              ERROR_NO_LOGON_SERVERS
STATUS_NO_SUCH_LOGON_SESSION         ERROR_NO_SUCH_LOGON_SESSION
STATUS_INVALID_ACCOUNT_NAME          ERROR_INVALID_ACCOUNT_NAME
STATUS_USER_EXISTS                   ERROR_USER_EXISTS
STATUS_NO_SUCH_USER                  ERROR_NO_SUCH_USER
STATUS_GROUP_EXISTS                  ERROR_GROUP_EXISTS
STATUS_NO_SUCH_GROUP                 ERROR_NO_SUCH_GROUP
STATUS_SPECIAL_GROUP                 ERROR_SPECIAL_GROUP
STATUS_MEMBER_IN_GROUP               ERROR_MEMBER_IN_GROUP

STATUS_MEMBER_NOT_IN_GROUP           ERROR_MEMBER_NOT_IN_GROUP
STATUS_LAST_ADMIN                    ERROR_LAST_ADMIN
STATUS_WRONG_PASSWORD                ERROR_INVALID_PASSWORD
STATUS_WRONG_PASSWORD_CORE           ERROR_INVALID_PASSWORD
STATUS_ILL_FORMED_PASSWORD           ERROR_ILL_FORMED_PASSWORD
STATUS_PASSWORD_RESTRICTION          ERROR_PASSWORD_RESTRICTION
STATUS_PASSWORD_EXPIRED              ERROR_PASSWORD_EXPIRED
STATUS_ACCOUNT_DISABLED              ERROR_ACCOUNT_DISABLED
STATUS_NONE_MAPPED                   ERROR_NONE_MAPPED
STATUS_TOO_MANY_LUIDS_REQUESTED      ERROR_TOO_MANY_LUIDS_REQUESTED

STATUS_LUIDS_EXHAUSTED               ERROR_LUIDS_EXHAUSTED
STATUS_INVALID_SUB_AUTHORITY         ERROR_INVALID_SUB_AUTHORITY
STATUS_INVALID_ACL                   ERROR_INVALID_ACL
STATUS_INVALID_SID                   ERROR_INVALID_SID
STATUS_INVALID_SECURITY_DESCR        ERROR_INVALID_SECURITY_DESCR
STATUS_PROCEDURE_NOT_FOUND           ERROR_PROC_NOT_FOUND
STATUS_BAD_INITIAL_PC                ERROR_BAD_EXE_FORMAT
STATUS_INVALID_FILE_FOR_SECTION      ERROR_BAD_EXE_FORMAT
STATUS_INVALID_IMAGE_FORMAT          ERROR_BAD_EXE_FORMAT
STATUS_INVALID_IMAGE_NOT_MZ          ERROR_BAD_EXE_FORMAT

STATUS_IMAGE_CHECKSUM_MISMATCH       ERROR_BAD_EXE_FORMAT
STATUS_NO_TOKEN                      ERROR_NO_TOKEN
STATUS_RANGE_NOT_LOCKED              ERROR_NOT_LOCKED
STATUS_SERVER_DISABLED               ERROR_SERVER_DISABLED
STATUS_SERVER_NOT_DISABLED           ERROR_SERVER_NOT_DISABLED
STATUS_INVALID_ID_AUTHORITY          ERROR_INVALID_ID_AUTHORITY
STATUS_ALLOTTED_SPACE_EXCEEDED       ERROR_ALLOTTED_SPACE_EXCEEDED
STATUS_INSUFF_SERVER_RESOURCES       ERROR_NOT_ENOUGH_SERVER_MEMORY

STATUS_FILE_INVALID                  ERROR_FILE_INVALID
STATUS_MAPPED_FILE_SIZE_ZERO         ERROR_FILE_INVALID
STATUS_DEVICE_BUSY                   ERROR_BUSY

STATUS_DUPLICATE_NAME                ERROR_DUP_NAME
STATUS_BAD_NETWORK_PATH              ERROR_BAD_NETPATH
STATUS_NETWORK_BUSY                  ERROR_NETWORK_BUSY
STATUS_DEVICE_DOES_NOT_EXIST         ERROR_DEV_NOT_EXIST
STATUS_TOO_MANY_COMMANDS             ERROR_TOO_MANY_CMDS

STATUS_ADAPTER_HARDWARE_ERROR        ERROR_ADAP_HDW_ERR
STATUS_REDIRECTOR_NOT_STARTED        ERROR_PATH_NOT_FOUND
STATUS_INVALID_EA_NAME               ERROR_INVALID_EA_NAME
STATUS_EA_LIST_INCONSISTENT          ERROR_EA_LIST_INCONSISTENT
STATUS_EA_TOO_LARGE                  ERROR_EA_LIST_INCONSISTENT
STATUS_INVALID_EA_FLAG               ERROR_EA_LIST_INCONSISTENT
STATUS_FILE_CORRUPT_ERROR            ERROR_FILE_CORRUPT
STATUS_EA_CORRUPT_ERROR              ERROR_FILE_CORRUPT
STATUS_NONEXISTENT_EA_ENTRY          ERROR_FILE_CORRUPT
STATUS_NO_EAS_ON_FILE                ERROR_FILE_CORRUPT

STATUS_INVALID_NETWORK_RESPONSE      ERROR_BAD_NET_RESP
STATUS_USER_SESSION_DELETED          ERROR_UNEXP_NET_ERR
STATUS_UNEXPECTED_NETWORK_ERROR      ERROR_UNEXP_NET_ERR
STATUS_BAD_REMOTE_ADAPTER            ERROR_BAD_REM_ADAP
STATUS_PRINT_QUEUE_FULL              ERROR_PRINTQ_FULL
STATUS_NO_SPOOL_SPACE                ERROR_NO_SPOOL_SPACE
STATUS_PRINT_CANCELLED               ERROR_PRINT_CANCELLED
STATUS_NETWORK_NAME_DELETED          ERROR_NETNAME_DELETED
STATUS_NETWORK_ACCESS_DENIED         ERROR_NETWORK_ACCESS_DENIED
STATUS_BAD_DEVICE_TYPE               ERROR_BAD_DEV_TYPE

STATUS_BAD_NETWORK_NAME              ERROR_BAD_NET_NAME
STATUS_TOO_MANY_NAMES                ERROR_TOO_MANY_NAMES
STATUS_TOO_MANY_GUIDS_REQUESTED      ERROR_TOO_MANY_NAMES
STATUS_TOO_MANY_ADDRESSES            ERROR_TOO_MANY_NAMES
STATUS_TOO_MANY_NODES                ERROR_TOO_MANY_NAMES
STATUS_TOO_MANY_SESSIONS             ERROR_TOO_MANY_SESS
STATUS_SHARING_PAUSED                ERROR_SHARING_PAUSED
STATUS_REQUEST_NOT_ACCEPTED          ERROR_REQ_NOT_ACCEP
STATUS_REDIRECTOR_PAUSED             ERROR_REDIR_PAUSED
STATUS_NET_WRITE_FAULT               ERROR_NET_WRITE_FAULT

STATUS_VIRTUAL_CIRCUIT_CLOSED        ERROR_VC_DISCONNECTED
STATUS_INVALID_PIPE_STATE            ERROR_BAD_PIPE
STATUS_INVALID_READ_MODE             ERROR_BAD_PIPE
STATUS_PIPE_CLOSING                  ERROR_NO_DATA
STATUS_PIPE_EMPTY                    ERROR_NO_DATA
STATUS_PIPE_CONNECTED                ERROR_PIPE_CONNECTED
STATUS_PIPE_DISCONNECTED             ERROR_PIPE_NOT_CONNECTED
STATUS_PIPE_LISTENING                ERROR_PIPE_LISTENING
STATUS_PIPE_NOT_AVAILABLE            ERROR_PIPE_BUSY
STATUS_INSTANCE_NOT_AVAILABLE        ERROR_PIPE_BUSY

STATUS_PIPE_BUSY                     ERROR_PIPE_BUSY
STATUS_PIPE_BROKEN                   ERROR_BROKEN_PIPE
STATUS_DIRECTORY_NOT_EMPTY           ERROR_DIR_NOT_EMPTY
STATUS_IO_TIMEOUT                    ERROR_SEM_TIMEOUT
STATUS_CANCELLED                     ERROR_OPERATION_ABORTED
STATUS_UNRECOGNIZED_MEDIA            ERROR_UNRECOGNIZED_MEDIA
STATUS_INVALID_LEVEL                 ERROR_INVALID_LEVEL
STATUS_UNRECOGNIZED_VOLUME           ERROR_UNRECOGNIZED_VOLUME
STATUS_FULLSCREEN_MODE               ERROR_FULLSCREEN_MODE
STATUS_END_OF_MEDIA                  ERROR_END_OF_MEDIA
STATUS_EOM_OVERFLOW                  ERROR_EOM_OVERFLOW
STATUS_BEGINNING_OF_MEDIA            ERROR_BEGINNING_OF_MEDIA
STATUS_MEDIA_CHANGED                 ERROR_MEDIA_CHANGED
STATUS_BUS_RESET                     ERROR_BUS_RESET
STATUS_FILEMARK_DETECTED             ERROR_FILEMARK_DETECTED
STATUS_SETMARK_DETECTED              ERROR_SETMARK_DETECTED

STATUS_NO_DATA_DETECTED              ERROR_NO_DATA_DETECTED
STATUS_PARTITION_FAILURE             ERROR_PARTITION_FAILURE
STATUS_INVALID_BLOCK_LENGTH          ERROR_INVALID_BLOCK_LENGTH
STATUS_DEVICE_NOT_PARTITIONED        ERROR_DEVICE_NOT_PARTITIONED
STATUS_UNABLE_TO_LOCK_MEDIA          ERROR_UNABLE_TO_LOCK_MEDIA
STATUS_UNABLE_TO_UNLOAD_MEDIA        ERROR_UNABLE_TO_UNLOAD_MEDIA
STATUS_UNMAPPABLE_CHARACTER          ERROR_NO_UNICODE_TRANSLATION
STATUS_NOT_ALL_ASSIGNED              ERROR_NOT_ALL_ASSIGNED
STATUS_SOME_NOT_MAPPED               ERROR_SOME_NOT_MAPPED
STATUS_NO_QUOTAS_FOR_ACCOUNT         ERROR_NO_QUOTAS_FOR_ACCOUNT

STATUS_LOCAL_USER_SESSION_KEY        ERROR_LOCAL_USER_SESSION_KEY
STATUS_NULL_LM_PASSWORD              ERROR_NULL_LM_PASSWORD
STATUS_BAD_INHERITANCE_ACL           ERROR_BAD_INHERITANCE_ACL
STATUS_INVALID_GROUP_ATTRIBUTES      ERROR_INVALID_GROUP_ATTRIBUTES
STATUS_BAD_IMPERSONATION_LEVEL       ERROR_BAD_IMPERSONATION_LEVEL
STATUS_CANT_OPEN_ANONYMOUS           ERROR_CANT_OPEN_ANONYMOUS
STATUS_BAD_VALIDATION_CLASS          ERROR_BAD_VALIDATION_CLASS
STATUS_BAD_TOKEN_TYPE                ERROR_BAD_TOKEN_TYPE
STATUS_NO_SECURITY_ON_OBJECT         ERROR_NO_SECURITY_ON_OBJECT
STATUS_CANT_ACCESS_DOMAIN_INFO       ERROR_CANT_ACCESS_DOMAIN_INFO

STATUS_INVALID_SERVER_STATE          ERROR_INVALID_SERVER_STATE
STATUS_INVALID_DOMAIN_STATE          ERROR_INVALID_DOMAIN_STATE
STATUS_INVALID_DOMAIN_ROLE           ERROR_INVALID_DOMAIN_ROLE
STATUS_NO_SUCH_DOMAIN                ERROR_NO_SUCH_DOMAIN
STATUS_DOMAIN_EXISTS                 ERROR_DOMAIN_EXISTS
STATUS_DOMAIN_LIMIT_EXCEEDED         ERROR_DOMAIN_LIMIT_EXCEEDED
STATUS_INTERNAL_DB_CORRUPTION        ERROR_INTERNAL_DB_CORRUPTION
STATUS_INTERNAL_ERROR                ERROR_INTERNAL_ERROR
STATUS_GENERIC_NOT_MAPPED            ERROR_GENERIC_NOT_MAPPED
STATUS_BAD_DESCRIPTOR_FORMAT         ERROR_BAD_DESCRIPTOR_FORMAT

STATUS_NOT_LOGON_PROCESS             ERROR_NOT_LOGON_PROCESS
STATUS_LOGON_SESSION_EXISTS          ERROR_LOGON_SESSION_EXISTS
STATUS_NO_SUCH_PACKAGE               ERROR_NO_SUCH_PACKAGE
STATUS_BAD_LOGON_SESSION_STATE       ERROR_BAD_LOGON_SESSION_STATE
STATUS_LOGON_SESSION_COLLISION       ERROR_LOGON_SESSION_COLLISION
STATUS_INVALID_LOGON_TYPE            ERROR_INVALID_LOGON_TYPE
STATUS_RXACT_INVALID_STATE           ERROR_RXACT_INVALID_STATE
STATUS_RXACT_COMMIT_FAILURE          ERROR_RXACT_COMMIT_FAILURE
STATUS_SPECIAL_ACCOUNT               ERROR_SPECIAL_ACCOUNT
STATUS_SPECIAL_USER                  ERROR_SPECIAL_USER

STATUS_MEMBERS_PRIMARY_GROUP         ERROR_MEMBERS_PRIMARY_GROUP
STATUS_TOKEN_ALREADY_IN_USE          ERROR_TOKEN_ALREADY_IN_USE
STATUS_NO_SUCH_ALIAS                 ERROR_NO_SUCH_ALIAS
STATUS_MEMBER_NOT_IN_ALIAS           ERROR_MEMBER_NOT_IN_ALIAS
STATUS_MEMBER_IN_ALIAS               ERROR_MEMBER_IN_ALIAS
STATUS_ALIAS_EXISTS                  ERROR_ALIAS_EXISTS
STATUS_LOGON_NOT_GRANTED             ERROR_LOGON_NOT_GRANTED
STATUS_TOO_MANY_SECRETS              ERROR_TOO_MANY_SECRETS
STATUS_SECRET_TOO_LONG               ERROR_SECRET_TOO_LONG
STATUS_INTERNAL_DB_ERROR             ERROR_INTERNAL_DB_ERROR

STATUS_TOO_MANY_CONTEXT_IDS          ERROR_TOO_MANY_CONTEXT_IDS
STATUS_LOGON_TYPE_NOT_GRANTED        ERROR_LOGON_TYPE_NOT_GRANTED
STATUS_NT_CROSS_ENCRYPTION_REQUIRED  ERROR_NT_CROSS_ENCRYPTION_REQUIRED
STATUS_NO_SUCH_MEMBER                ERROR_NO_SUCH_MEMBER
STATUS_INVALID_MEMBER                ERROR_INVALID_MEMBER
STATUS_TOO_MANY_SIDS                 ERROR_TOO_MANY_SIDS
STATUS_LM_CROSS_ENCRYPTION_REQUIRED  ERROR_LM_CROSS_ENCRYPTION_REQUIRED
STATUS_MESSAGE_NOT_FOUND             ERROR_MR_MID_NOT_FOUND
STATUS_LOCAL_DISCONNECT              ERROR_NETNAME_DELETED
STATUS_REMOTE_DISCONNECT             ERROR_NETNAME_DELETED

STATUS_REMOTE_RESOURCES              ERROR_REM_NOT_LIST
STATUS_LINK_FAILED                   ERROR_UNEXP_NET_ERR
STATUS_LINK_TIMEOUT                  ERROR_UNEXP_NET_ERR
STATUS_INVALID_CONNECTION            ERROR_UNEXP_NET_ERR
STATUS_INVALID_ADDRESS               ERROR_UNEXP_NET_ERR
STATUS_IO_DEVICE_ERROR               ERROR_IO_DEVICE
STATUS_DEVICE_PROTOCOL_ERROR         ERROR_IO_DEVICE
STATUS_DRIVER_INTERNAL_ERROR         ERROR_IO_DEVICE
STATUS_DEVICE_CONFIGURATION_ERROR    ERROR_INVALID_PARAMETER

STATUS_INVALID_USER_BUFFER           ERROR_INVALID_USER_BUFFER
STATUS_SERIAL_NO_DEVICE_INITED       ERROR_SERIAL_NO_DEVICE
STATUS_SHARED_IRQ_BUSY               ERROR_IRQ_BUSY
STATUS_SERIAL_MORE_WRITES            ERROR_MORE_WRITES
STATUS_SERIAL_COUNTER_TIMEOUT        ERROR_COUNTER_TIMEOUT
STATUS_FLOPPY_ID_MARK_NOT_FOUND      ERROR_FLOPPY_ID_MARK_NOT_FOUND
STATUS_FLOPPY_WRONG_CYLINDER         ERROR_FLOPPY_WRONG_CYLINDER
STATUS_FLOPPY_UNKNOWN_ERROR          ERROR_FLOPPY_UNKNOWN_ERROR
STATUS_FLOPPY_BAD_REGISTERS          ERROR_FLOPPY_BAD_REGISTERS
STATUS_DISK_RECALIBRATE_FAILED       ERROR_DISK_RECALIBRATE_FAILED

STATUS_DISK_OPERATION_FAILED         ERROR_DISK_OPERATION_FAILED
STATUS_DISK_RESET_FAILED             ERROR_DISK_RESET_FAILED
STATUS_EVENTLOG_FILE_CORRUPT         ERROR_EVENTLOG_FILE_CORRUPT
STATUS_EVENTLOG_CANT_START           ERROR_EVENTLOG_CANT_START
STATUS_NETLOGON_NOT_STARTED          ERROR_NETLOGON_NOT_STARTED
STATUS_ACCOUNT_EXPIRED               ERROR_ACCOUNT_EXPIRED
STATUS_NETWORK_CREDENTIAL_CONFLICT   ERROR_SESSION_CREDENTIAL_CONFLICT
STATUS_REMOTE_SESSION_LIMIT          ERROR_REMOTE_SESSION_LIMIT_EXCEEDED
STATUS_INVALID_BUFFER_SIZE           ERROR_INVALID_USER_BUFFER
STATUS_INVALID_ADDRESS_COMPONENT     ERROR_INVALID_NETNAME

STATUS_INVALID_ADDRESS_WILDCARD      ERROR_INVALID_NETNAME
STATUS_ADDRESS_ALREADY_EXISTS        ERROR_DUP_NAME
STATUS_ADDRESS_CLOSED                ERROR_NETNAME_DELETED
STATUS_CONNECTION_DISCONNECTED       ERROR_NETNAME_DELETED
STATUS_CONNECTION_RESET              ERROR_NETNAME_DELETED
STATUS_TRANSACTION_ABORTED           ERROR_UNEXP_NET_ERR
STATUS_TRANSACTION_TIMED_OUT         ERROR_UNEXP_NET_ERR
STATUS_TRANSACTION_NO_RELEASE        ERROR_UNEXP_NET_ERR
STATUS_TRANSACTION_NO_MATCH          ERROR_UNEXP_NET_ERR
STATUS_TRANSACTION_RESPONDED         ERROR_UNEXP_NET_ERR

STATUS_TRANSACTION_INVALID_ID        ERROR_UNEXP_NET_ERR
STATUS_TRANSACTION_INVALID_TYPE      ERROR_UNEXP_NET_ERR
RPC_NT_SERVER_UNAVAILABLE            RPC_S_SERVER_UNAVAILABLE
RPC_NT_INVALID_STRING_BINDING        RPC_S_INVALID_STRING_BINDING
RPC_NT_WRONG_KIND_OF_BINDING         RPC_S_WRONG_KIND_OF_BINDING
RPC_NT_PROTSEQ_NOT_SUPPORTED         RPC_S_PROTSEQ_NOT_SUPPORTED
RPC_NT_INVALID_RPC_PROTSEQ           RPC_S_INVALID_RPC_PROTSEQ
RPC_NT_INVALID_STRING_UUID           RPC_S_INVALID_STRING_UUID

RPC_NT_INVALID_ENDPOINT_FORMAT       RPC_S_INVALID_ENDPOINT_FORMAT
RPC_NT_INVALID_NET_ADDR              RPC_S_INVALID_NET_ADDR
RPC_NT_NO_ENDPOINT_FOUND             RPC_S_NO_ENDPOINT_FOUND
RPC_NT_INVALID_TIMEOUT               RPC_S_INVALID_TIMEOUT
RPC_NT_OBJECT_NOT_FOUND              RPC_S_OBJECT_NOT_FOUND
RPC_NT_ALREADY_REGISTERED            RPC_S_ALREADY_REGISTERED
RPC_NT_TYPE_ALREADY_REGISTERED       RPC_S_TYPE_ALREADY_REGISTERED
RPC_NT_ALREADY_LISTENING             RPC_S_ALREADY_LISTENING
RPC_NT_NO_PROTSEQS_REGISTERED        RPC_S_NO_PROTSEQS_REGISTERED
RPC_NT_NOT_LISTENING                 RPC_S_NOT_LISTENING

RPC_NT_UNKNOWN_MGR_TYPE              RPC_S_UNKNOWN_MGR_TYPE
RPC_NT_UNKNOWN_IF                    RPC_S_UNKNOWN_IF
RPC_NT_NO_BINDINGS                   RPC_S_NO_BINDINGS
RPC_NT_NO_MORE_BINDINGS              RPC_S_NO_MORE_BINDINGS
RPC_NT_NO_PROTSEQS                   RPC_S_NO_PROTSEQS
RPC_NT_CANT_CREATE_ENDPOINT          RPC_S_CANT_CREATE_ENDPOINT
RPC_NT_OUT_OF_RESOURCES              RPC_S_OUT_OF_RESOURCES
RPC_NT_SERVER_TOO_BUSY               RPC_S_SERVER_TOO_BUSY
RPC_NT_INVALID_NETWORK_OPTIONS       RPC_S_INVALID_NETWORK_OPTIONS
RPC_NT_NO_CALL_ACTIVE                RPC_S_NO_CALL_ACTIVE

RPC_NT_CALL_FAILED                   RPC_S_CALL_FAILED
RPC_NT_CALL_FAILED_DNE               RPC_S_CALL_FAILED_DNE
RPC_NT_PROTOCOL_ERROR                RPC_S_PROTOCOL_ERROR
RPC_NT_UNSUPPORTED_TRANS_SYN         RPC_S_UNSUPPORTED_TRANS_SYN
RPC_NT_UNSUPPORTED_TYPE              RPC_S_UNSUPPORTED_TYPE
RPC_NT_INVALID_TAG                   RPC_S_INVALID_TAG
RPC_NT_INVALID_BOUND                 RPC_S_INVALID_BOUND
RPC_NT_NO_ENTRY_NAME                 RPC_S_NO_ENTRY_NAME
RPC_NT_INVALID_NAME_SYNTAX           RPC_S_INVALID_NAME_SYNTAX
RPC_NT_UNSUPPORTED_NAME_SYNTAX       RPC_S_UNSUPPORTED_NAME_SYNTAX

RPC_NT_UUID_NO_ADDRESS               RPC_S_UUID_NO_ADDRESS
RPC_NT_DUPLICATE_ENDPOINT            RPC_S_DUPLICATE_ENDPOINT
RPC_NT_UNKNOWN_AUTHN_TYPE            RPC_S_UNKNOWN_AUTHN_TYPE
RPC_NT_MAX_CALLS_TOO_SMALL           RPC_S_MAX_CALLS_TOO_SMALL
RPC_NT_STRING_TOO_LONG               RPC_S_STRING_TOO_LONG
RPC_NT_PROTSEQ_NOT_FOUND             RPC_S_PROTSEQ_NOT_FOUND
RPC_NT_PROCNUM_OUT_OF_RANGE          RPC_S_PROCNUM_OUT_OF_RANGE
RPC_NT_BINDING_HAS_NO_AUTH           RPC_S_BINDING_HAS_NO_AUTH
RPC_NT_UNKNOWN_AUTHN_SERVICE         RPC_S_UNKNOWN_AUTHN_SERVICE
RPC_NT_UNKNOWN_AUTHN_LEVEL           RPC_S_UNKNOWN_AUTHN_LEVEL

RPC_NT_INVALID_AUTH_IDENTITY         RPC_S_INVALID_AUTH_IDENTITY
RPC_NT_UNKNOWN_AUTHZ_SERVICE         RPC_S_UNKNOWN_AUTHZ_SERVICE
EPT_NT_INVALID_ENTRY                 EPT_S_INVALID_ENTRY
EPT_NT_CANT_PERFORM_OP               EPT_S_CANT_PERFORM_OP
EPT_NT_NOT_REGISTERED                EPT_S_NOT_REGISTERED
RPC_NT_NOTHING_TO_EXPORT             RPC_S_NOTHING_TO_EXPORT
RPC_NT_INCOMPLETE_NAME               RPC_S_INCOMPLETE_NAME
RPC_NT_INVALID_VERS_OPTION           RPC_S_INVALID_VERS_OPTION
RPC_NT_NO_MORE_MEMBERS               RPC_S_NO_MORE_MEMBERS
RPC_NT_NOT_ALL_OBJS_UNEXPORTED       RPC_S_NOT_ALL_OBJS_UNEXPORTED

RPC_NT_INTERFACE_NOT_FOUND           RPC_S_INTERFACE_NOT_FOUND
RPC_NT_ENTRY_ALREADY_EXISTS          RPC_S_ENTRY_ALREADY_EXISTS
RPC_NT_ENTRY_NOT_FOUND               RPC_S_ENTRY_NOT_FOUND
RPC_NT_NAME_SERVICE_UNAVAILABLE      RPC_S_NAME_SERVICE_UNAVAILABLE
RPC_NT_INVALID_NAF_ID                RPC_S_INVALID_NAF_ID
RPC_NT_CANNOT_SUPPORT                RPC_S_CANNOT_SUPPORT
RPC_NT_NO_CONTEXT_AVAILABLE          RPC_S_NO_CONTEXT_AVAILABLE
RPC_NT_INTERNAL_ERROR                RPC_S_INTERNAL_ERROR
RPC_NT_ZERO_DIVIDE                   RPC_S_ZERO_DIVIDE
RPC_NT_ADDRESS_ERROR                 RPC_S_ADDRESS_ERROR

RPC_NT_FP_DIV_ZERO                   RPC_S_FP_DIV_ZERO
RPC_NT_FP_UNDERFLOW                  RPC_S_FP_UNDERFLOW
RPC_NT_FP_OVERFLOW                   RPC_S_FP_OVERFLOW
RPC_NT_NO_MORE_ENTRIES               RPC_X_NO_MORE_ENTRIES
RPC_NT_SS_CHAR_TRANS_OPEN_FAIL       RPC_X_SS_CHAR_TRANS_OPEN_FAIL
RPC_NT_SS_CHAR_TRANS_SHORT_FILE      RPC_X_SS_CHAR_TRANS_SHORT_FILE
RPC_NT_SS_CONTEXT_MISMATCH           ERROR_INVALID_HANDLE
RPC_NT_SS_CONTEXT_DAMAGED            RPC_X_SS_CONTEXT_DAMAGED
RPC_NT_SS_HANDLES_MISMATCH           RPC_X_SS_HANDLES_MISMATCH
RPC_NT_SS_CANNOT_GET_CALL_HANDLE     RPC_X_SS_CANNOT_GET_CALL_HANDLE

RPC_NT_NULL_REF_POINTER              RPC_X_NULL_REF_POINTER
RPC_NT_ENUM_VALUE_OUT_OF_RANGE       RPC_X_ENUM_VALUE_OUT_OF_RANGE
RPC_NT_BYTE_COUNT_TOO_SMALL          RPC_X_BYTE_COUNT_TOO_SMALL
RPC_NT_BAD_STUB_DATA                 RPC_X_BAD_STUB_DATA
RPC_NT_INVALID_OBJECT                RPC_S_INVALID_OBJECT
STATUS_NO_TRUST_LSA_SECRET           ERROR_NO_TRUST_LSA_SECRET
STATUS_NO_TRUST_SAM_ACCOUNT          ERROR_NO_TRUST_SAM_ACCOUNT
STATUS_TRUSTED_DOMAIN_FAILURE        ERROR_TRUSTED_DOMAIN_FAILURE
STATUS_TRUSTED_RELATIONSHIP_FAILURE  ERROR_TRUSTED_RELATIONSHIP_FAILURE
STATUS_TRUST_FAILURE                 ERROR_TRUST_FAILURE
RPC_NT_CALL_IN_PROGRESS              RPC_S_CALL_IN_PROGRESS

STATUS_LOG_FILE_FULL                 ERROR_LOG_FILE_FULL
STATUS_EVENTLOG_FILE_CHANGED         ERROR_EVENTLOG_FILE_CHANGED

STATUS_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT
                                 ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT

STATUS_NOLOGON_WORKSTATION_TRUST_ACCOUNT
                                 ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT

STATUS_NOLOGON_SERVER_TRUST_ACCOUNT  ERROR_NOLOGON_SERVER_TRUST_ACCOUNT
STATUS_DOMAIN_TRUST_INCONSISTENT     ERROR_DOMAIN_TRUST_INCONSISTENT
STATUS_NO_USER_SESSION_KEY           ERROR_NO_USER_SESSION_KEY
STATUS_POSSIBLE_DEADLOCK             ERROR_POSSIBLE_DEADLOCK
STATUS_IMAGE_ALREADY_LOADED          ERROR_SERVICE_ALREADY_RUNNING
RPC_NT_GROUP_MEMBER_NOT_FOUND        RPC_S_GROUP_MEMBER_NOT_FOUND

EPT_NT_CANT_CREATE                   EPT_S_CANT_CREATE
STATUS_NO_BROWSER_SERVERS_FOUND      ERROR_NO_BROWSER_SERVERS_FOUND
STATUS_MAPPED_ALIGNMENT              ERROR_MAPPED_ALIGNMENT
STATUS_CONNECTION_IN_USE             ERROR_DEVICE_IN_USE
STATUS_VERIFY_REQUIRED               ERROR_MEDIA_CHANGED
#endif

      default:
          DPRINT("Unknown status code: %u\n", Status);
          return ERROR_GEN_FAILURE;
   }
   return(0);
}


VOID SetLastError(DWORD dwErrorCode)
{
   LastError = dwErrorCode;
}

DWORD GetLastError(VOID)
{
   return(LastError);
}

BOOL __ErrorReturnFalse(ULONG ErrorCode)
{
   return(FALSE);
}

PVOID __ErrorReturnNull(ULONG ErrorCode)
{
   return(NULL);
}

WINBOOL
STDCALL
Beep (DWORD dwFreq, DWORD dwDuration)
{
    HANDLE hBeep;
    BEEP_SET_PARAMETERS BeepSetParameters;
    DWORD dwReturned;

    hBeep = CreateFile("\\Beep",
                       FILE_GENERIC_READ | FILE_GENERIC_WRITE,
                       0,
                       NULL,
                       OPEN_EXISTING,
                       0,
                       NULL);
    if (!hBeep)
        return FALSE;

    /* Set beep data */
    BeepSetParameters.Frequency = dwFreq;
    BeepSetParameters.Duration  = dwDuration;

    DeviceIoControl(hBeep,
                    IOCTL_BEEP_SET,
                    &BeepSetParameters,
                    sizeof(BEEP_SET_PARAMETERS),
                    NULL,
                    0,
                    &dwReturned,
                    NULL);

    CloseHandle (hBeep);

    return TRUE;
}

