
ENTRY(render)
SECTIONS {
  . = 0x4d560;
  .text : { *(.text.render) *(.text*) *(.rodata*) }
  . = 0x50000;
  .weights : { *(.weights) }
  /DISCARD/ : { *(.ARM.exidx*) *(.comment) *(.ARM.attributes) }
}
