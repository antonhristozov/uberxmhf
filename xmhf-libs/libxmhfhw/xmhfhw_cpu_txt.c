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

// xmhfhw_cpu_txt: CPU TXT functions
// authors: amit vasudevan (amitvasudevan@acm.org) and jonmccune@cmu.edu

#include <xmhf.h>
#include <xmhf-hwm.h>
#include <xmhfhw.h>
#include <xmhf-debug.h>


uint32_t __getsec_capabilities(uint32_t index)
{
    uint32_t cap;
    uint32_t eax=0, ebx=0, ecx=0, edx=0;

    eax = IA32_GETSEC_CAPABILITIES;
    ebx = index;

 CASM_FUNCCALL(xmhfhw_cpu_getsec,&eax, &ebx, &ecx, &edx);

    cap = eax;
//    __asm__ __volatile__ (IA32_GETSEC_OPCODE "\n"
//              : "=a"(cap)
//              : "a"(IA32_GETSEC_CAPABILITIES), "b"(index));

    return cap;
}


void __getsec_senter(uint32_t sinit_base, uint32_t sinit_size)
{
    uint32_t eax=0, ebx=0, ecx=0, edx=0;

    eax = IA32_GETSEC_SENTER;
    ebx = sinit_base;
    ecx = sinit_size;
    edx = 0;

 CASM_FUNCCALL(xmhfhw_cpu_getsec,&eax, &ebx, &ecx, &edx);


//    __asm__ __volatile__ (IA32_GETSEC_OPCODE "\n"
//			  :
//			  : "a"(IA32_GETSEC_SENTER),
//			    "b"(sinit_base),
//			    "c"(sinit_size),
//			    "d"(0x0));
}

void __getsec_sexit(void)
{

    uint32_t eax=0, ebx=0, ecx=0, edx=0;

    eax = IA32_GETSEC_SEXIT;

 CASM_FUNCCALL(xmhfhw_cpu_getsec,&eax, &ebx, &ecx, &edx);


//    __asm__ __volatile__ (IA32_GETSEC_OPCODE "\n"
//                          : : "a"(IA32_GETSEC_SEXIT));
}

void __getsec_wakeup(void)
{

    uint32_t eax=0, ebx=0, ecx=0, edx=0;

    eax = IA32_GETSEC_WAKEUP;

 CASM_FUNCCALL(xmhfhw_cpu_getsec,&eax, &ebx, &ecx, &edx);


//    __asm__ __volatile__ (IA32_GETSEC_OPCODE "\n"
//                          : : "a"(IA32_GETSEC_WAKEUP));
}



void __getsec_smctrl(void)
{
    uint32_t eax=0, ebx=0, ecx=0, edx=0;

    eax = IA32_GETSEC_SMCTRL;
    ebx = 0;

 CASM_FUNCCALL(xmhfhw_cpu_getsec,&eax, &ebx, &ecx, &edx);
//    __asm__ __volatile__ (IA32_GETSEC_OPCODE "\n"
//                          : : "a"(IA32_GETSEC_SMCTRL), "b"(0x0));
}


void __getsec_parameters(uint32_t index,
                         int* param_type,
                         uint32_t* peax,
                         uint32_t* pebx,
                         uint32_t* pecx){
    uint32_t eax=0, ebx=0, ecx=0, edx=0;

    eax = IA32_GETSEC_PARAMETERS;
    ebx = index;


 CASM_FUNCCALL(xmhfhw_cpu_getsec,&eax, &ebx, &ecx, &edx);


    if ( param_type != NULL )   *param_type = eax & 0x1f;
    if ( peax != NULL )         *peax = eax;
    if ( pebx != NULL )         *pebx = ebx;
    if ( pecx != NULL )         *pecx = ecx;

}

