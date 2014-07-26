/*
 * Copyright (c) 2008-2014, Dave Benson and the protobuf-c authors.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*! \file
 * Support library for `protoc-c` generated code.
 *
 * This file implements the public API used by the code generated
 * by `protoc-c`.
 *
 * \authors Dave Benson and the protobuf-c authors
 *
 * \copyright 2008-2014. Licensed under the terms of the [BSD-2-Clause] license.
 */

/**
 * \todo 64-BIT OPTIMIZATION: certain implementations use 32-bit math
 * even on 64-bit platforms (uint64_size, uint64_pack, parse_uint64).
 *
 * \todo Use size_t consistently.
 */

#include <stdlib.h>	/* for malloc, free */

#include "protobuf-c.h"


/* --- version --- */

const char *
protobuf_c_version(void)
{
	return PROTOBUF_C_VERSION;
}

uint32_t
protobuf_c_version_number(void)
{
	return PROTOBUF_C_VERSION_NUMBER;
}

static void *
system_alloc(void *allocator_data, size_t size)
{
	return malloc(size);
}

static void
system_free(void *allocator_data, void *data)
{
	free(data);
}

/*
 * This allocator uses the system's malloc() and free(). It is the default
 * allocator used if NULL is passed as the ProtobufCAllocator to an exported
 * function.
 */
ProtobufCAllocator protobuf_c_default_allocator = {
	.alloc = &system_alloc,
	.free = &system_free,
	.allocator_data = NULL,
};

