#if _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32

#define WINPCAP
#define HAVE_REMOTE

#include <iostream>
#include "Ethernet.h"
#include "ipv4.h"
#include "ICMPv4.h"
#include "arpRarp.h"
#include "sniffer.h"

#include <winsock2.h>
#include "pcap.h"

#ifdef _MSC_VER
/*
 * we do not want the warnings about the old deprecated and unsecure CRT functions
 * since these examples can be compiled under *nix as well
 */
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>

#include <pcap.h>

#define LINE_LEN 16

using namespace std;

int main(int argc, char **argv) {
	pcap_if_t *alldevs, *d;
	pcap_t *fp;
	u_int inum, i=0;
	char errbuf[PCAP_ERRBUF_SIZE];
	int res;
	struct pcap_pkthdr *header;
	const u_char *pkt_data;

	printf("pktdump_ex: prints the packets of the network using WinPcap.\n");
	printf("   Usage: pktdump_ex [-s source]\n\n"
	       "   Examples:\n"
	       "      pktdump_ex -s file.acp\n"
	       "      pktdump_ex -s \\Device\\NPF_{C8736017-F3C3-4373-94AC-9A34B7DAD998}\n\n");

	if(argc < 3) {
		printf("\nNo adapter selected: printing the device list:\n");
		/* The user didn't provide a packet source: Retrieve the local device list */
		if(pcap_findalldevs(&alldevs, errbuf) == -1) {
			fprintf(stderr,"Error in pcap_findalldevs_ex: %s\n", errbuf);
			exit(1);
		}

		/* Print the list */
		for(d=alldevs; d; d=d->next) {
			printf("%d. %s\n    ", ++i, d->name);

			if (d->description)
				printf(" (%s)\n", d->description);
			else
				printf(" (No description available)\n");
		}

		if (i==0) {
			printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
			return -1;
		}

		printf("Enter the interface number (1-%d):",i);
		scanf("%d", &inum);

		if (inum < 1 || inum > i) {
			printf("\nInterface number out of range.\n");

			/* Free the device list */
			pcap_freealldevs(alldevs);
			return -1;
		}

		/* Jump to the selected adapter */
		for (d=alldevs, i=0; i< inum-1 ; d=d->next, i++);

		/* Open the adapter */
		if ((fp = pcap_open_live(d->name,	// name of the device
		                         65536,							// portion of the packet to capture.
		                         // 65536 grants that the whole packet will be captured on all the MACs.
		                         1,								// promiscuous mode (nonzero means promiscuous)
		                         1000,							// read timeout
		                         errbuf							// error buffer
		                        )) == NULL) {
			fprintf(stderr,"\nError opening adapter\n");
			return -1;
		}
	} else {
		/* Do not check for the switch type ('-s') */
		if ((fp = pcap_open_live(argv[2],	// name of the device
		                         65536,							// portion of the packet to capture.
		                         // 65536 grants that the whole packet will be captured on all the MACs.
		                         1,								// promiscuous mode (nonzero means promiscuous)
		                         1000,							// read timeout
		                         errbuf							// error buffer
		                        )) == NULL) {
			fprintf(stderr,"\nError opening adapter\n");
			return -1;
		}
	}

	/* Read the packets */
	while((res = pcap_next_ex( fp, &header, &pkt_data)) >= 0) {

		if(res == 0)
			/* Timeout elapsed */
			continue;

		/* print pkt timestamp and pkt len */
		//printf("%ld:%ld (%ld)\n", header->ts.tv_sec, header->ts.tv_usec, header->len);
		/* Print the packet */

		int aux(0);
		std::ofstream newFile("new_archivo.bin");
		for (i=1; (i < header->caplen + 1 ) ; i++) {
			aux =  pkt_data[i-1];
			newFile.write((char*)&aux, 1);
		}
		newFile.close();

		string opc;
		Sniffer mySniffer;
		mySniffer.showData();

		cout << endl << endl << "¿Desea abrir un nuevo archivo?(S/N): ";
		do {
			getline(cin, opc);
		} while(opc != "N" and opc != "n" and
		        opc != "S" and opc != "s");
		if(opc == "N" or opc == "n") {
			break;
		}
	}

	if(res == -1) {
		printf("Error reading the packets: %s\n", pcap_geterr(fp));
		return -1;
	}

	pcap_close(fp);
	return 0;
}
