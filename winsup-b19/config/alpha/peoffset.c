#include <Windows.h>

static	PIMAGE_DOS_HEADER dosHeader	;
static	char name[16];
static	PIMAGE_NT_HEADERS  pNTHeader;
static	PIMAGE_SECTION_HEADER psection,tsection;

GetpeOffset(char *module,int *bs,int *be,
		int *ds,int *de,int *ls,int *le) {
	HANDLE base;
	int i,loops;
	int addr,len;
	int bss_start,bss_end,data_start,data_end;
	int l_data_start,l_data_end;
	bss_start=bss_end=data_start=data_end=0;
	l_data_start=l_data_end=0;
 	base=GetModuleHandle(module);

	if (base==INVALID_HANDLE_VALUE) {
		return -1;
	}

	dosHeader = (PIMAGE_DOS_HEADER)base;
	addr=(int)dosHeader+dosHeader->e_lfanew;
	pNTHeader = (struct _IMAGE_NT_HEADERS *)addr;
	psection = IMAGE_FIRST_SECTION ( pNTHeader );
	tsection=psection;
	loops=0;
	while (loops <pNTHeader->FileHeader.NumberOfSections ) {
		for (i=0;i<sizeof(name);i++) name[i]='\0';
		for (i=0;i<8;i++) name[i]=tsection->Name[i];
		if (strcmp(name,".bss")==0) {
			bss_start= tsection->VirtualAddress;
			bss_start += (int)base; 
			bss_end=tsection->Misc.VirtualSize;
			bss_end +=bss_start;		 	
		}
		if (strcmp(name,".data")==0) {
			data_start= tsection->VirtualAddress;
			data_start += (int)base; 
			data_end=tsection->Misc.VirtualSize;
			data_end +=data_start;		 
		}
		if (strcmp(name,".ldata")==0) {
			l_data_start= tsection->VirtualAddress;
			l_data_start += (int)base; 
			l_data_end=tsection->Misc.VirtualSize;
			l_data_end +=l_data_start;		 
		}
	    addr=(int)tsection;
		len= sizeof(IMAGE_SECTION_HEADER);
		addr+=len;
		tsection=(struct _IMAGE_SECTION_HEADER *)addr;
		loops++;
	}
/* bs, be now .ldata begin end */
	*bs=bss_start;
	*be=bss_end;
	*ds=data_start;
	*de=data_end;
	*ls=l_data_start;
	*le=l_data_end;
	return 0;
}

