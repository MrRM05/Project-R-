#ifndef GCC_TM_H
#define GCC_TM_H
#define TARGET_CPU_DEFAULT ((MASK_EXPLICIT_RELOCS)|MASK_RELAX_PIC_CALLS)
#ifndef LIBC_GLIBC
# define LIBC_GLIBC 1
#endif
#ifndef LIBC_UCLIBC
# define LIBC_UCLIBC 2
#endif
#ifndef LIBC_BIONIC
# define LIBC_BIONIC 3
#endif
#ifndef LIBC_MUSL
# define LIBC_MUSL 4
#endif
#ifndef MIPS_ISA_DEFAULT
# define MIPS_ISA_DEFAULT 3
#endif
#ifndef MIPS_ABI_DEFAULT
# define MIPS_ABI_DEFAULT ABI_O64
#endif
#ifdef IN_GCC
# include "options.h"
# include "insn-constants.h"
# include "config/vxworks-dummy.h"
# include "config/elfos.h"
# include "config/newlib-stdint.h"
# include "config/mips/mips.h"
# include "config/mips/elf.h"
# include "config/initfini-array.h"
#endif
#if defined IN_GCC && !defined GENERATOR_FILE && !defined USED_FOR_TARGET
# include "insn-flags.h"
#endif
#if defined IN_GCC && !defined GENERATOR_FILE
# include "insn-modes.h"
#endif
# include "defaults.h"
#endif /* GCC_TM_H */
