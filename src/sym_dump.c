#include "ft_nm_otool.h"

void	dump_section_64(struct section_64 *sect)
{
	ft_printf("{blu}{inv}struct section_64{eoc} sectname=[%s]\n",
			sect->sectname);
}

void	dump_segment_64(t_machodata *data, struct segment_command_64 *seg)
{
	uint32_t			nsects;
	uint32_t			i;
	struct section_64	*sect;

	(void)data;
	nsects = seg->nsects;
	ft_printf("{blu}{inv}struct segment_command_64{eoc} segname=[%s], nsects=[%i]\n", seg->segname, nsects);
	sect = (void*)(seg + 1);
	for (i = 0; i < nsects; i++)
	{
		dump_section_64(sect);
		sect = sect + 1;
	}
}


void	dump_symbol(t_machodata *data, t_symbol *symbol)
{
	uint8_t		n_type;        /* type flag, see below */
	uint8_t		n_sect;        /* section number or NO_SECT */
	uint16_t	n_desc;       /* see <mach-o/stab.h> */
	uint64_t	n_value;      /* value of this symbol (or stab offset) */
	char		*sect_name;

	n_type = symbol->nlist.n_type;
	n_sect = symbol->nlist.n_sect;
	n_desc = symbol->nlist.n_desc;
	n_value = symbol->nlist.n_value;
	DG("check");
	sect_name = n_sect ?
		(*(struct section_64**)ft_lst_at(data->sects, n_sect - 1)->content)->sectname : NULL;
	DG("check2");
	ft_printf("%i:\t%03b|%b|%x|%b\
	\t%i(%s) \t%#06x \t%x %-20s\n",
			symbol->pos,
			(n_type & N_STAB) >> 5, (n_type & N_PEXT) >> 4,
			n_type & N_TYPE, n_type & N_EXT,
			n_sect, sect_name, n_desc, n_value,
			symbol->string);
}

void	dump_machheader_64(t_machodata *data)
{
	uint32_t				ncmds;
	uint32_t				i;
	struct load_command		*lc;
	struct mach_header_64	*header;

	header = data->file;
	ncmds = header->ncmds;
	lc = (void*)(header + 1);
	for (i = 0; i < ncmds; i++)
	{
		if (lc->cmd == LC_SYMTAB)
			dump_symtab(data, (struct symtab_command*)lc);
		else if (lc->cmd == LC_DYSYMTAB)
			dump_dysymtab(data, (struct dysymtab_command*)lc);
		else if (lc->cmd == LC_SEGMENT_64)
			dump_segment_64(data, (struct segment_command_64*)lc);
		lc = (void*)lc + lc->cmdsize;
	}
}
