/* Generated by IDL compiler version OSF DCE T1.2.0-09 */
#ifdef VMS
#pragma nostandard
#endif
#include <dce/idlddefs.h>
#include <convc.h>
static idl_ulong_int IDL_offset_vec[] = {
0,
sizeof(uuid_t ),
offsetof(uuid_t , time_low),
offsetof(uuid_t , time_mid),
offsetof(uuid_t , time_hi_and_version),
offsetof(uuid_t , clock_seq_hi_and_reserved),
offsetof(uuid_t , clock_seq_low),
offsetof(uuid_t , node),
0
};

static IDL_rtn_func_t IDL_rtn_vec[] = {
(IDL_rtn_func_t)NULL,
(IDL_rtn_func_t)NULL
};

static idl_byte IDL_type_vec[] = {
0xff,0xff,0xff,0xff,
0,
0,
0xff,0xff,
0x00,0x03,
0x00,0x02,
0x00,0x01,
0x00,0x00,
0x4a,0x96,0x7f,0x14,
0x30,0x00,
0x00,0x00,
0x0d,
0x00,
0x01,0x28,0x82,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x04,
0x00,0x00,0x00,0x8c,
0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,
0x00,0x00,0x00,0x01,
0x00,0x00,0x00,0x06,
0x00,0x00,0x00,0x03,
0x00,0x00,0x00,0x01,
0x00,0x00,0x00,0x58,
0x00,0x00,0x00,0x00,
0xff,0xff,0xff,0xff,
0x00,0x00,0x00,0x02,
IDL_DT_PASSED_BY_REF,
IDL_DT_FIXED_STRUCT,
0|IDL_PROP_DEP_INT|IDL_PROP_MAYBE_WIRE_ALIGNED,
0xff,
0x00,0x00,0x00,0x68,
IDL_DT_EOL,
0xff,0xff,0xff,
0x00,0x00,0x00,0x01,
IDL_DT_NDR_ALIGN_4,
IDL_DT_ULONG,
IDL_DT_USHORT,
IDL_DT_USHORT,
IDL_DT_USMALL,
IDL_DT_USMALL,
IDL_DT_FIXED_ARRAY,
0,
0x00,0x00,0x00,0x7f,
0x00,0x00,0x00,0x7f,
IDL_DT_EOL,
0xff,0xff,
1,
0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x05,
IDL_DT_BYTE,
0xff,0xff,0xff,
0x00,0x00,0x00,0x10,
0
};


static void op0_ssr
#ifdef IDL_PROTOTYPES
(
 handle_t h,
 rpc_call_handle_t IDL_call_h,
 rpc_iovector_elt_p_t IDL_elt_p,
 ndr_format_p_t IDL_drep_p,
 rpc_transfer_syntax_p_t IDL_transfer_syntax_p,
 rpc_mgr_epv_t IDL_mgr_epv,
 error_status_t *IDL_status_p
)
#else
(h, IDL_call_h, IDL_elt_p, IDL_drep_p, IDL_transfer_syntax_p, IDL_mgr_epv, IDL_status_p)
 handle_t h;
 rpc_call_handle_t IDL_call_h;
 rpc_iovector_elt_p_t IDL_elt_p;
 ndr_format_p_t IDL_drep_p;
 rpc_transfer_syntax_p_t IDL_transfer_syntax_p;
 rpc_mgr_epv_t IDL_mgr_epv;
 error_status_t *IDL_status_p;
#endif
{
IDL_ms_t IDL_ms;
idl_byte IDL_stack_packet[IDL_STACK_PACKET_SIZE];
volatile ndr_boolean IDL_manager_entered = ndr_false;
volatile RPC_SS_THREADS_CANCEL_STATE_T IDL_async_cancel_state;
volatile RPC_SS_THREADS_CANCEL_STATE_T IDL_general_cancel_state;
rpc_void_p_t IDL_param_vec[3];
uuid_t cas_uuid;
RPC_SS_INIT_SERVER
rpc_ss_init_marsh_state(IDL_type_vec, &IDL_ms);
IDL_ms.IDL_stack_packet_status = IDL_stack_packet_unused_k;
IDL_ms.IDL_stack_packet_addr = IDL_stack_packet;
TRY
IDL_ms.IDL_offset_vec = IDL_offset_vec;
IDL_ms.IDL_rtn_vec = IDL_rtn_vec;
IDL_ms.IDL_call_h = (rpc_call_handle_t)IDL_call_h;
IDL_ms.IDL_drep = *IDL_drep_p;
IDL_ms.IDL_elt_p = IDL_elt_p;
IDL_param_vec[1] = (rpc_void_p_t)&h;
IDL_param_vec[2] = (rpc_void_p_t)&cas_uuid;
IDL_ms.IDL_param_vec = IDL_param_vec;
IDL_ms.IDL_side = IDL_server_side_k;
IDL_ms.IDL_language = IDL_lang_c_k;
rpc_ss_ndr_unmar_interp(
    1,
    88,
    IDL_param_vec, &IDL_ms);

/* manager call */
IDL_manager_entered = ndr_true;
RPC_SS_THREADS_DISABLE_ASYNC(IDL_async_cancel_state);
RPC_SS_THREADS_ENABLE_GENERAL(IDL_general_cancel_state);
(*((convc_v1_0_epv_t *)IDL_mgr_epv)->convc_indy)(h,
 &cas_uuid);
RPC_SS_THREADS_RESTORE_GENERAL(IDL_general_cancel_state);
RPC_SS_THREADS_RESTORE_ASYNC(IDL_async_cancel_state);
{
rpc_ss_ndr_marsh_interp(
    0,
    0,
    IDL_param_vec, &IDL_ms);
if (IDL_ms.IDL_iovec.num_elt != 0)
  rpc_call_transmit((rpc_call_handle_t)IDL_ms.IDL_call_h,(rpc_iovector_p_t)&IDL_ms.IDL_iovec,
  (unsigned32*)&IDL_ms.IDL_status);  /* Send remaining outs */

}if (IDL_ms.IDL_status != error_status_ok) goto IDL_closedown;

IDL_closedown: ;
CATCH_ALL
if ( IDL_manager_entered )
{
RPC_SS_THREADS_RESTORE_GENERAL(IDL_general_cancel_state);
RPC_SS_THREADS_RESTORE_ASYNC(IDL_async_cancel_state);
}
rpc_ss_ndr_clean_up(&IDL_ms);
if (!RPC_SS_EXC_MATCHES(THIS_CATCH,&rpc_x_ss_pipe_comm_error))
{
if ( ! IDL_manager_entered )
{
}
{
rpc_ss_send_server_exception_2(IDL_call_h,THIS_CATCH,0,0,&IDL_ms);
IDL_ms.IDL_status = error_status_ok;
}
}
ENDTRY
if (IDL_ms.IDL_mem_handle.memory)
{
 rpc_ss_mem_free(&IDL_ms.IDL_mem_handle);
}
if (IDL_ms.IDL_status != error_status_ok)
{
if (IDL_ms.IDL_status == rpc_s_call_cancelled)
{
rpc_ss_send_server_exception(IDL_call_h,&RPC_SS_THREADS_X_CANCELLED);
IDL_ms.IDL_status = error_status_ok;
}
else
{
{
rpc_ss_send_server_exception(IDL_call_h,&rpc_x_ss_remote_comm_failure);
IDL_ms.IDL_status = error_status_ok;
}
}
}
*IDL_status_p = IDL_ms.IDL_status;
}

static rpc_v2_server_stub_proc_t IDL_epva[] = 
{
 (rpc_v2_server_stub_proc_t)op0_ssr
};

static rpc_syntax_id_t IDL_transfer_syntaxes[1] = {
{
{0x8a885d04u, 0x1ceb, 0x11c9, 0x9f, 0xe8, {0x8, 0x0, 0x2b, 0x10, 0x48, 0x60}},
2}};

static rpc_if_rep_t IDL_ifspec = {
  1, /* ifspec rep version */
  1, /* op count */
  1, /* if version */
  {0x4a967f14u, 0x3000, 0x0000, 0x0d, 0x00, {0x1, 0x28, 0x82, 0x0, 0x0, 0x0}},
  2, /* stub/rt if version */
  {0, NULL}, /* endpoint vector */
  {1, IDL_transfer_syntaxes} /* syntax vector */
,IDL_epva /* server_epv */
,NULL /* manager epv */
};
/* global */ rpc_if_handle_t convc_v1_0_s_ifspec = (rpc_if_handle_t)&IDL_ifspec;
#ifdef VMS
#pragma standard
#endif
