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

//
// @author Antonio Zea
//

cplusplus {{
#include <TransportAddress.h>
#include <vector>

typedef std::vector<int> TopicList;
}}


// import the IP Address class
class noncobject TransportAddress;
class noncobject TopicList;

// first, we declare an enum to tell the message types apart:
enum ServerMessageType 
{
    SERVER_JOIN = 1;           // outgoing message
    SERVER_ACKJOIN = 2;
    SUBSCRIBE = 3;           // returning message
    UNSUBSCRIBE = 4;
    SERVER_LEAVE = 5;
    TWEET = 6;
    USERS_REQUEST = 7;
}

// now we declare the message
packet ServerMessage 
{
    int type enum(ServerMessageType);      // message type
    TransportAddress senderAddress;  // address of the node that sent the message
    int topicId;
   	string tweet;
   	TopicList topics;
}

