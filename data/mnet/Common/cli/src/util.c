#include <vxworks.h>
#include <stdioLib.h>
#include <taskLib.h>
#include <tyLib.h>
#include <lstLib.h>
#include <inetLib.h>    /* for INET_ADDR_LEN */
#include <timers.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <../include/cli_parser_private.h>
#include <../include/pstypes.h>
#include <../include/psvxif.h>
#include <../include/imsg.h>
#include <../include/imc.h>
#include <../include/cli_parser_api.h>
#include <../include/address.h>
#include <../include/parsertypes.h>
#include <../include/config.h>


/*
 * null
 * check for null string
 */

boolean null (const char *s)
{
    char c;

    if (s)
                while ((c = *s++) != '\0')
                        if ((c != ' ') && (c != '\t'))
                                return(FALSE);
    return(TRUE);
}


/*
 * deblank
 * Remove leading white space
 */

char *
deblank (const char *s)
{
    if (!s)
                return((char *)s);
 
    while (*s == ' ' || *s == '\t')
                ++s;
 
    return((char *)s);
}



/*
 * partialmatch
 * Returns TRUE if "unknown" is a proper substring of "known"
 */

boolean partialmatch (char const *known, char *unknown)
{                                                                               /* see if unknown <= known */
    char k, u;

    if (null(unknown))                                  /* null string never matches */
                return(FALSE);
    unknown = (char *)deblank(unknown);
    while ((k = *known++)) {
                if (!(u = *unknown++)) {
                        return(TRUE);                           /* u < known OK */
                } else {
                        if (toupper(k) != toupper(u))
                                return(FALSE);
                }
    }
    if (*unknown)                                               /* known exhausted */
                return(FALSE);                                  /* unknown > known */
    return(TRUE);                                               /* unknown == known */
}


char *
address_string (ulong address,char *buf)
{
  sprintf(buf, "%d.%d.%d.%d",
		     (address >> 24) & 0xff, (address >> 16) & 0xff,
		     (address >> 8) & 0xff, address & 0xff);

  return buf;
}


#ifdef IOS_PARSER


/*
 * parse_unsigned
 * Parse an unsigned number.
 * If number starts with '0x', interpret as hexadecimal.
 * If number starts with '0', interpret as octal.
 * Anything else is assigned to be unsigned decimal.
 * Returns -1 on error.
 */

ulong parse_unsigned (char *buff, boolean *okflag)
{
    char c;
    ulong num;
    char *startptr;

    *okflag = FALSE;

    if (null(buff))
                return(-1);
    buff = deblank(buff);
    num = 0;
    c = *buff++;
    if (c == '0') {

                /*
                 * If '0x', we've parsed a hexadecimal number
                 */
                if ((*buff == 'x') || (*buff == 'X')) {
                        buff++;
                        c = toupper(*buff++);
                        startptr = buff;
                        while (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'F'))) {
                                if ((c >= '0') && (c <= '9')) 
                                        num = num*16 + (c - '0');
                                else
                                        num = num*16 + (c - '7');
                                c = toupper(*buff++);
                        }
                        if ((buff == startptr) || (term_char(c) == FALSE))
                                return(-1);
                        *okflag = TRUE;
                        return(num);
                }
        
                /*
                 * Check for an octal number, or just zero.
                 */
                startptr = buff-1;
                while ((c >= '0') && (c <= '7')) {
                        num = num*8 + (c - '0');
                        c = *buff++;
                }
                if (buff == startptr || (term_char(c) == FALSE))
                        return(-1);
                *okflag = TRUE;
                return(num);
    }

    /*
     * No leading zero, looks like a positive decimal number.
     */
    startptr = buff;
    while ((c >= '0') && (c <= '9')) {
                num = num*10 + (c - '0');
                c = *buff++;
    }
    if ((buff == startptr) || (term_char(c) == FALSE))
                return(-1);
    *okflag = TRUE;
    return(num);
}
/*
 * parse_signed
 * Parse an unsigned number.
 * If number starts with '0x', interpret as hexadecimal.
 * If number starts with '0', interpret as octal.
 * Anything else is assigned to be unsigned decimal.
 * Returns OKFLAG=FALSE on error else okflag=TRUE.
 */

ulong parse_signed (
                                        char *buff,
                                        boolean *okflag)
{
    char c;
    ulong num;
    char *startptr;
    int   sign = 1;

    *okflag = FALSE;

    if (null(buff))
                return(0);

    buff = deblank(buff);
    num = 0;

    while ((c = *buff++) == '+')
                ;
    while ((c = *buff++) == '-')
                sign = sign * -1;

    if (c == '0') {

                /*
                 * If '0x', we've parsed a hexadecimal number
                 */
                if ((*buff == 'x') || (*buff == 'X')) {
                        buff++;
                        c = toupper(*buff++);
                        startptr = buff;
                        while (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'F'))) {
                                if ((c >= '0') && (c <= '9')) 
                                        num = num*16 + (c - '0');
                                else
                                        num = num*16 + (c - '7');
                                c = toupper(*buff++);
                        }
                        if ((buff == startptr) || (term_char(c) == FALSE))
                                return(0);
                        *okflag = TRUE;
                        return(num);
                }
        
                /*
                 * Check for an octal number, or just zero.
                 */
                startptr = buff-1;
                while ((c >= '0') && (c <= '7')) {
                        num = num*8 + (c - '0');
                        c = *buff++;
                }
                if (buff == startptr || (term_char(c) == FALSE))
                        return(0);
                *okflag = TRUE;
                return(num*sign);
    }

    /*
     * No leading zero, looks like a positive decimal number.
     */
    startptr = buff;
    while ((c >= '0') && (c <= '9')) {
                num = num*10 + (c - '0');
                c = *buff++;
    }
    if ((buff == startptr) || (term_char(c) == FALSE))
                return(0);
    *okflag = TRUE;
    return(num*sign);
}

/*
 * parse_decimal_long
 * Parse an unsigned decimal number.
 * Returns -1 on error.
 */

ulong parse_decimal_long (char *buff, boolean *okflag)
{
    char c;
    ulong num;
    char *startptr;

    *okflag = FALSE;

    if (null(buff))
                return(-1);
    buff = deblank(buff);
    num = 0;
    c = *buff++;

    startptr = buff;
    while ((c >= '0') && (c <= '9')) {
                num = num*10 + (c - '0');
                c = *buff++;
    }
    if (buff == startptr)
                return(-1);
    *okflag = TRUE;
    return(num);
}

/*
 * parse_hex_long
 * Parse a 32 bit hex number from a string buffer.  Return 0 if a bad number
 */

ulong parse_hex_long (char *buff)
{
    char c;
    ulong num;
    char *startptr;

    if (null(buff))
                return(0);
    buff = deblank(buff);
    num = 0;
    c = toupper(*buff++);
    startptr = buff;
    while (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'F'))) {
                if ((c >= '0') && (c <= '9')) 
                        num = num*16 + (c - '0');
                else
                        num = num*16 + (c - '7');
                c = toupper(*buff++);
    }
    if ((buff == startptr) ||
                (c != '.' && c != ':' && term_char(c) == FALSE) )
                return(0L);
    return(num);
}

/*
 * octet
 * parse one octet of a protocol address (IP, DECnet, etc.).
 * Returns valid char pointer on success, nil pointer otherwise
 */

char *octet (char *ptr, ulong *address, char brkchar)
{
    ulong i = 0;                                                /* accumulate number here */
    char c;                                                             /* get first character */

    if (null(ptr))                                              /*  make sure pointer is reasonable */
                return(NULL);
    c = *ptr++;
    while ((c >= '0') && (c <= '9')) {  /* while it's a number */
                i = i*10 + ((int) c - '0');             /* add a digit */
                c = *ptr++;                                             /* get next character */
    }
    if ((i <= 255) && (c == brkchar)) { /* sanity and break check */
                *address = (*address << 8) + i; /* form more of the address */
                return(ptr);                                    /* give a good return */
    } else
                return(NULL);                                   /* bad number or termination */
}

/*
 * t_number
 * Return TRUE if string is a number
 */

boolean t_number (char *s)
{
    char c;

    if (null(s))
                return(FALSE);
    s = deblank(s);
    c = *s++;
    while ((term_char(c) == FALSE)) {
                if (c < '0' || c > '9')
                        return(FALSE);
                c = *s++;
    }
    return(TRUE);
}

/*
 * notset
 * Given a non-zero integer argument, print as a decimal number.
 * If zero, as the string "not set".
 */

void notset (int arg)
{
    if (arg == 0)
                printf("not set");
    else
                printf("%d", arg);
}

/*
 * is_printable_string
 * Is this a printable ascii string?
 * Return FALSE if any byte in the supposed string is not an ascii
 * printable character, else, return TRUE.
 * The NULL string is not considered a string by this routine.
 */

boolean is_printable_string (const char *s, int size)
{
    char ch;
    int i;

    if (!s || !size)
                return(FALSE);
    for (i=0; i<size; i++) {
                ch = *s++;
                if (!isprint(ch))                               /* check for printable ascii character */
                        return(FALSE);
    }
    return(TRUE);                                               /* All characters are ascii printable*/
}

/*
 * int_array_op
 * Perform addition and deletion operations on an arbitrary sized
 * integer array.
 *
 * Return TRUE if operation succeeded; FALSE otherwise.
 *
 * add is a boolean to add to the array. If FALSE, remove from array.
 */

boolean int_array_op (int *array, int *index, int maxx, int value,
                                          boolean add)
{
    int i;

    for (i = 0; i < *index; i++)
                if (array[i] == value)
                        break;
    if (!add) {
                if (i >= *index)
                        return(FALSE);
                if (i != maxx - 1)
                        while (i < maxx - 1) {
                                array[i] = array[i+1];
                                i++;
                        }
                (*index)--;
    } else if (i >= *index) {                   /* not found in list */
                if (i == maxx - 1)
                        return(FALSE);
                array[*index] = value;
                (*index)++;
    }
    return(TRUE);
}

/*
 * strmatch
 * If nullok is non zero, null string will match
 */

boolean strmatch (char *str1, char *cmd, boolean nullok)
{
    char c, d;

    if (null(str1))                                             /* if a null pointer */
                str1 = "";                                              /* make it instead reference a null string */
    str1 = deblank(str1);
    if (!nullok) {
                c = *str1;
                d = *cmd;
                if (c == '\0' || d == '\0')             /* one is empty */
                        if (c || d)
                                return(FALSE);                  /* one is not null */
                        else
                                return(TRUE);                   /* nulls can only match each other */
    }

    /*
     * return equal if equal up to a space
     */
    d = '\0';                                                   /* in case first c is \0 */
    while ((c = *str1++) && (d = *cmd++) && c != ' ' && d != ' ')
                if (toupper(c) != toupper(d))
                        return(FALSE);

    /*
     * Return FALSE if string is longer than command and we are not
     * at a space, eg. "testx" will NOT match "test" but "test xxx" will.
     */
    if (d == '\0' && c != '\0' && c != ' ')
                return(FALSE);
    return(TRUE);
}

/*
 * ExactToSPsmatch
 * Exact match up to a ' ' in source string
 */

boolean ExactToSPsmatch (char *s, char *t)
{
    char c, d;

    while (TRUE) {
                c = *s++;
                d = *t++;
                if (c == ' ' && d == '\0')
                        return(TRUE);                           /* matched up to a space */
                if (!c || !d)
                        break;                                          /* end of at least one string */
                if (toupper (c) != toupper (d))
                        return(FALSE);
    }
    if (c || d)
                return(FALSE);                                  /* only partial match */
    return(TRUE);
}

/*
 * nmatch
 * Find the number of matches to str, and return that number.
 */

int nmatch (register char *str, char *const cmds[], const ushort cmdflags[],
                        int ncmds, int *index)
{
    int j;
    int i, len, minlen;

    if (null(str))
                str = "";
    i = 0;
    minlen = 1000;                                              /* large enough */
    str = deblank(str);
    for (j = 0; j < ncmds; ++j) {
                if (strmatch(str, cmds[j], FALSE)) {
                        len = strlen(cmds[j]);
                        if (len < minlen) {                     /* keep minimums */
                                minlen = len;
                                *index = j;
                        }
                        i++;
                }
    }
    if ((i > 1) && ExactToSPsmatch(str, cmds[*index]))
                return(TRUE);
    return(i);
}

/*
 * findarg
 * Return a string pointer to a spot after a space
 */

char *findarg (char *str)
{
    if (null(str))
                return(NULL);
    str = deblank(str);
    while (*str && *str++ != ' ');              /* to end or after first space */
    if (!*str)
                return(NULL);
    str = (char *) deblank(str);
    return(str);
}

/*
 * return_false, return_true
 * Stub functions that always return TRUE or FALSE
 */

boolean return_false (void *dummy, ...)
{
    return(FALSE);
}

boolean return_true (void *dummy, ...)
{
    return(TRUE);
}

fuzzy return_fuz_false (void *dummy, ...)
{
    return(FUZ_FALSE);
}
fuzzy return_fuz_true (void *dummy, ...)
{
    return(FUZ_TRUE);
}

uchar *return_null (void *dummy, ...)
{
    return(NULL);
}

long return_zero (void)
{
    return(0L);
}

long return_one (void)
{
    return(1L);
}

void return_nothing (void *dummy, ...)
{
    return;
}

/*
 * instring
 */
boolean instring (char *query, char *string)
{
    char *p, *q;
    int i, limit;
    
    /* Quick tests */
    if (query == NULL || *query == '\0')
                return(TRUE);
    if (string == NULL || *string == '\0')
                return(FALSE);

    limit = strlen(string) - strlen(query) + 1;
    for (i = 0; i < limit; i++) {
                p = query;
                q = string+i;
                while (tolower(*p++) == tolower(*q++))
                        if (*p == '\0')
                                return(TRUE);
    }
    return(FALSE);
}

/*
 * str_cat_with_realloc
 *
 * Concatenate source string on dest string.  If dest string is not
 * large enough to hold result (determined by comparing needed size
                                                                * with destsize), a new buffer is allocated.  The buffer is resized
                                                                * by STRING_BUF_CHARS bytes.
                                                                */
void
strcat_with_realloc(char **dest, uint *destsize, char *src)
{
    char *newbuf;
    
    while (strlen(src) >= *destsize - strlen(*dest)) {
                newbuf = realloc(*dest, *destsize + STRING_BUF_CHARS);
                if (newbuf) {
                        *destsize += STRING_BUF_CHARS;
                        *dest = newbuf;
                } else
                        return;
    }
    strcat(*dest, src);
}

/* safe_sprintf
 *
 * Works like sprintf, only it takes a pointer to a buffer, dest, and
 * a pointer to the size of the buffer.  Routine will pass back results
 * in the buffer.  Buffer may be reallocated if additional space is
 * needed.  Routine returns number of characters processed.
 */
int
safe_sprintf (char **dest, uint *destsize, const char *fmt, ...)
{
    char *workbuf = string_getnext();
    va_list argp;
    int count;
    boolean allocated = FALSE;
    
    /* Calculate how many bytes we need */
    va_start(argp, fmt);
    count = _doprnt(NULL, NULLTTY, fmt, argp, FALSE);
    va_end(argp);

    /* If standard buffer not big enough then allocate one */
    if (count >= STRING_BUF_CHARS - 1) {
                workbuf = PARSERmalloc(count + 1);
                if (workbuf == NULL)
                        return 0;
                allocated = TRUE;
    }
    
    va_start(argp, fmt);
    count = _doprnt(workbuf, NULL, fmt, argp, FALSE);
    va_end(argp);
    workbuf[count] = '\0';
    
    strcat_with_realloc(dest, destsize, workbuf);

    if (allocated)
                PARSERfree(workbuf);
    return count;
}

/*
 * queuepick - Pick an element in a queue, by index
 *
 * This routine is used to return the pointer to an arbitrary element in
 * a linked list, passing the address of the queue head and an index
 * number.
 * 
 * This allows walking through a queue "by index" which can be used to
 * avoid poison-free crashes. The index is zero-based (zero gives you
                                                                                                           * the "first" element in the queue).
                                                                                                           */


void *queuepick (void *queue, int index)
{
    void *ptr;
    
    for (ptr = *(void **)queue; ptr; ptr = *(void **)ptr)
                if (index-- == 0)
                        break;
    return(ptr);
}

/*
 * xnethash
 * Hash addresses
 */

uint xnethash (register uchar *addr, register ushort len)
{
    register uint i, sum;

    sum = 0;
    for (i = 0; i < len; i++)
                sum += addr[i];
    return sum;
}

/*
 * lw_insert -- insert an element into a doubly-linked list.
 *
 * 
 * Insert new entry "entry" in list after element "pred"
 * NOTE: an empty list is formed by having the initial element
 * have both the flink and blink point to itself. Think of this
 * as a queue (ie, a circular list) rather than a simple
 * double-linked list where the terminal elements point to NULL.
 */
void lw_insert (dqueue_t *entry, dqueue_t *pred)
{
    pred->flink->blink = entry;
    entry->flink = pred->flink;
    entry->blink = pred;
    pred->flink = entry;
}

/*
 * lw_remove -- remove an element from a doubly-linked list.
 *
 * removes entry "entry"
 * Note that the removed element has its flink & blink set to point
 * to itself.
 */
void lw_remove (dqueue_t *entry)
{
    entry->blink->flink = entry->flink;
    entry->flink->blink = entry->blink;
    entry->flink = entry->blink = entry;
}

void o_init (dqueue_t *entry, void *parent)
{
    entry->flink  = entry;
    entry->blink  = entry;
    entry->parent = parent;
    TIMER_STOP(entry->value);
}

void o_enqueue (dqueue_t *header, dqueue_t *entry)
{
    dqueue_t *p;

    for (p = header->flink; p != header; p = p->flink) {
                if (TIMER_LATER(p->value, entry->value))
                        break;
    }

    entry->flink = p->blink->flink;
    p->blink->flink = entry;
    entry->blink = p->blink;
    p->blink = entry;
}

dqueue_t *o_dequeue (dqueue_t *header)
{
    dqueue_t *p;

    if (header->flink == header)
                return(NULL);
    if (SLEEPING(header->flink->value))
                return(NULL);
    p = header->flink;
    p->flink->blink = p->blink;
    p->blink->flink = p->flink;
    p->flink = p->blink = p;
    TIMER_STOP(p->value);
    return(p);
}

void o_unqueue (dqueue_t *entry)
{
    entry->flink->blink = entry->blink;
    entry->blink->flink = entry->flink;
    entry->flink = entry->blink = entry;
    TIMER_STOP(entry->value);
}

/*
 * nethash
 * Given a 32 bit quantity, return an 8 bit hash table offset.
 * We use XOR'ing as our hash function to avoid division overhead.
 */

int nethash (ulong addr)
{
    register ushort bucket;
    register charlong address;

    address.d.lword = addr;

    bucket = address.d.sword[0];
    bucket ^= address.d.sword[1];
    bucket ^= (bucket >> 8);
    bucket &= 0xFF;
    return(bucket);
}

/*
 * strdup()
 *      malloc() a new string, and copy old string to new memory
 */
char *strdup (const char *oldstr)
{
    char *newstr;
    SAVE_CALLER();

    if (oldstr == NULL)
                return(NULL);

    newstr = PARSERmalloc(strlen(oldstr) + 1);
    if (newstr == NULL) {
                return(NULL);
    }
    strcpy(newstr, oldstr);
    memory_specify_allocator(newstr, caller());
    return(newstr);
}

/*
 * malloc_named() a new string, and copy old string to new memory
 */
char *strdup_named (const char *oldstr, const char *name)
{
    char *newstr;
    SAVE_CALLER();

    if (oldstr == NULL)
                return(NULL);

    newstr = malloc_named(strlen(oldstr) + 1, name);
    if (newstr == NULL) {
                return(NULL);
    }
    strcpy(newstr, oldstr);
    memory_specify_allocator(newstr, caller());
    return(newstr);
}

char *
address_string (addrtype *address)
{
    char *buffer;

    buffer = string_getnext();
    reg_invoke_sprintf_address_addr(address->type, buffer, address);
    return(buffer);
}



#endif /* IOS_PARSER */

