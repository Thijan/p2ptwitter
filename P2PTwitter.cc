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
 * @file P2PTwitter.cc
 * @author Stephan Krause
 * @author Dimitar Toshev
 */

#include <assert.h>
#include "P2PTwitter.h"
#include "P2PTwitterTracedMessage_m.h"
#include <string>
#include <vector>
#include<NeighborCache.h>
#include "GlobalNodeListAccess.h"
#include <BootstrapList.h>
using namespace std;

//ge-add vir tcp
#include "UnderlayConfigurator.h"
#include "GlobalStatistics.h"
#include "IPvXAddress.h"
#include "TransportAddress.h"
#include "ServerMessage_m.h"


Define_Module(P2PTwitter);

P2PTwitter::P2PTwitter()
{
    timer = new cMessage( "app_timer"); 
    joinGroups = true;
    sendMessages = true;
    observer = NULL;
	firstTime = true;
	reply = false;
	replyCount = 2;
	tweetCount = 0;
}

P2PTwitter::~P2PTwitter()
{
    cancelAndDelete( timer ); 
}

void P2PTwitter::initializeApp(int stage)
{
    if( stage != (numInitStages()-1))
    {
        return;
    }
    observer = check_and_cast<MessageObserver*>(
            simulation.getModuleByPath("globalObserver.globalFunctions[0].function.observer"));
    joinGroups = par("joinGroups");
    msglen = par("messageLength");
    sendMessages = par("sendMessages");

    //ge-add vir tcp
    numToSend = par("numToSend");
    largestKey = par("largestKey");
    numSent = 0;
    numReceived = 0;

    //register signals
    bytesTCPSentReqUsersSig = registerSignal("bytesSentReqUsers");
	bytesTCPRecReqUsersSig = registerSignal("bytesRecReqUsers");
	bytesTCPSentFollowSig = registerSignal("bytesSentFollow");
	bytesTCPSentJoinSig = registerSignal("bytesSentJoin");
	bytesTCPRecJoinSig = registerSignal("bytesRecJoin");
	bytesTCPSentTweetSig = registerSignal("bytesSentTweet");
	bytesTCPRecTweetSig = registerSignal("bytesRecTweet");

    // set up and listen on tcp
    bindAndListenTcp(24000);
    overlayReady = false;

    bootAd = false;
}

void P2PTwitter::finishApp()
{
    cancelEvent(timer);
    observer->nodeDead(getId());

    //ge-add vir tcp
    closeTcpConnection(bootAddress);
    globalStatistics->addStdDev("PastryClient: Sent packets", numSent);
    globalStatistics->addStdDev("PastryClient: Received packets", numReceived);
}

void P2PTwitter::handleTimerEvent( cMessage* msg )
{
    if( msg == timer ) {

    	if (!overlayReady){
    		return;
    	}

    	if (!bootAd) {
    		makeTCPConnection();
    		bootAd = true;
    	}

		if(firstTime){
			startUp();
		}else{
			double random = uniform( 0, 1);
			if( (random < 0.5 && joinGroups)) {
				contactServer(this->getId(), USERS_REQUEST);
			} /*else if( random < 0.4 && joinGroups && subscribedTo.size() > 1) {
				int randGroup = rand() % subscribedTo.size();
				if(randGroup != 0){
					subscribedTo.erase(subscribedTo.begin() + randGroup);
					leaveGroup( subscribedTo[randGroup]);
					contactServer(subscribedTo[randGroup], UNSUBSCRIBE);
				}
			}*/ else if ( sendMessages ) {
				tweetCount++;

				sendDataToGroup(this->getId(), "Normal Tweet");

				EV << "\nTTTTTTTTTTTTT\nTTTTTTTTTTTT\nI am tweeting\n\n";
				contactServer(this->getId(), TWEET);
			}
		}
		scheduleAt( simTime() + 10, timer );
    }
}

void P2PTwitter::makeTCPConnection(){
	EV << "\n*******************\n*******************\nStarted up the first time\n*******************\n*******************\n";

	ServerMessage *myMessage; // the message we'll send
	myMessage = new ServerMessage();
	myMessage->setType(SERVER_JOIN); // set the message type to PING
	thisNode.setPort(24000);
	myMessage->setSenderAddress(thisNode); // set the sender address to our own
	myMessage->setTopicId(this->getId());
	myMessage->setByteLength(50); // set the message length to 100 bytes
	numSent++; // update statistics

	EV << "PastryClient::handleTimerEvent => "<< thisNode.getIp() << ": Sending packet to "
			<< bootAddress.getIp() << ":" << bootAddress.getPort() << "!" << std::endl;

	sendTcpData(myMessage, bootAddress);

	clientNumTCPSent++;
	emit(numTCPSentSig, clientNumTCPSent);

	int clientBytesSent = myMessage->getByteLength();
	emit(bytesTCPSentJoinSig, clientBytesSent);

}

void P2PTwitter::contactServer(int id, int messageType){
	ServerMessage *myMessage;
	myMessage = new ServerMessage();
	myMessage->setType(messageType);
	myMessage->setTopicId(id);
	thisNode.setPort(24000);
	myMessage->setSenderAddress(thisNode);

	if(messageType == USERS_REQUEST){
		myMessage->setByteLength(20);
		emit(bytesTCPSentReqUsersSig, 20);
	}else if ( messageType == SUBSCRIBE){
		myMessage->setByteLength(20);
		emit(bytesTCPSentFollowSig, 20);
	}else{
		myMessage->setByteLength(160);
		emit(bytesTCPSentTweetSig, 160);
	}

	sendTcpData(myMessage, bootAddress);

	clientNumTCPSent++;
	emit(numTCPSentSig, clientNumTCPSent);

}

void P2PTwitter::startUp(){
	firstTime = false;
	onlineTopics.push_back(this->getId());
}

void P2PTwitter::handleLowerMessage(cMessage* msg)
{
    ALMMulticastMessage* mcast = dynamic_cast<ALMMulticastMessage*>(msg);
    if ( mcast != 0 ) {
        handleMCast(mcast);
    }
}

void P2PTwitter::handleReadyMessage(CompReadyMessage* msg)
{
	// process only ready messages from the tier below
	if( (getThisCompType() - msg->getComp() == 1) && msg->getReady() ){
	        if(msg->getReady()) {
	            overlayReady = true;

	            NodeHandle nodehandle = overlay->getThisNode();
	            bootAddress.setAddress(IPvXAddress("1.0.0.1"),24000);

	            EV << "PastryClient::handleReadyMessage => " << thisNode.getIp() << ": Overlay is ready. Establishing TCP Connectino to  "
	                                       << bootAddress
	                                       <<  std::endl;
	            establishTcpConnection(bootAddress);

	            cancelEvent(timer);
	            scheduleAt(simTime() + 1, timer);
	        }
	        else {
	            overlayReady = false;
	        }
	    }
	    delete msg;
}

void P2PTwitter::handleTransportAddressChangedNotification()
{
    //TODO: Implement
    assert(false);
}

void P2PTwitter::handleUDPMessage(cMessage* msg)
{
	//TODO: Implement
	    assert(false);
}

void P2PTwitter::handleUpperMessage(cMessage* msg)
{
    //TODO: Implement
    assert(false);
}

void P2PTwitter::joinGroup(int i)
{
    ALMSubscribeMessage* msg = new ALMSubscribeMessage;
    msg->setGroupId(OverlayKey(i));
    send(msg, "to_lowerTier");
	EV << "P2PTwitter::joinGroup => This nodes Id: " << this->getId();

	subscribedTo.push_back(i);

    observer->joinedGroup(getId(), OverlayKey(i));
	getParentModule()->getParentModule()->bubble("++++++++++Joined Group+++++++++++");
	
	EV << "\n+++++++++++++++++++++++++++++++++++++++++++\nI Joined a group: " << i
			<< "\nMy ID is: " << this->getId()
			<< "\n+++++++++++++++++++++++++++++++++++++++\n";
}

void P2PTwitter::leaveGroup(int i)
{
    ALMLeaveMessage* msg = new ALMLeaveMessage;
    msg->setGroupId(OverlayKey(i));
    send(msg, "to_lowerTier");

    observer->leftGroup(getId(), OverlayKey(i));
	getParentModule()->getParentModule()->bubble("-----------------Left Group-----------------------");
	EV << "########### Left group '" << msg->getGroupId() << "' ########";

	EV << "\n----------------------------------------\nI left a group: " << i
				<< "\nMy ID is: " << this->getId()
				<< "\n---------------------------------------\n";
}

void P2PTwitter::sendDataToGroup( int i, const ALMMulticastMessage& message)
{
    ALMMulticastMessage* msg = new ALMMulticastMessage(message);
    msg->setGroupId(OverlayKey(i));

    P2PTwitterTracedMessage* traced = new P2PTwitterTracedMessage("This is my traced message");
    traced->setTimestamp();
    traced->setGroupId(OverlayKey(i));
    traced->setMcastId(traced->getId());
    traced->setSenderId(getId());
    traced->setByteLength(msglen);
	traced->setUName("Thijan Dippenaar");
	traced->setScreen_name("@thijan");
	traced->setUId(this->getId());
	traced->setUTweet_count(tweetCount);

    msg->encapsulate(traced);
    send(msg, "to_lowerTier");
    observer->sentMessage(traced);
	getParentModule()->getParentModule()->bubble("#######################MESSAGE SENT################");
	
}

void P2PTwitter::handleMCast( ALMMulticastMessage* mcast )
{
    getParentModule()->getParentModule()->bubble("Received message!");
	
	P2PTwitterTracedMessage* traced = check_and_cast<P2PTwitterTracedMessage*>(mcast->decapsulate());
    traced->setReceiverId(getId());
	
	//Receiving messages on base group to see what users are online
	if(mcast->getGroupId() == 0){
		EV << "\n\nNew Member joined the group\n\n"
			<< "I am topic: " << this->getId()
			<< "App received data message for group: " << mcast->getGroupId()
			<< "\n\n New member entered: " << traced->getUId()
			<< endl;
			
		if(traced->getUId() != this->getId()){
			onlineTopics.push_back(traced->getUId());
		}
			
			for ( int i = 0; i < onlineTopics.size(); i++) {
				EV << onlineTopics[i] << " \n";
			}
	}
	
	//Normal messages from groups subscribed to.
	else{
		EV << "\n[P2PTwitter::handleMCast()]\n"
			<< "    App received data message for group: " << mcast->getGroupId()
			<< "\n Message received: " << mcast->getName()
			<< endl;

		EV << "Username that tweeted message:" << traced->getUName()
			<< "\nScreen name:" << traced->getScreen_name()
			<<  "\nUser ID:" << traced->getUId()
			<< "\n Tweet ID:" << traced->getUTweet_count()
			<< "\nThis nodes ID: " << this->getId() << "\n"
			<< endl;
	}
	
    observer->receivedMessage(traced);

    delete traced;

    delete mcast;
}

void P2PTwitter::handleDataReceived(TransportAddress address, cPacket* msg, bool urgent) {

	clientNumTCPRec++;
	int clientBytesRec = msg->getByteLength();
	emit(numTCPRecSig, clientNumTCPRec);
	//emit(bytesTCPRecSig, clientBytesRec);

	EV << "PastryClient::handleDataReceivedMessage => Received a msg " << msg->detailedInfo() << std::endl;

    // we are only expecting messages of type PastryServerMessage, throw away any other
    ServerMessage *myMsg = dynamic_cast<ServerMessage*>(msg);

    // did we receive an ACK from the server?
    if (myMsg && (myMsg->getType() == SERVER_ACKJOIN)) {

    	emit(bytesTCPRecJoinSig, clientBytesRec);

        EV << "P2PTwitter::handleDataReceived => " << this->overlay->getThisNode().getIp() << ": Received an ACKJOIN packet from "
                << myMsg->getSenderAddress()
                <<  std::endl;
    }else if(myMsg && (myMsg->getType() == TWEET)){
    	EV << "\n1.1.1.1.1.1.1.1.1.\n1.1.1.1.1.1.1.1.1.1.1\n"
    			<< "tweet received from:" << myMsg->getTopicId();

    	emit(bytesTCPRecTweetSig, clientBytesRec);
    }else if(myMsg && (myMsg->getType() == USERS_REQUEST)){

    	emit(bytesTCPRecReqUsersSig, clientBytesRec);

    	int randGroup = rand() % onlineTopics.size();

    	std::vector<int> tempVec(myMsg->getTopics());
		for ( int i = 0; i <tempVec.size(); i++) {
			for(int j = 0; j<onlineTopics.size(); j++){
				if(tempVec[i] == onlineTopics[j]){
					break;
				}else if(j == onlineTopics.size() -1){
					onlineTopics.push_back(tempVec[i]);
				}
			}
		}
		//if its my own group, do nothing
		if(onlineTopics[randGroup] == this->getId()){
			return;
		}

		//check if im subscribed already to this random group, if so don't send subscribe again
		for(int i = 0; i < subscribedTo.size(); i++){
			if(subscribedTo[i] == onlineTopics[randGroup]){
				return;
			}
		}
		contactServer(onlineTopics[randGroup], SUBSCRIBE);
		joinGroup(onlineTopics[randGroup]);


		EV << "\n\n###############\nThe following topics is online\n#################\n";

		for ( int i = 0; i < onlineTopics.size(); i++) {
			EV << onlineTopics[i] << " \n";
		}
    }
    // Message isn't needed any more -> delete it
    delete msg;
}

void P2PTwitter::handleConnectionEvent(EvCode code, TransportAddress address) {
    BaseTcpSupport::handleConnectionEvent(code, address);
}

