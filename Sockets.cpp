// Sockets.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

const int  REQ_WINSOCK_VER   = 2;   // Minimum winsock version required
const char DEF_SERVER_NAME[] = "www.google.com";
const int  SERVER_PORT       = 80;
const int  TEMP_BUFFER_SIZE  = 128;

class HRException
{
public:
    HRException() :
         m_pMessage("") {}
    virtual ~HRException() {}
    HRException(const char *pMessage) :
         m_pMessage(pMessage) {}
    const char * what() { return m_pMessage; }
private:
    const char *m_pMessage;
};

const char HEAD_REQUEST_PART1[] =
{
    "HEAD / HTTP/1.1\r\n"           // Get root index from server
    "Host: "        // Specify host name used
};

const char HEAD_REQUEST_PART2[] =
{
    "\r\n"                          // End hostname header from part1
    "User-agent: HeadReqSample\r\n" // Specify user agent
    "Connection: close\r\n"         // Close connection after response
    "\r\n"                          // Empty line indicating end of request
};

bool RequestHeaders(const char *pServername)
{
    SOCKET      hSocket = INVALID_SOCKET;
    char        tempBuffer[TEMP_BUFFER_SIZE];
    sockaddr_in sockAddr = {0};
    bool        bSuccess = true;

    try
    {
        // code goes here
    }
    catch(HRException e)
    {
        cerr << "\nError: " << e.what() << endl;
        bSuccess = false;
    }

    return bSuccess;
}

int main(int argc, char* argv[])
{
	int iRet = 1;
	WSADATA wsaData;
	hostent *hello;
	cout << "Winsock, starting up... ";
	if(WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)
		{
        // Check if major version is at least REQ_WINSOCK_VER
        if (LOBYTE(wsaData.wVersion) >= REQ_WINSOCK_VER)
        {
            cout << "initialized.\n";

            // Set default hostname:
            const char *pHostname = DEF_SERVER_NAME;

            // Set custom hostname if given on the commandline:
            if (argc > 1)
                pHostname = argv[1];

        }
        else
        {
            cerr << "required version not supported!";
        }

        cout << "Cleaning up winsock... ";

        // Cleanup winsock
        if (WSACleanup()!=0)
        {
            cerr << "cleanup failed!\n";
            iRet = 1;
        }
        cout << "done.\n";
    }

	hello = gethostbyname("www.mcpeinventoryeditor.coffeecup.com");
	system("Pause");
	return 0;
}
