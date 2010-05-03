/* processor.h cpu-specific definitions and macros for x86 */

/* Portions are: Copyright (c) 1994 Linus Torvalds */
/* Modified for SecVisor by Arvind Seshadri */

#ifndef __PROCESSOR_H
#define __PROCESSOR_H

/*
 * CPU vendor IDs
 */
#define VENDOR_INTEL 0

/* CPUID string for Intel CPUs */
#define INTEL_STRING_DWORD1 0x756E6547
#define INTEL_STRING_DWORD2 0x49656e69
#define INTEL_STRING_DWORD3 0x6c65746e

/*
 * EFLAGS bits
 */
#define EFLAGS_CF	0x00000001 /* Carry Flag */
#define EFLAGS_PF	0x00000004 /* Parity Flag */
#define EFLAGS_AF	0x00000010 /* Auxillary carry Flag */
#define EFLAGS_ZF	0x00000040 /* Zero Flag */
#define EFLAGS_SF	0x00000080 /* Sign Flag */
#define EFLAGS_TF	0x00000100 /* Trap Flag */
#define EFLAGS_IF	0x00000200 /* Interrupt Flag */
#define EFLAGS_DF	0x00000400 /* Direction Flag */
#define EFLAGS_OF	0x00000800 /* Overflow Flag */
#define EFLAGS_IOPL	0x00003000 /* IOPL mask */
#define EFLAGS_NT	0x00004000 /* Nested Task */
#define EFLAGS_RF	0x00010000 /* Resume Flag */
#define EFLAGS_VM	0x00020000 /* Virtual Mode */
#define EFLAGS_AC	0x00040000 /* Alignment Check */
#define EFLAGS_VIF	0x00080000 /* Virtual Interrupt Flag */
#define EFLAGS_VIP	0x00100000 /* Virtual Interrupt Pending */
#define EFLAGS_ID	0x00200000 /* CPUID detection flag */

/*
 * Intel CPU flags in CR0
 */
#define CR0_PE          0x00000001 /* Enable Protected Mode    (RW) */
#define CR0_MP          0x00000002 /* Monitor Coprocessor      (RW) */
#define CR0_EM          0x00000004 /* Require FPU Emulation    (RO) */
#define CR0_TS          0x00000008 /* Task Switched            (RW) */
#define CR0_ET          0x00000010 /* Extension type           (RO) */
#define CR0_NE          0x00000020 /* Numeric Error Reporting  (RW) */
#define CR0_WP          0x00010000 /* Supervisor Write Protect (RW) */
#define CR0_AM          0x00040000 /* Alignment Checking       (RW) */
#define CR0_NW          0x20000000 /* Not Write-Through        (RW) */
#define CR0_CD          0x40000000 /* Cache Disable            (RW) */
#define CR0_PG          0x80000000 /* Paging                   (RW) */


/*
 * Intel CPU features in CR3
 */
#define CR3_PCD		(1UL << 4)	/* page cache disable */
#define CR3_PWT		(1UL << 3)	/* page write through */

/*
 * Intel CPU features in CR4
 */
#define CR4_VME		0x0001	/* enable vm86 extensions */
#define CR4_PVI		0x0002	/* virtual interrupts flag enable */
#define CR4_TSD		0x0004	/* disable time stamp at ipl 3 */
#define CR4_DE		0x0008	/* enable debugging extensions */
#define CR4_PSE		0x0010	/* enable page size extensions */
#define CR4_PAE		0x0020	/* enable physical address extensions */
#define CR4_MCE		0x0040	/* Machine check enable */
#define CR4_PGE		0x0080	/* enable global pages */
#define CR4_PCE		0x0100	/* enable performance counters at ipl 3 */
#define CR4_OSFXSR      0x0200	/* enable fast FPU save and restore */
#define CR4_OSXMMEXCPT	0x0400	/* enable unmasked SSE exceptions */
#define CR4_VMXE        0x2000  /* enable VMX */

/*
 * Trap/fault mnemonics.
 */
#define TRAP_divide_error      0
#define TRAP_debug             1
#define TRAP_nmi               2
#define TRAP_int3              3
#define TRAP_overflow          4
#define TRAP_bounds            5
#define TRAP_invalid_op        6
#define TRAP_no_device         7
#define TRAP_double_fault      8
#define TRAP_copro_seg         9
#define TRAP_invalid_tss      10
#define TRAP_no_segment       11
#define TRAP_stack_error      12
#define TRAP_gp_fault         13
#define TRAP_page_fault       14
#define TRAP_spurious_int     15
#define TRAP_copro_error      16
#define TRAP_alignment_check  17
#define TRAP_machine_check    18
#define TRAP_simd_error       19
#define TRAP_deferred_nmi     31

/* CPUID flags */
#define EDX_PAE	6
#define EDX_XD	20
#define EDX_NP 	0

#define ECX_SMX 6
#define ECX_VMX 5

#ifndef __ASSEMBLY__

typedef struct {
  u16 isrLow;
  u16 isrSelector;
  u8  count;
  u8  type;
  u16 isrHigh;
} __attribute__ ((packed)) idtentry_t;



typedef struct cpu_user_regs {
  uint32_t ebx;
  uint32_t ecx;
  uint32_t edx;
  uint32_t esi;
  uint32_t edi;
  uint32_t ebp;
  uint32_t eax;
  uint16_t error_code;    /* private */
  uint16_t entry_vector;  /* private */
  uint32_t eip;
  uint16_t cs;
  uint8_t  saved_upcall_mask;
  uint8_t  _pad0;
  uint32_t eflags;        /* eflags.IF == !saved_upcall_mask */
  uint32_t esp;
  uint16_t ss, _pad1;
  uint16_t es, _pad2;
  uint16_t ds, _pad3;
  uint16_t fs, _pad4;
  uint16_t gs, _pad5;
} cpu_user_regs_t;

typedef struct {
  unsigned long backlink;
  unsigned long esp0;
  unsigned short ss0;
  unsigned short res0;
  unsigned long esp1;
  unsigned short ss1;
  unsigned short res1;
  unsigned long esp2;
  unsigned short ss2;
  unsigned short res2;
  unsigned long cr3;
  unsigned long eip;
  unsigned long eflags;
  unsigned long eax, ecx, edx, ebx;
  unsigned long esp, ebp, esi, edi;
  unsigned short es;
  unsigned short res3;
  unsigned short cs;
  unsigned short res4;
  unsigned short ss;
  unsigned short res5;
  unsigned short ds;
  unsigned short res6;
  unsigned short fs;
  unsigned short res7;
  unsigned short gs;
  unsigned short res8;
  unsigned short ldt;
  unsigned short res9;
  unsigned short debug;
  unsigned short iopermbase;    
} __attribute__ ((packed)) TSS;


typedef struct {
  unsigned short limit0_15;
  unsigned short baseAddr0_15;
  unsigned char baseAddr16_23;
  unsigned char attributes1;
  unsigned char limit16_19attributes2;    
  unsigned char baseAddr24_31;
} __attribute__ ((packed)) TSSENTRY;

typedef struct {
	unsigned long eip;
	unsigned long cs;
	unsigned long eflags;
	unsigned long esp;
	unsigned long ss;
	unsigned long es;
	unsigned long ds;
	unsigned long fs;
	unsigned long gs;
} __attribute__ ((packed)) FAULTFRAME; 


typedef struct {
	unsigned long ebp;
	unsigned long edi;
	unsigned long esi;
	unsigned long edx;
	unsigned long ecx;
	unsigned long ebx;
	unsigned long eax;
	unsigned long esp;
} __attribute__ ((packed)) INTRREGS; 


#define get_eflags(x)  __asm__ __volatile__("pushfl ; popl %0 ":"=g" (x): /* no input */ :"memory")
#define set_eflags(x) __asm__ __volatile__("pushl %0 ; popfl": /* no output */ :"g" (x):"memory", "cc")

/*
 * Generic CPUID function
 */
#if 1
#define cpuid(op, eax, ebx, ecx, edx)		\
({						\
  __asm__("cpuid"				\
          :"=a"(*(eax)), "=b"(*(ebx)), "=c"(*(ecx)), "=d"(*(edx))	\
          :"0"(op), "2" (0));			\
})

#else
static inline void cpuid(u32 op, u32 *eax, u32 *ebx, u32 *ecx, u32 *edx)
{
  __asm__("cpuid"
          :"=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
          :"0"(op), "2" (0));
}

/* Some CPUID calls want 'count' to be placed in ecx */
static inline void cpuid_count( int op, int count,
                               unsigned int *eax,
                               unsigned int *ebx,
                               unsigned int *ecx,
                               unsigned int *edx)
{
  __asm__("cpuid"
          : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
          : "0" (op), "c" (count));
}

/*
 * CPUID functions returning a single datum
 */
static inline unsigned int cpuid_eax(unsigned int op)
{
  unsigned int eax;

  __asm__("cpuid"
          : "=a" (eax)
          : "0" (op)
          : "%ebx", "%ecx", "%edx");
  return eax;
}
static inline unsigned int cpuid_ebx(unsigned int op)
{
  unsigned int eax, ebx;

  __asm__("cpuid"
          : "=a" (eax), "=b" (ebx)
          : "0" (op)
          : "%ecx", "%edx" );
  return ebx;
}
static inline unsigned int cpuid_edx(unsigned int op)
{
  unsigned int eax, edx;

  __asm__("cpuid"
          : "=a" (eax), "=d" (edx)
          : "0" (op)
          : "%ebx", "%ecx");
  return edx;
}


#endif



#endif /*ifndef __ASSEMBLY__ */

#endif /* __PROCESSOR_H */
