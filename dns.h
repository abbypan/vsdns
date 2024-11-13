#ifndef NEWBIE_DNS_INCLUDED
#define NEWBIE_DNS_INCLUDED


enum {  /* Some of DNS types: */
    dns_type_a     = 1,
    dns_type_cname = 5,
    dns_type_mx    = 15,
    dns_type_txt   = 16,
    dns_type_srv   = 33, 
    /* If you need other one -- add it here. */
    dns_type_aaaa     = 28,
    dns_type_ns     = 2,
    dns_type_tlsa     = 52
};

/* Answers as linked list. */
struct dns_answers {
    struct dns_answers *next;
    char               *host;  /* for which answer is provided */
    int                 type;  /* type of current answer */
    unsigned int        size;  /* size of data */
    void               *data;
};


/* For CNAME & TXT data is just human-readable null-terminated 'char *',
 * for A data is 'unsigned char *' of size 4,
 * other answers are more complex,
 * so functions to access their data are provided: */

char *dns_mx_server(void *data);
int   dns_mx_preference(void *data);

char *dns_srv_server(void *data);
int   dns_srv_port(void *data);
int   dns_srv_priority(void *data);
int   dns_srv_weight(void *data);


/* In case of error result is 0, as if server don't know host. */
struct dns_answers *dns_get(const char *server, const char *host, int query);

void dns_free(struct dns_answers *answers);

char * dns_query_packet(const char *h, int qt, int is_tcp, int enable_dnssec, int *plen);

char *dns_get_tcp_query(char *s, int port, char *query_packet, int query_plen, int *plen);


#endif
