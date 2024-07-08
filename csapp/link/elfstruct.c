typedef struct { 
    int   name;      /* string table offset */ 
    char  type:4,    /* function or data (4 bits) */ 
	  binding:4;       /* local or global (4 bits) */ 
    char  reserved;  /* unused */  
    short section;   /* section header index */
    long  value;     /* section offset or absolute address */ 
    long  size;      /* object size in bytes */ 
} Elf64_Symbol;
