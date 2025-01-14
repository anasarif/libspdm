/**
 *  Copyright Notice:
 *  Copyright 2021 DMTF. All rights reserved.
 *  License: BSD 3-Clause License. For full text see link: https://github.com/DMTF/libspdm/blob/main/LICENSE.md
 **/

#include "internal/libspdm_responder_lib.h"
#include "spdm_transport_mctp_lib.h"
#include "spdm_unit_fuzzing.h"
#include "toolchain_harness.h"

uintn get_max_buffer_size(void)
{
    return LIBSPDM_MAX_MESSAGE_BUFFER_SIZE;
}

void test_spdm_transport_mctp_decode_message(void **State)
{
    spdm_test_context_t *spdm_test_context;
    libspdm_context_t *spdm_context;
    uintn transport_message_size;
    uint8_t transport_message[LIBSPDM_MAX_MESSAGE_BUFFER_SIZE];
    bool is_app_message;
    bool is_requester;
    spdm_test_context = *State;
    spdm_context = spdm_test_context->spdm_context;
    is_requester = spdm_test_context->is_requester;
    is_app_message = false;

    spdm_context->connection_info.connection_state = LIBSPDM_CONNECTION_STATE_AFTER_VERSION;

    transport_message_size = sizeof(transport_message);

    libspdm_transport_mctp_decode_message(spdm_context, NULL, &is_app_message, is_requester,
                                          spdm_test_context->test_buffer_size,
                                          spdm_test_context->test_buffer, &transport_message_size,
                                          transport_message);
}

spdm_test_context_t m_spdm_transport_mctp_test_context = {
    SPDM_TEST_CONTEXT_SIGNATURE,
    false,
};

void run_test_harness(const void *test_buffer, uintn test_buffer_size)
{
    void *State;

    setup_spdm_test_context(&m_spdm_transport_mctp_test_context);

    m_spdm_transport_mctp_test_context.test_buffer = test_buffer;
    m_spdm_transport_mctp_test_context.test_buffer_size = test_buffer_size;

    spdm_unit_test_group_setup(&State);

    test_spdm_transport_mctp_decode_message(&State);

    spdm_unit_test_group_teardown(&State);
}
