#include <dns.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
    char         *server = "8.8.8.8"; /* place your favourite one */
    int port = 53;

    char *host = "www.opendnssec.org";
    int qtype = dns_type_a;
    
    int qlen = 0;
    char *query = dns_query_packet(host, qtype, 1, 1, &qlen);

    FILE *qf = fopen("dns_example.query.bin","wb");
    fwrite(query, sizeof(char), qlen, qf); 
    fclose(qf);


    int rlen = 0;
    char *res = dns_get_tcp_query(server, port, query, qlen, &rlen);

    FILE *rf = fopen("dns_example.res.bin","wb");
    fwrite(res, sizeof(char), rlen, rf); 
    fclose(rf);
    
    free(query);
    free(res);

    return 0;
}
