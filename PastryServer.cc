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

#include <string>

#include "UnderlayConfigurator.h"
#include "GlobalStatistics.h"
#include <BootstrapList.h>

#include "ServerMessage_m.h"

#include "PastryServer.h"

Define_Module(PastryServer);

// initializeApp() is called when the module is being created.
// Use this function instead of the constructor for initializing variables.
void PastryServer::initializeApp(int stage)
{
    // initializeApp will be called twice, each with a different stage.
    // stage can be either MIN_STAGE_APP (this module is being created),
    // or MAX_STAGE_APP (all modules were created).
    // We only care about MIN_STAGE_APP here.

    if (stage != MIN_STAGE_APP) return;

    // copy the module parameter values to our own variables
    sendPeriod = par("sendPeriod");
    numToSend = par("numToSend");
    largestKey = par("largestKey");

    // initialize our statistics variables
    serverNumTCPSent = 0;
    serverNumTCPRec = 0;

    //register signals
    numTCPSentSig = registerSignal("sent");
    numTCPRecSig = registerSignal("received");

    bytesTCPSentReqUsersSig = registerSignal("bytesSentReqUsers");
    bytesTCPRecReqUsersSig = registerSignal("bytesRecReqUsers");
    bytesTCPRecFollowSig = registerSignal("bytesRecFollow");
    bytesTCPSentJoinSig = registerSignal("bytesSentJoin");
    bytesTCPRecJoinSig = registerSignal("bytesRecJoin");
    bytesTCPSentTweetSig = registerSignal("bytesSentTweet");
    bytesTCPRecTweetSig = registerSignal("bytesRecTweet");

    // set up and listen on tcp
    bindAndListenTcp(24000);

    //bindToPort(2000);
    overlay->getBootstrapList().registerBootstrapNode(overlay->getThisNode());
}


// finish is called when the module is being destroyed
void PastryServer::finishApp()
{
    // finish() is usually used to save the module's statistics.
    // We'll use globalStatistics->addStdDev(), which will calculate min, max, mean and deviation values.
    // The first parameter is a name for the value, you can use any name you like (use a name you can find quickly!).
    // In the end, the simulator will mix together all values, from all nodes, with the same name.

    globalStatistics->addStdDev("PastryServer: Sent packets", serverNumTCPSent);
    globalStatistics->addStdDev("PastryServer: Received packets", serverNumTCPRec);
}


// handleTimerEvent is called when a timer event triggers
void PastryServer::handleTimerEvent(cMessage* msg)
{


}

// deliver() is called when we receive a message from the overlay.
// Unknown packets can be safely deleted here.
void PastryServer::deliver(OverlayKey& key, cMessage* msg)
{
    // we are not expecting any message, throw away any other
    delete msg;
}

void PastryServer::handleReadyMessage(CompReadyMessage* msg)
{
    // process only ready messages from the tier below
    if( getThisCompType() - msg->getComp() == 1 ){
        if(msg->getReady()) {
            TransportAddress bootAddress = this->overlay->getBootstrapList().getBootstrapNode();
            EV << "PastryServer::handleReadyMessage => Server with address: " << this->overlay->getThisNode().getAddress() << " has bootAddress: " << bootAddress << std::endl;
        }
    }
    delete msg;
}

void PastryServer::handleDataReceived(TransportAddress address, cPacket* msg, bool urgent) {

    // we are only expecting messages of type ServerMessage, throw away any other
    ServerMessage *myMsg = dynamic_cast<ServerMessage*>(msg);

    switch(myMsg->getType()){
		case SERVER_JOIN:
		{
			joinServer(myMsg->getSenderAddress(), myMsg->getTopicId());
			ClientInfo ci;
			ci.topicId = myMsg->getTopicId();
			clientInfo.push_back(ci);

			//stats record
			int servBytesSent = myMsg->getByteLength();
			emit(bytesTCPRecJoinSig, servBytesSent);

			EV << "\n{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{\nUser joined server "
										<< myMsg->getTopicId()
										<< "\n{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{\n";
		}
			break;
		case SERVER_LEAVE:
			//onlineTopics.erase(myMsg->getTopicId());
			closeTcpConnection(address);
			connections.erase(address);
			break;
		case SUBSCRIBE:
		{
			//stats record
			int servBytesSent = myMsg->getByteLength();
			emit(bytesTCPRecFollowSig, servBytesSent);

			for(int i = 0; i<clientInfo.size();i++){
				if(clientInfo[i].topicId == myMsg->getTopicId()){
					clientInfo[i].followedBy.insert(myMsg->getSenderAddress());

					EV << "\n++++++++++++++++++++\n++++++++++++++++++++\nUser Subscribed to "
							<< myMsg->getTopicId()
							<< "\n++++++++++++++++++++\n++++++++++++++++++++\n";

					break;
				}
			}
		}
			break;
		case UNSUBSCRIBE:
			for(int i = 0; i<clientInfo.size();i++){
				if(clientInfo[i].topicId == myMsg->getTopicId()){
					clientInfo[i].followedBy.erase(myMsg->getSenderAddress());

					EV << "\n----------------------------\n----------------------------\nUser left group "
												<< myMsg->getTopicId()
												<< "\n----------------------------\n----------------------------\n";

					break;
				}
			}
			break;
		case TWEET:
		{
			//stats record
			int servBytesSent = myMsg->getByteLength();
			emit(bytesTCPRecTweetSig, servBytesSent);

			//Uncomment the netx section to simulate the server-client version

			/*
			for(int i = 0; i<clientInfo.size();i++){
				if(clientInfo[i].topicId == myMsg->getTopicId()){
					EV << "\n*-*-*-*-*-**-*-*\n*-*-*-*-*-*-*-*-*-*-*\nTrying to forward tweets";

					std::set<TransportAddress>::const_iterator it;

					if(clientInfo[i].followedBy.size() > 1){
						for(it = clientInfo[i].followedBy.begin(); it != clientInfo[i].followedBy.end(); it++){
							ServerMessage *tweet = new ServerMessage();
							tweet->setType(TWEET); // set the message type to PING
							thisNode.setPort(24000);
							tweet->setSenderAddress(thisNode); // set the sender address to our own
							tweet->setByteLength(160); // set the message length to 100 bytes
							tweet->setTopicId(myMsg->getTopicId());

							//TransportAddress remoteAddress = *it;
							//establishTcpConnection(*it);
							sendTcpData(tweet, *it);

							//stats
							serverNumTCPSent++;
							emit(numTCPSentSig, serverNumTCPSent);
							servBytesSent = tweet->getByteLength();
							emit(bytesTCPSentTweetSig, servBytesSent);

							EV << "\n0.0.0.0.0.0.0.0.0.0.0.0.\n0.0.0.0.0.0.0.0.0.0.0.0.0\nForwarded to"
									<< *it << "\n";
						}
					}

					break;
				}
			}*/
			break;
		}
		case USERS_REQUEST:
		{

			EV << "\naaaaaaaaaaaa\naaaaaaaaaaa\nOnline users requested";
			ServerMessage *userreq = new ServerMessage();

			userreq->setType(USERS_REQUEST); // set the message type to PING
			userreq->setTopics(onlineTopics);
			thisNode.setPort(24000);
			userreq->setSenderAddress(thisNode); // set the sender address to our own
			userreq->setByteLength(150); // set the message length to 100 bytes

			sendTcpData(userreq, myMsg->getSenderAddress());

			//stats collect
			serverNumTCPSent++;
			emit(numTCPSentSig, serverNumTCPSent);
			int servBytesSent = userreq->getByteLength();
			emit(bytesTCPSentReqUsersSig, servBytesSent);
			servBytesSent = myMsg->getByteLength();
			emit(bytesTCPRecReqUsersSig, servBytesSent);
		}

    }

    // Message isn't needed any more -> delete it
    delete msg;
}

void PastryServer::handleConnectionEvent(EvCode code, TransportAddress address)
{
    BaseTcpSupport::handleConnectionEvent(code, address);
}

void PastryServer::joinServer(TransportAddress client, int id){
	EV << "PastryServer::handleDataReceived => " << thisNode.getIp() << ": Got JOIN packet from "
	                << client.getIp() << ":" << client.getPort()<< ", replying with an ACK!"
	                <<  std::endl;

	        // send it back to its owner

	        ServerMessage *ackMessage = new ServerMessage();

	        ackMessage->setType(SERVER_ACKJOIN); // set the message type to PING
	        //ackMessage->setTopics(onlineTopics);
	        thisNode.setPort(24000);
	        ackMessage->setSenderAddress(thisNode); // set the sender address to our own
	        ackMessage->setByteLength(20); // set the message length to 100 bytes

	        if (connections.find(client) == connections.end()) {

	            // connect and send message
	            TransportAddress remoteAddress = TransportAddress(client.getIp(), 24000);
	            establishTcpConnection(remoteAddress);
	            connections.insert(client);
	            onlineTopics.push_back(id);
	        }

	        sendTcpData(ackMessage, client);

	        //stats collect
	        serverNumTCPSent++;
	        emit(numTCPSentSig, serverNumTCPSent);
	        int servBytesSent = ackMessage->getByteLength();
	        emit(bytesTCPSentJoinSig, servBytesSent);


	        EV << "\n~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~\n"
	        	            	        		<< "Message byte lenght: " << servBytesSent;


}
