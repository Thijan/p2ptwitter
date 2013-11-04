//
// Generated file, do not edit! Created by opp_msgc 4.1 from applications/p2ptwitter/ServerMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "ServerMessage_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("ServerMessageType");
    if (!e) enums.getInstance()->add(e = new cEnum("ServerMessageType"));
    e->insert(SERVER_JOIN, "SERVER_JOIN");
    e->insert(SERVER_ACKJOIN, "SERVER_ACKJOIN");
    e->insert(SUBSCRIBE, "SUBSCRIBE");
    e->insert(UNSUBSCRIBE, "UNSUBSCRIBE");
    e->insert(SERVER_LEAVE, "SERVER_LEAVE");
    e->insert(TWEET, "TWEET");
    e->insert(USERS_REQUEST, "USERS_REQUEST");
);

Register_Class(ServerMessage);

ServerMessage::ServerMessage(const char *name, int kind) : cPacket(name,kind)
{
    this->type_var = 0;
    this->topicId_var = 0;
    this->tweet_var = 0;
}

ServerMessage::ServerMessage(const ServerMessage& other) : cPacket()
{
    setName(other.getName());
    operator=(other);
}

ServerMessage::~ServerMessage()
{
}

ServerMessage& ServerMessage::operator=(const ServerMessage& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->type_var = other.type_var;
    this->senderAddress_var = other.senderAddress_var;
    this->topicId_var = other.topicId_var;
    this->tweet_var = other.tweet_var;
    this->topics_var = other.topics_var;
    return *this;
}

void ServerMessage::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->type_var);
    doPacking(b,this->senderAddress_var);
    doPacking(b,this->topicId_var);
    doPacking(b,this->tweet_var);
    doPacking(b,this->topics_var);
}

void ServerMessage::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->senderAddress_var);
    doUnpacking(b,this->topicId_var);
    doUnpacking(b,this->tweet_var);
    doUnpacking(b,this->topics_var);
}

int ServerMessage::getType() const
{
    return type_var;
}

void ServerMessage::setType(int type_var)
{
    this->type_var = type_var;
}

TransportAddress& ServerMessage::getSenderAddress()
{
    return senderAddress_var;
}

void ServerMessage::setSenderAddress(const TransportAddress& senderAddress_var)
{
    this->senderAddress_var = senderAddress_var;
}

int ServerMessage::getTopicId() const
{
    return topicId_var;
}

void ServerMessage::setTopicId(int topicId_var)
{
    this->topicId_var = topicId_var;
}

const char * ServerMessage::getTweet() const
{
    return tweet_var.c_str();
}

void ServerMessage::setTweet(const char * tweet_var)
{
    this->tweet_var = tweet_var;
}

TopicList& ServerMessage::getTopics()
{
    return topics_var;
}

void ServerMessage::setTopics(const TopicList& topics_var)
{
    this->topics_var = topics_var;
}

class ServerMessageDescriptor : public cClassDescriptor
{
  public:
    ServerMessageDescriptor();
    virtual ~ServerMessageDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ServerMessageDescriptor);

ServerMessageDescriptor::ServerMessageDescriptor() : cClassDescriptor("ServerMessage", "cPacket")
{
}

ServerMessageDescriptor::~ServerMessageDescriptor()
{
}

bool ServerMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ServerMessage *>(obj)!=NULL;
}

const char *ServerMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ServerMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int ServerMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *ServerMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
        "senderAddress",
        "topicId",
        "tweet",
        "topics",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int ServerMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderAddress")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "topicId")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "tweet")==0) return base+3;
    if (fieldName[0]=='t' && strcmp(fieldName, "topics")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ServerMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "TransportAddress",
        "int",
        "string",
        "TopicList",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *ServerMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "ServerMessageType";
            return NULL;
        default: return NULL;
    }
}

int ServerMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ServerMessage *pp = (ServerMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ServerMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ServerMessage *pp = (ServerMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        case 1: {std::stringstream out; out << pp->getSenderAddress(); return out.str();}
        case 2: return long2string(pp->getTopicId());
        case 3: return oppstring2string(pp->getTweet());
        case 4: {std::stringstream out; out << pp->getTopics(); return out.str();}
        default: return "";
    }
}

bool ServerMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ServerMessage *pp = (ServerMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        case 2: pp->setTopicId(string2long(value)); return true;
        case 3: pp->setTweet((value)); return true;
        default: return false;
    }
}

const char *ServerMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        "TransportAddress",
        NULL,
        NULL,
        "TopicList",
    };
    return (field>=0 && field<5) ? fieldStructNames[field] : NULL;
}

void *ServerMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ServerMessage *pp = (ServerMessage *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getSenderAddress()); break;
        case 4: return (void *)(&pp->getTopics()); break;
        default: return NULL;
    }
}


