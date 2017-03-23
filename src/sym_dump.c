#include "ft_nm_otool.h"

void	dump_section_64(struct section_64 *sect)
{
	ft_printf("{blu}{inv}struct section_64{eoc}: segname=[%s], sectname=[%s]\n",
			sect->segname, sect->sectname);
}

void	dump_segment_64(struct segment_command_64 *seg, void *file)
{
	uint32_t			nsects;
	uint32_t			i;
	struct section_64	*sect;

	(void)file;
	nsects = seg->nsects;
	ft_printf("{blu}{inv}struct segment_command_64{eoc}: segname=[%s], nsects=[%i]\n", seg->segname, nsects);
	sect = (void*)(seg + 1);
	for (i = 0; i < nsects; i++)
	{
		dump_section_64(sect);
		sect = sect + 1;
	}
}

void	dump_symtab(struct symtab_command *symtab, void *file)
{
	int						i;
	char					*stringtable;
	char					*string;
	struct nlist_64			*array;

	ft_printf("{blu}{inv}struct symtab_command{eoc}\n");
	stringtable = file + symtab->stroff;
	array = (struct nlist_64*)(file + symtab->symoff);
	i = -1;
	while (++i < (int)symtab->nsyms)
	{
		string = stringtable + array[i].n_un.n_strx;
		ft_printf("%s\n", string);
	}
}

void	dump_dysymtab(struct dysymtab_command *dysymtab, void *file)
{
	(void)file;
	ft_printf("{blu}{inv}struct dysymtab_command{eoc}\n");
	ft_printf("ilocalsym     %i\n", dysymtab->ilocalsym);
	ft_printf("nlocalsym     %i\n", dysymtab->nlocalsym);
	ft_printf("iextdefsym    %i\n", dysymtab->iextdefsym);
	ft_printf("nextdefsym    %i\n", dysymtab->nextdefsym);
	ft_printf("iundefsym     %i\n", dysymtab->iundefsym);
	ft_printf("nundefsym     %i\n", dysymtab->nundefsym);
	ft_printf("---------------\n");
	ft_printf("ntoc          %i\n", dysymtab->ntoc);
	ft_printf("nmodtab       %i\n", dysymtab->nmodtab);
	ft_printf("nextrefsyms   %i\n", dysymtab->nextrefsyms);
	ft_printf("nmodtab       %i\n", dysymtab->nmodtab);
	ft_printf("nindirectsims %i\n", dysymtab->nindirectsyms);
	ft_printf("nextrel       %i\n", dysymtab->nextrel);
	ft_printf("nlocrel       %i\n", dysymtab->nlocrel);
	ft_putendl("");
}
