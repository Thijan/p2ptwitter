//
// Generated file, do not edit! Created by opp_msgc 4.1 from applications/p2ptwitter/ServerMessage.msg.
//

#ifndef _SERVERMESSAGE_M_H_
#define _SERVERMESSAGE_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0401
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// cplusplus {{
#include <TransportAddress.h>
#include <vector>

typedef std::vector<int> TopicList;
// }}



/**
 * Enum generated from <tt>applications/p2ptwitter/ServerMessage.msg</tt> by opp_msgc.
 * <pre>
 * enum ServerMessageType 
 * {
 *     SERVER_JOIN = 1;           
 *     SERVER_ACKJOIN = 2;
 *     SUBSCRIBE = 3;           
 *     UNSUBSCRIBE = 4;
 *     SERVER_LEAVE = 5;
 *     TWEET = 6;
 *     USERS_REQUEST = 7;
 * }
 * </pre>
 */
enum ServerMessageType {
    SERVER_JOIN = 1,
    SERVER_ACKJOIN = 2,
    SUBSCRIBE = 3,
    UNSUBSCRIBE = 4,
    SERVER_LEAVE = 5,
    TWEET = 6,
    USERS_REQUEST = 7
};

/**
 * Class generated from <tt>applications/p2ptwitter/ServerMessage.msg</tt> by opp_msgc.
 * <pre>
 * packet ServerMessage 
 * {
 *     int type enum(ServerMessageType);      
 *     TransportAddress senderAddress;  
 *     int topicId;
 *    	string tweet;
 *    	TopicList topics;
 * }
 * </pre>
 */
class ServerMessage : public ::cPacket
{
  protected:
    int type_var;
    ::TransportAddress senderAddress_var;
    int topicId_var;
    opp_string tweet_var;
    ::TopicList topics_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ServerMessage&);

  public:
    ServerMessage(const char *name=NULL, int kind=0);
    ServerMessage(const ServerMessage& other);
    virtual ~ServerMessage();
    ServerMessage& operator=(const ServerMessage& other);
    virtual ServerMessage *dup() const {return new ServerMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getType() const;
    virtual void setType(int type_var);
    virtual TransportAddress& getSenderAddress();
    virtual const TransportAddress& getSenderAddress() const {return const_cast<ServerMessage*>(this)->getSenderAddress();}
    virtual void setSenderAddress(const TransportAddress& senderAddress_var);
    virtual int getTopicId() const;
    virtual void setTopicId(int topicId_var);
    virtual const char * getTweet() const;
    virtual void setTweet(const char * tweet_var);
    virtual TopicList& getTopics();
    virtual const TopicList& getTopics() const {return const_cast<ServerMessage*>(this)->getTopics();}
    virtual void setTopics(const TopicList& topics_var);
};

inline void doPacking(cCommBuffer *b, ServerMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, ServerMessage& obj) {obj.parsimUnpack(b);}


#endif // _SERVERMESSAGE_M_H_
