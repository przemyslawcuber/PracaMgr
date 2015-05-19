#include "readpcapfile.h"
#include "packet.h"

#include <iostream>
#include <iomanip>      // std::setprecision
#include <sstream>

#include "preparedata.h"

using namespace std;

extern "C"
{
// ------------------------------------- FOR WINDOWS -----------------------------------------------
#ifdef _WIN32
#define ETHERTYPE_IP 0x0800
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

/* Ethernet addresses are always 6 bytes */
#define ETHER_ADDR_LEN	6

/* Ethernet header */
struct sniff_ethernet {
    u_char ether_dhost[ETHER_ADDR_LEN]; /* Destination host address */
    u_char ether_shost[ETHER_ADDR_LEN]; /* Source host address */
    u_short ether_type; /* IP? ARP? RARP? etc */
};

/* IP header */
struct sniff_ip {
    u_char ip_vhl;		/* version << 4 | header length >> 2 */
    u_char ip_tos;		/* type of service */
    u_short ip_len;		/* total length */
    u_short ip_id;		/* identification */
    u_short ip_off;		/* fragment offset field */
#define IP_RF 0x8000		/* reserved fragment flag */
#define IP_DF 0x4000		/* dont fragment flag */
#define IP_MF 0x2000		/* more fragments flag */
#define IP_OFFMASK 0x1fff	/* mask for fragmenting bits */
    u_char ip_ttl;		/* time to live */
    u_char ip_p;		/* protocol */
    u_short ip_sum;		/* checksum */
    struct in_addr ip_src,ip_dst; /* source and dest address */
};
#define IP_HL(ip)		(((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)		(((ip)->ip_vhl) >> 4)

/* TCP header */
struct sniff_tcp {
    u_short th_sport;	/* source port */
    u_short th_dport;	/* destination port */
    unsigned int th_seq;		/* sequence number */
    unsigned int th_ack;		/* acknowledgement number */

    u_char th_offx2;	/* data offset, rsvd */
#define TH_OFF(th)	(((th)->th_offx2 & 0xf0) >> 4)
    u_char th_flags;
#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
#define TH_ECE 0x40
#define TH_CWR 0x80
#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
    u_short th_win;		/* window */
    u_short th_sum;		/* checksum */
    u_short th_urp;		/* urgent pointer */

#endif

// ------------------------------------- FOR LINUX -------------------------------------------------

#ifdef __linux
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#endif

#include <pcap.h>
}

// GLOBAL VARIABLES

QList<Packet *> dataSet;


extern "C"{
void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
    const struct ether_header* ethernetHeader;
    const struct ip* ipHeader;
    const struct tcphdr* tcpHeader;
    char sourceIp[INET_ADDRSTRLEN];
    char destIp[INET_ADDRSTRLEN];
    u_int sourcePort, destPort;
    u_char *data;
    int dataLength = 0;
    string dataStr = "";
    ethernetHeader = (struct ether_header*)packet;
    if (ntohs(ethernetHeader->ether_type) == ETHERTYPE_IP) {
        ipHeader = (struct ip*)(packet + sizeof(struct ether_header));
        qint16 uniqueIndicator = ipHeader->ip_id;
        inet_ntop(AF_INET, &(ipHeader->ip_src), sourceIp, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ipHeader->ip_dst), destIp, INET_ADDRSTRLEN);
        if (ipHeader->ip_p == IPPROTO_TCP) {
            tcpHeader = (tcphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
            sourcePort = ntohs(tcpHeader->source);
            destPort = ntohs(tcpHeader->dest);
            data = (u_char*)(packet + sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr));
            dataLength = pkthdr->len - (sizeof(struct ether_header) + sizeof(struct ip) + sizeof(struct tcphdr));
            // convert non-printable characters, other than carriage return, line feed,
            // or tab into periods when displayed.
            for (int i = 0; i < dataLength; i++) {
                if ((data[i] >= 32 && data[i] <= 126) || data[i] == 10 || data[i] == 11 || data[i] == 13) {
                    dataStr += (char)data[i];
                } else {
                    dataStr += ".";
                }
            }
            std::ostringstream oss; // output to string
            oss << std::setprecision(7) << pkthdr->ts.tv_sec << ":" << pkthdr->ts.tv_usec;
            string time_s = oss.str();
            time_t time = atoi(time_s.c_str());
            struct tm * timeinfo = localtime(&time);
            char buffer[80];
            strftime (buffer, 80, "%X", timeinfo);
            //const char time_as_str[] = "1296575549:573352";
            //time_t t = atoi(time_as_str); // convert to time_t, ignores msec
            //cout << asctime(localtime(&t));
            //printf("Time: %.6f\n",seconds);
            // print the results
            // cout << "Time: " << buffer << "." << pkthdr->ts.tv_usec << " " << sourceIp << ":" << sourcePort << " -> " << destIp << ":" << destPort << " length: " << dataLength << endl;
            // buffer to data/godzina
            // hour
            // strftime (buffer, 80, "%H", timeinfo);
            // qint8 hour = atoi(buffer);
            // minutes
            // strftime (buffer, 80, "%M", timeinfo);
            // qint8 minutes = atoi(buffer);
            // seconds
            // strftime (buffer, 80, "%S", timeinfo);
            // qint8 seconds = atoi(buffer);
            // microseconds
            //quint16 ms = pkthdr->ts.tv_usec;
            // qint32 ms = pkthdr->ts.tv_usec;
            // sourceIp
            QString adresZrodlowy = QString::fromUtf8(sourceIp);
            // sourcePort
            quint16 sourcePortttt = sourcePort;
            // destIp
            QString destIPP = QString::fromUtf8(destIp);
            // destPort
            quint16 destPorttt = destPort;
            // SETTING TABLE VIEW
            // QStandardItem* item0 = new QStandardItem(true);
            // item0->setCheckable(true);
            // item0->setCheckState(Qt::Unchecked);
            // item0->setToolTip("Wybór początkowych środków klastrów dla algorytmu k-means");
            // item0->setSelectable(false);
            // item0->setEditable(false);
            // _model_for_c->setItem(counter, 0, item0);
            // QStandardItem* timeColumn = new QStandardItem(QString::fromUtf8(buffer) + "." + QString::number(pkthdr->ts.tv_usec));
            // timeColumn->setEditable(false);
            // _model_for_c->setItem(counter, 1, timeColumn);
            // QStandardItem* sourceIpAsAddressColumn = new QStandardItem(adresZrodlowy);
            // sourceIpAsAddressColumn->setEditable(false);
            // _model_for_c->setItem(counter, 2, sourceIpAsAddressColumn);
            // QStandardItem* sourcePortColumn = new QStandardItem(QString(QString::number(sourcePortttt)));
            // sourcePortColumn->setEditable(false);
            // _model_for_c->setItem(counter, 3, sourcePortColumn);
            // QStandardItem* destIpAsAddressColumn = new QStandardItem(destIPP);
            // destIpAsAddressColumn->setEditable(false);
            // _model_for_c->setItem(counter, 4, destIpAsAddressColumn);
            // QStandardItem* destPortColumn = new QStandardItem(QString(QString::number(destPorttt)));
            // destPortColumn->setEditable(false);
            // _model_for_c->setItem(counter, 5, destPortColumn);
            // counter++;
            // end setting table view

// -------------------------------------------- CREATE PACKET ----------------------------------
            Packet * newPacket = new Packet();
            newPacket->setSourceIp(QString::fromUtf8(sourceIp));
            newPacket->setDestIp(QString::fromUtf8(destIp));
            newPacket->setId(uniqueIndicator);
            dataSet.append(newPacket);
        }
        //if (dataLength > 0) {
        // cout << dataStr << endl;
        //}
    }
}
} // extern "C"

void ReadPcapFile::readFile(const QString &fileName) {

    char errbuf[PCAP_ERRBUF_SIZE];
    // open capture file for offline processing
    pcap_t * descr = pcap_open_offline(fileName.toUtf8().constData(), errbuf);
    if (descr == NULL) {
        cout << "pcap_open_live() failed: " << errbuf << endl;
        //        emit warnings(tr("Błąd"), tr("Zły format pliku!"));
        return;
    }
    // start packet processing loop, just like live capture
    if (pcap_loop(descr, 0, packetHandler, NULL) < 0) {
        cout << "pcap_loop() failed: " << pcap_geterr(descr);
        return;
    }

    PrepareData * prepareData = new PrepareData();
    prepareData->_prepareData(dataSet);
    prepareData->writeData();

    /* ... here is the expensive or blocking operation ... */
    QString result = "";
    emit resultReady(result);
}

ReadPcapFile::ReadPcapFile()
{

}

ReadPcapFile::~ReadPcapFile()
{

}
