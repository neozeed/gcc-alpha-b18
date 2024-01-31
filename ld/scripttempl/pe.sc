# Linker script for PE.
if [ "x${RELOCATING}" = x ]
then
#  If this is a link -rU, we need to force the constructor list to exist;
#  give the customer what he asked for.
   OUTPUT_FORMAT=${LINK_FORMAT} :
   CONSTRUCTOR_FORMAT="
       ___CTOR_LIST__ = .; __CTOR_LIST__ = . ; 
			LONG (-1); *(.ctors); *(.ctor); LONG (0);
       ___DTOR_LIST__ = .; __DTOR_LIST__ = . ; 
			LONG (-1); *(.dtors); *(.dtor);  LONG (0);"
else
#  If this is a final link, we want to PROVIDE the constructor list symbols;
#  it might be the case that a prior link -rU already provided values.
   CONSTRUCTOR_FORMAT="
       PROVIDE(___CTOR_LIST__ = .); PROVIDE(__CTOR_LIST__ = .); 
			LONG (-1); *(.ctors); *(.ctor); LONG (0);
       PROVIDE(___DTOR_LIST__ = .); PROVIDE(__DTOR_LIST__ = .); 
			LONG (-1); *(.dtors); *(.dtor);  LONG (0);"
fi

cat <<EOF
OUTPUT_FORMAT(${OUTPUT_FORMAT})
${LIB_SEARCH_DIRS}

ENTRY(${ENTRY})

SECTIONS
{
  .text ${RELOCATING+ __section_alignment__ } : 
  {
    ${RELOCATING+ *(.init)}
    *(.text)
    ${RELOCATING+. = ALIGN(4);}
    ${CONSTRUCTING+$CONSTRUCTOR_FORMAT}
    ${RELOCATING+ *(.fini)}
    /* ??? Why is .gcc_exc here?  */
    ${RELOCATING+ *(.gcc_exc)}
    ${RELOCATING+ etext = .;}
    /* Grouped section support currently must be explicitly provided for
	in the linker script.  */
    *(.text\$)
    *(.gcc_except_table)
  }

  .data ${RELOCATING+ BLOCK(__section_alignment__) } :
  {
    ${RELOCATING+ __data_start__ = . }; 
    *(.data)
    *(.data2)
    ${RELOCATING+ __data_end__ = . }; 
    /* Grouped section support currently must be explicitly provided for
	in the linker script.  */
    *(.data\$)
  }

  .rdata ${RELOCATING+ BLOCK(__section_alignment__) } :
  {
    *(.rdata)
    /* Grouped section support currently must be explicitly provided for
	in the linker script.  */
    *(.rdata\$)
  }

  .pdata ${RELOCATING+ BLOCK(__section_alignment__) } :
  {
    *(.pdata)
    ;
  }

  .bss ${RELOCATING+ BLOCK(__section_alignment__) } :
  {
    ${RELOCATING+ __bss_start__ = . };
    *(.bss)
    *(COMMON)
    ${RELOCATING+ __bss_end__ = . };
  }

  .edata ${RELOCATING+ BLOCK(__section_alignment__) } :
  {
    *(.edata)
  }

  /DISCARD/ ${RELOCATING+ BLOCK(__section_alignment__) } :
  {
    *(.debug\$S)
    *(.debug\$T)
    *(.debug\$F)
    *(.drectve)
  }

  .idata ${RELOCATING+ BLOCK(__section_alignment__) } :
  {
    /* This cannot currently be handled with grouped sections.
	See pe.em:sort_sections.  */
    *(.idata\$2)
    *(.idata\$3)
    *(.idata\$4)
    *(.idata\$5)
    *(.idata\$6)
    *(.idata\$7)
  }
  .CRT ${RELOCATING+ BLOCK(__section_alignment__) } :
  {                                     
    /* Grouped sections are used to handle .CRT\$foo.  */
    *(.CRT\$)
  }
  .rsrc ${RELOCATING+ BLOCK(__section_alignment__) } :
  {                                     
    /* Grouped sections are used to handle .rsrc\$0[12].  */
    *(.rsrc\$)
  }

  .endjunk ${RELOCATING+ BLOCK(__section_alignment__) } :
  {
    /* end is deprecated, don't use it */
    ${RELOCATING+ end = .;}
    ${RELOCATING+ __end__ = .;}
  }

  .stab ${RELOCATING+ BLOCK(__section_alignment__) } ${RELOCATING+"(NOLOAD)"} : 
  {
    [ .stab ]
  }

  .stabstr ${RELOCATING+ BLOCK(__section_alignment__) } ${RELOCATING+"(NOLOAD)"} : 
  {
    [ .stabstr ]
  }

  .reloc ${RELOCATING+ BLOCK(__section_alignment__) } :
  {                                     
    *(.reloc)
  }
}
EOF
