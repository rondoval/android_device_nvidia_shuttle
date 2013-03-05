cmd_/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/linux/ar6000.mod.o := /home/rondoval/android/advent_cm10.1/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-gcc -Wp,-MD,/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/linux/.ar6000.mod.o.d  -nostdinc -isystem /home/rondoval/android/advent_cm10.1/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include -I/home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include -Iarch/arm/include/generated -Iinclude  -I/home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include -include /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/kconfig.h   -I/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/linux -D__KERNEL__ -mlittle-endian   -I/home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/mach-tegra/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -marm -fno-dwarf2-cfi-asm -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fomit-frame-pointer -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -D__linux__ -Wno-error -DANDROID_ECLAIR_ENV=1   -I/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/include   -I/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/../include   -I/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/../include/AR6002   -I/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/wlan/include   -I/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/linux/include   -I/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/   -I/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/bmi/include -DLINUX -DDEBUG -D__KERNEL__ -DTCMD -DSEND_EVENT_TO_APP -DUSER_KEYS -DNO_SYNC_FLUSH -DANDROID_ENV -DKERNEL_2_6   -I/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/hif/sdio/linux_sdio/include -DSDIO   -I/src/include  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(ar6000.mod)"  -D"KBUILD_MODNAME=KBUILD_STR(ar6000)" -DMODULE  -c -o /home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/linux/ar6000.mod.o /home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/linux/ar6000.mod.c

source_/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/linux/ar6000.mod.o := /home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/linux/ar6000.mod.c

deps_/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/linux/ar6000.mod.o := \
    $(wildcard include/config/module/unload.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/kconfig.h \
    $(wildcard include/config/h.h) \
    $(wildcard include/config/.h) \
    $(wildcard include/config/foo.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/module.h \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/debug/set/module/ronx.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/types.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/int-ll64.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/bitsperlong.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/bitsperlong.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/posix_types.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/stddef.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/compiler-gcc4.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/posix_types.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/const.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/stat.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/stat.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/compaction.h) \
  /home/rondoval/android/advent_cm10.1/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include/stdarg.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/linkage.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/linkage.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/bitops.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/bitops.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/system.h \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/cpu/xsc3.h) \
    $(wildcard include/config/cpu/fa526.h) \
    $(wildcard include/config/arch/has/barriers.h) \
    $(wildcard include/config/arm/dma/mem/bufferable.h) \
    $(wildcard include/config/cpu/sa1100.h) \
    $(wildcard include/config/cpu/sa110.h) \
    $(wildcard include/config/cpu/v6.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/typecheck.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/irqflags.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/hwcap.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/outercache.h \
    $(wildcard include/config/outer/cache/sync.h) \
    $(wildcard include/config/outer/cache.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/cmpxchg-local.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/bitops/non-atomic.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/bitops/fls64.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/bitops/sched.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/bitops/hweight.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/bitops/arch_hweight.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/bitops/const_hweight.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/bitops/lock.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/bitops/le.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/byteorder.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/byteorder/little_endian.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/swab.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/swab.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/byteorder/generic.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/printk.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/init.h \
    $(wildcard include/config/hotplug.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/dynamic_debug.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/div64.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/cache.h \
    $(wildcard include/config/arm/l1/cache/shift.h) \
    $(wildcard include/config/aeabi.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/seqlock.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/vfpv3.h) \
    $(wildcard include/config/iwmmxt.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/stringify.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/bottom_half.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/spinlock_types.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/spinlock_types.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/prove/rcu.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/rwlock_types.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/spinlock.h \
    $(wildcard include/config/thumb2/kernel.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/processor.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/arm/errata/754327.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/hw_breakpoint.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/rwlock.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/inline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/atomic.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/atomic-long.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/math64.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/kmod.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/gfp.h \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/arch/populates/node/map.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/wait.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/current.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/nodemask.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/bitmap.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/string.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/generated/bounds.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/page.h \
    $(wildcard include/config/cpu/copy/v3.h) \
    $(wildcard include/config/cpu/copy/v4wt.h) \
    $(wildcard include/config/cpu/copy/v4wb.h) \
    $(wildcard include/config/cpu/copy/feroceon.h) \
    $(wildcard include/config/cpu/copy/fa.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/cpu/copy/v6.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/glue.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/memory.h \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/task/size.h) \
    $(wildcard include/config/dram/size.h) \
    $(wildcard include/config/dram/base.h) \
    $(wildcard include/config/have/tcm.h) \
    $(wildcard include/config/arm/patch/phys/virt.h) \
    $(wildcard include/config/arm/patch/phys/virt/16bit.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/mach-tegra/include/mach/memory.h \
    $(wildcard include/config/arch/tegra/2x/soc.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/sizes.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/sizes.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/memory_model.h \
    $(wildcard include/config/sparsemem/vmemmap.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/getorder.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/notifier.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/errno.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/errno.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/errno.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/errno-base.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/rwsem-spinlock.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/srcu.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/smp.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/pfn.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/percpu.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/percpu.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/topology.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/asm-generic/topology.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/jiffies.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/timex.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/param.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/timex.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/mach-tegra/include/mach/timex.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/sysctl.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tiny/preempt/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/preempt/rt.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/completion.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/rcutree.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/elf.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/elf-em.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/elf.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/user.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/kobject.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/sysfs.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/kobject_ns.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/kref.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/tracepoint.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/export.h \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/arch/arm/include/asm/module.h \
    $(wildcard include/config/arm/unwind.h) \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/trace/events/module.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/trace/define_trace.h \
  /home/rondoval/android/advent_cm10.1/kernel/nvidia/shuttle/include/linux/vermagic.h \
  include/generated/utsrelease.h \

/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/linux/ar6000.mod.o: $(deps_/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/linux/ar6000.mod.o)

$(deps_/home/rondoval/android/advent_cm10.1/device/nvidia/shuttle/wlan/AR6kSDK.2.2.1.151/host/os/linux/ar6000.mod.o):
