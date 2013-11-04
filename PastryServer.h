//
// Copyright (C) 2009 Institut fuer Telematik, Universitaet Karlsruhe (TH)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

/**
 * @author Antonio Zea
  */

#ifndef PASTRYSERVER_H
#define PASTRYSERVER_H

#include <omnetpp.h>
#include <set>
#include <string>
#include<cstring>
#include <vector>
//#include "ClientInfo.h"

#include "BaseApp.h"

struct ClientInfo{
	int topicId;
	std::set<TransportAddress> followedBy;
	//std::vector<string> tweets;
};

class PastryServer : public BaseApp
{
    // module parameters
    simtime_t sendPeriod;     // we'll store the "sendPeriod" parameter here
    int numToSend;            // we'll store the "numToSend" parameter here
    int largestKey;           // we'll store the "largestKey" parameter here

    //stats collection
    simsignal_t numTCPSentSig;
    simsignal_t numTCPRecSig;

    simsignal_t bytesTCPSentReqUsersSig;
    simsignal_t bytesTCPRecReqUsersSig;
    simsignal_t bytesTCPRecFollowSig;
    simsignal_t bytesTCPSentJoinSig;
    simsignal_t bytesTCPRecJoinSig;
    simsignal_t bytesTCPSentTweetSig;
    simsignal_t bytesTCPRecTweetSig;

    // statistics
    int serverNumTCPSent;              //number of packets sent
    int serverNumTCPRec;          //number of packets received
    std::vector<int> onlineTopics;

    //connected client info
    std::vector<ClientInfo> clientInfo;


    // our timer
    cMessage *timerMsg;

    std::set<TransportAddress> connections;

    // application routines
    void initializeApp(int stage);                 // called when the module is being created
    void finishApp();                              // called when the module is about to be destroyed
    void handleTimerEvent(cMessage* msg);          // called when we received a timer message
    void deliver(OverlayKey& key, cMessage* msg);  // called when we receive a message from the overlay
    void handleReadyMessage(CompReadyMessage* msg);

    void handleDataReceived(TransportAddress address, cPacket* msg, bool urgent);
    void handleConnectionEvent(EvCode code, TransportAddress address);

    void joinServer(TransportAddress client, int id);



public:
    PastryServer() { timerMsg = NULL; };
    ~PastryServer() { cancelAndDelete(timerMsg); };
};


#endif
