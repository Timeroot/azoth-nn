
ENTRY(render)
SECTIONS {
  . = 0x4d520;
  .text : { *(.text.render) *(.text*) *(.rodata*) *(.data*) }
  /DISCARD/ : { *(.ARM.exidx*) *(.comment) }
}
