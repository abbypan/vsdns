# DNS made simple.

fork from: https://github.com/aversey/vsdns

# function

query packet (support dnssec flag):

    char * dns_query_packet(const char *h, int qt, int is_tcp, int enable_dnssec, int *plen);

send tcp query:

    char *dns_get_tcp_query(char *s, int port, char *query_packet, int query_plen, int *plen);


# test

send dnssec tcp query www.opendnssec.org to 8.8.8.8
    
    $ sudo pacman -S ldns

    $ make

    $ ./dns_example

    $ drill -i dns_example.query.bin 
    ;; ->>HEADER<<- opcode: QUERY, rcode: NOERROR, id: 49983
    ;; flags: rd ad ; QUERY: 1, ANSWER: 0, AUTHORITY: 0, ADDITIONAL: 0 
    ;; QUESTION SECTION:
    ;; www.opendnssec.org.	IN	A

    ;; ANSWER SECTION:

    ;; AUTHORITY SECTION:

    ;; ADDITIONAL SECTION:

    ;; Query time: 0 msec
    ;; EDNS: version 0; flags: do ; udp: 1232
    ;; WHEN: Thu Jan  1 08:00:00 1970
    ;; MSG SIZE  rcvd: 48

    $ drill -i dns_example.res.bin
    ;; ->>HEADER<<- opcode: QUERY, rcode: NOERROR, id: 49983
    ;; flags: qr rd ra ad ; QUERY: 1, ANSWER: 2, AUTHORITY: 0, ADDITIONAL: 0 
    ;; QUESTION SECTION:
    ;; www.opendnssec.org.	IN	A

    ;; ANSWER SECTION:
    www.opendnssec.org.	14400	IN	A	185.49.141.14
    www.opendnssec.org.	14400	IN	RRSIG	A 8 3 14400 20241129223641 20241109045047 58078 opendnssec.org. TtriN+THjZi3qzFyjE8LTqUbCQM1TMGeS8aVbYhr8EbkJKVHZbzJ1ndxGVunVxx6UpJEpZO2+isgMHN+C5N9t/LOWMB6jPisxf2WtzGnurIJSRmH1FPrrFf3iVCCPOCkOg5LG7zOH8zo/O0qbJC68I/vIVpKtDKQZCo8E6sURLQ=

    ;; AUTHORITY SECTION:

    ;; ADDITIONAL SECTION:

    ;; Query time: 0 msec
    ;; EDNS: version 0; flags: do ; udp: 512
    ;; WHEN: Thu Jan  1 08:00:00 1970
    ;; MSG SIZE  rcvd: 238
