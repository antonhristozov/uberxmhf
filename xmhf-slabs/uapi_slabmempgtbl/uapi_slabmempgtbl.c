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
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in
 * the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the names of Carnegie Mellon or VDG Inc, nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
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

/*
 * slab memory pagetable uAPI
 *
 * author: amit vasudevan (amitvasudevan@acm.org)
 */

#include <xmhf.h>
#include <xmhf-hic.h>
#include <xmhf-debug.h>

#include <xmhfhicslab.h>
#include <xc.h>
#include <uapi_slabmempgtbl.h>



/////
void slab_main(slab_params_t *sp){

    xmhf_uapi_params_hdr_t *uapiphdr = (xmhf_uapi_params_hdr_t *)sp->in_out_params;

    switch(uapiphdr->uapifn){

       case XMHF_HIC_UAPI_MEMPGTBL_GETENTRY:{
            xmhf_uapi_slabmempgtbl_entry_params_t *smempgtblentryp =
                (xmhf_uapi_slabmempgtbl_entry_params_t *)sp->in_out_params;

            {
                u64 pdpt_index = pae_get_pdpt_index(smempgtblentryp->gpa);
                u64 pd_index = pae_get_pdt_index(smempgtblentryp->gpa);
                u64 pt_index = pae_get_pt_index(smempgtblentryp->gpa);
                smempgtblentryp->entry =
                    _dbuf_mempgtbl_pt[smempgtblentryp->dst_slabid][pdpt_index][pd_index][pt_index];
            }

        }
        break;


        case XMHF_HIC_UAPI_MEMPGTBL_SETENTRY:{
            xmhf_uapi_slabmempgtbl_entry_params_t *smempgtblentryp =
                (xmhf_uapi_slabmempgtbl_entry_params_t *)sp->in_out_params;

            {
                u64 pdpt_index = pae_get_pdpt_index(smempgtblentryp->gpa);
                u64 pd_index = pae_get_pdt_index(smempgtblentryp->gpa);
                u64 pt_index = pae_get_pt_index(smempgtblentryp->gpa);
                _dbuf_mempgtbl_pt[smempgtblentryp->dst_slabid][pdpt_index][pd_index][pt_index]
                    = smempgtblentryp->entry;

            }

        }
        break;



        default:
            _XDPRINTF_("UAPI_SLABMEMPGTBL[%u]: Unknown uAPI function %x. Halting!\n",
                    (u16)sp->cpuid, uapiphdr->uapifn);
            HALT();
            return;
    }


}
