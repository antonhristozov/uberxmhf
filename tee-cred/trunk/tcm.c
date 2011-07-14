/*
 * @XMHF_LICENSE_HEADER_START@
 *
 * eXtensible, Modular Hypervisor Framework (XMHF)
 * Copyright (c) 2009-2012 Carnegie Mellon University
 * Copyright (c) 2010-2012 VDG Inc.
 * All Rights Reserved.
 *
 * Developed by: XMHF Team
 *               Carnegie Mellon University / CyLab
 *               VDG Inc.
 *               http://xmhf.org
 *
 * This file is part of the EMHF historical reference
 * codebase, and is released under the terms of the
 * GNU General Public License (GPL) version 2.
 * Please see the LICENSE file for details.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * @XMHF_LICENSE_HEADER_END@
 */

#include <malloc.h>
#include <string.h>

#include "tcm.h"
#include "audited-kv.h"
#include "audited-kv-pal.h"
#include "audit.h"

#include <tee-sdk/tv.h>

int tcm_init(tcm_ctx_t* tcm_ctx,
             audit_ctx_t* audit_ctx,
             akv_ctx_t* akv_ctx)
{
  if (!tcm_ctx || !audit_ctx || !akv_ctx) {
    return TCM_EINVAL;
  }
  tcm_ctx->audit_ctx = audit_ctx;
  tcm_ctx->akv_ctx = akv_ctx;

  return 0;
}

void tcm_release(tcm_ctx_t* tcm_ctx)
{
}

int tcm_db_add(tcm_ctx_t* tcm_ctx,
               const char* key,
               const char* val)
{
  const uint8_t *audit_nonce;
  size_t audit_nonce_len;
  const char *audit_string;
  size_t audit_string_len;
  uint8_t audit_token[AUDIT_TOKEN_MAX];
  size_t audit_token_len = sizeof(audit_token);
  uint32_t cmd_handle;

  if (!tcm_ctx || !key || !val)
    return TCM_EINVAL;

  if (akv_begin_db_add(tcm_ctx->akv_ctx,
                       &cmd_handle,
                       &audit_nonce,
                       &audit_nonce_len,
                       &audit_string,
                       &audit_string_len,
                       key,
                       val)) {
    return TCM_EAKV;
  }

  if (audit_get_token(tcm_ctx->audit_ctx,
                      audit_nonce,
                      audit_nonce_len,
                      audit_string,
                      audit_string_len,
                      audit_token,
                      &audit_token_len)) {
    return TCM_EAUDIT;
  }

  if (akv_execute_db_add(tcm_ctx->akv_ctx,
                         cmd_handle,
                         audit_token,
                         audit_token_len)) {
    return TCM_EAKV;
  }

  return 0;
}

int main(void)
{
  tz_device_t tzDevice;
  tz_session_t tzPalSession;
  tz_uuid_t tzSvcId;
  int rv=0;

  /* tz_return_t trv; */
  /* hellopal(PAL_HELLO, NULL, NULL, &trv); */
  /* printf("got trv=%d\n", trv); */

  tv_tz_init(&tzDevice,
             &tzPalSession,
             &tzSvcId,
             &audited_kv_pal,
             PAGE_SIZE,
             PAGE_SIZE);

  tv_tz_teardown(&tzDevice,
                 &tzPalSession,
                 &tzSvcId);

  return rv;
} 
