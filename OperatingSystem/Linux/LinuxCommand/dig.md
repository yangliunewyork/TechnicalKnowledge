
```
$ dig redhat.com

; <<>> DiG 9.7.3-RedHat-9.7.3-2.el6 <<>> redhat.com
;; global options: +cmd
;; Got answer:
;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 62863
;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 4, ADDITIONAL: 3

;; QUESTION SECTION:
;redhat.com.                    IN      A

;; ANSWER SECTION:
redhat.com.             37      IN      A       209.132.183.81

;; AUTHORITY SECTION:
redhat.com.             73      IN      NS      ns4.redhat.com.


;; ADDITIONAL SECTION:
ns1.redhat.com.         73      IN      A       209.132.186.218

;; Query time: 13 msec
;; SERVER: 209.144.50.138#53(209.144.50.138)
;; WHEN: Thu Jan 12 10:09:49 2012
;; MSG SIZE  rcvd: 164
```
* Header: This displays the dig command version number, the global options used by the dig command, and few additional header information.
* QUESTION SECTION: This displays the question it asked the DNS. i.e This is your input. Since we said ‘dig redhat.com’, and the default type dig command uses is A record, it indicates in this section that we asked for the A record of the redhat.com website
* ANSWER SECTION: This displays the answer it receives from the DNS. i.e This is your output. This displays the A record of redhat.com
* AUTHORITY SECTION: This displays the DNS name server that has the authority to respond to this query. Basically this displays available name servers of redhat.com
* ADDITIONAL SECTION: This displays the ip address of the name servers listed in the AUTHORITY SECTION.
* Stats section at the bottom displays few dig command statistics including how much time it took to execute this query

