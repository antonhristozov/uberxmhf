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

/**
 * AntiRollBack (ARB) Tools - Untrusted portion.
 *
 * These library calls are used by the untrusted portion of
 * applications that cooperate to achieve crash resilience and
 * anti-rollback of PAL state.
 */

#ifndef _LIBARBTOOLS_H_
#define _LIBARBTOOLS_H_

/* There is no explicit NVRAM location; this is hard-coded into
 * TrustVisor. Just use the relevant NV hypercalls. */

/* Latest state snapshot. This is just an opaque byte array. */

/* Handle. Irrelevant within a single application. It is presently the
 * application's responsibility to write things to disk as necessary. */

/* Request */

#define LAST_SNAPSHOT_FILENAME "last-snapshot.bin"
#define THIS_SNAPSHOT_FILENAME "this-snapshot.bin"
#define LAST_REQUEST_FILENAME "last-request.bin"
#define THIS_REQUEST_FILENAME "this-request.bin"

void print_hex(const char *prefix, const void *prtptr, size_t size);
long slurp_file(const char *filename, void **buf);
long puke_file(const char *filename, const void *bytes, long len);
void dump_stderr_from_pal(tz_operation_t *tzOp);


#endif /* _LIBARBTOOLS_H_ */

/* Local Variables: */
/* mode:c           */
/* indent-tabs-mode:'t */
/* tab-width:2      */
/* End:             */