//
// Copyright (C) 2006 Institut fuer Telematik, Universitaet Karlsruhe (TH)
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
 * @file P2PTwitter.h
 * @author Stephan Krause
 * @author Dimitar Toshev
 */


#ifndef __P2PTWITTER_H_
#define __P2PTWITTER_H_

#include <omnetpp.h>
#include "BaseApp.h"
#include "CommonMessages_m.h"
#include "MessageObserver.h"
#include<list>
#include <string>
using namespace std;

class P2PTwitter : public BaseApp {


    //protected:
        // Handlers for message types
        void startUp();
        void makeTCPConnection();
        void contactServer(int i, int messageType);
        void handleLowerMessage(cMessage* msg);
        void handleReadyMessage(CompReadyMessage* msg);
        void handleTransportAddressChangedNotification();
        void handleUDPMessage(cMessage* msg);
        void handleUpperMessage(cMessage* msg);
        void handleTimerEvent(cMessage* msg);
        void handleDataReceived(TransportAddress address, cPacket* msg, bool urgent);
        void handleConnectionEvent(EvCode code, TransportAddress address);

        void joinGroup(int i);
        void leaveGroup(int i);
        void sendDataToGroup(int i, const ALMMulticastMessage& message);
        void handleMCast( ALMMulticastMessage* mcast );
        cMessage* timer;

    private:
        // Controls if we'll try joining groups other than 1.
        // True by default.
        // Set to false for multicast protocols that do not support
        // more than one multicast group.
        bool joinGroups;
		bool firstTime;
		bool reply;
		int replyCount;
		int tweetCount;
		std::vector<int> onlineTopics;
		std::vector<int> subscribedTo;
		NodeVector *neighbor;
		NodeHandle twitterServer;

		//ge-add vir tcp
		int numToSend;            // we'll store the "numToSend" parameter here
		int largestKey;           // we'll store the "largestKey" parameter here
		bool overlayReady;
		TransportAddress bootAddress; //server adres
		// statistics
		int numSent;              //number of packets sent
		int numReceived;          //number of packets received

		bool sendMessages;

        MessageObserver* observer;
        int msglen;

        //stats collection
        simsignal_t bytesTCPSentReqUsersSig;
		simsignal_t bytesTCPRecReqUsersSig;
		simsignal_t bytesTCPSentFollowSig;
		simsignal_t bytesTCPSentJoinSig;
		simsignal_t bytesTCPRecJoinSig;
		simsignal_t bytesTCPSentTweetSig;
		simsignal_t bytesTCPRecTweetSig;


		simsignal_t numTCPSentSig;
		simsignal_t numTCPRecSig;

		// statistics
		int clientNumTCPSent;              //number of packets sent
		int clientNumTCPRec;          //number of packets received

		bool bootAd;

    public:
            P2PTwitter();
            ~P2PTwitter();

            void initializeApp(int stage);
            void finishApp();
};

#endif
