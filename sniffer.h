#ifndef SNIFFER_H_INCLUDED
#define SNIFFER_H_INCLUDED

#if _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif // _WIN32

#include <iostream>
#include "Ethernet.h"
#include "ipv4.h"
#include "ICMPv4.h"
#include "arpRarp.h"
#include "ipv6.h"
#include "icmpv6.h"
#include <winsock2.h>

using namespace std;

class Sniffer {
public:
    void showData();
};

#endif // SNIFFER_H_INCLUDED
