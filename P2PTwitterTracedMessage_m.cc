//
// Generated file, do not edit! Created by opp_msgc 4.1 from applications/p2ptwitter/P2PTwitterTracedMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "P2PTwitterTracedMessage_m.h"

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




Register_Class(P2PTwitterTracedMessage);

P2PTwitterTracedMessage::P2PTwitterTracedMessage(const char *name, int kind) : cPacket(name,kind)
{
    this->mcastId_var = 0;
    this->senderId_var = 0;
    this->receiverId_var = 0;
    this->tweetID_var = 0;
    this->uName_var = 0;
    this->screen_name_var = 0;
    this->tweet_var = 0;
    this->uId_var = 0;
    this->uTweet_count_var = 0;
}

P2PTwitterTracedMessage::P2PTwitterTracedMessage(const P2PTwitterTracedMessage& other) : cPacket()
{
    setName(other.getName());
    operator=(other);
}

P2PTwitterTracedMessage::~P2PTwitterTracedMessage()
{
}

P2PTwitterTracedMessage& P2PTwitterTracedMessage::operator=(const P2PTwitterTracedMessage& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->groupId_var = other.groupId_var;
    this->mcastId_var = other.mcastId_var;
    this->senderId_var = other.senderId_var;
    this->receiverId_var = other.receiverId_var;
    this->tweetID_var = other.tweetID_var;
    this->uName_var = other.uName_var;
    this->screen_name_var = other.screen_name_var;
    this->tweet_var = other.tweet_var;
    this->uId_var = other.uId_var;
    this->uTweet_count_var = other.uTweet_count_var;
    return *this;
}

void P2PTwitterTracedMessage::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->groupId_var);
    doPacking(b,this->mcastId_var);
    doPacking(b,this->senderId_var);
    doPacking(b,this->receiverId_var);
    doPacking(b,this->tweetID_var);
    doPacking(b,this->uName_var);
    doPacking(b,this->screen_name_var);
    doPacking(b,this->tweet_var);
    doPacking(b,this->uId_var);
    doPacking(b,this->uTweet_count_var);
}

void P2PTwitterTracedMessage::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->groupId_var);
    doUnpacking(b,this->mcastId_var);
    doUnpacking(b,this->senderId_var);
    doUnpacking(b,this->receiverId_var);
    doUnpacking(b,this->tweetID_var);
    doUnpacking(b,this->uName_var);
    doUnpacking(b,this->screen_name_var);
    doUnpacking(b,this->tweet_var);
    doUnpacking(b,this->uId_var);
    doUnpacking(b,this->uTweet_count_var);
}

OverlayKey& P2PTwitterTracedMessage::getGroupId()
{
    return groupId_var;
}

void P2PTwitterTracedMessage::setGroupId(const OverlayKey& groupId_var)
{
    this->groupId_var = groupId_var;
}

long P2PTwitterTracedMessage::getMcastId() const
{
    return mcastId_var;
}

void P2PTwitterTracedMessage::setMcastId(long mcastId_var)
{
    this->mcastId_var = mcastId_var;
}

int P2PTwitterTracedMessage::getSenderId() const
{
    return senderId_var;
}

void P2PTwitterTracedMessage::setSenderId(int senderId_var)
{
    this->senderId_var = senderId_var;
}

int P2PTwitterTracedMessage::getReceiverId() const
{
    return receiverId_var;
}

void P2PTwitterTracedMessage::setReceiverId(int receiverId_var)
{
    this->receiverId_var = receiverId_var;
}

int P2PTwitterTracedMessage::getTweetID() const
{
    return tweetID_var;
}

void P2PTwitterTracedMessage::setTweetID(int tweetID_var)
{
    this->tweetID_var = tweetID_var;
}

const char * P2PTwitterTracedMessage::getUName() const
{
    return uName_var.c_str();
}

void P2PTwitterTracedMessage::setUName(const char * uName_var)
{
    this->uName_var = uName_var;
}

const char * P2PTwitterTracedMessage::getScreen_name() const
{
    return screen_name_var.c_str();
}

void P2PTwitterTracedMessage::setScreen_name(const char * screen_name_var)
{
    this->screen_name_var = screen_name_var;
}

const char * P2PTwitterTracedMessage::getTweet() const
{
    return tweet_var.c_str();
}

void P2PTwitterTracedMessage::setTweet(const char * tweet_var)
{
    this->tweet_var = tweet_var;
}

int P2PTwitterTracedMessage::getUId() const
{
    return uId_var;
}

void P2PTwitterTracedMessage::setUId(int uId_var)
{
    this->uId_var = uId_var;
}

int P2PTwitterTracedMessage::getUTweet_count() const
{
    return uTweet_count_var;
}

void P2PTwitterTracedMessage::setUTweet_count(int uTweet_count_var)
{
    this->uTweet_count_var = uTweet_count_var;
}

class P2PTwitterTracedMessageDescriptor : public cClassDescriptor
{
  public:
    P2PTwitterTracedMessageDescriptor();
    virtual ~P2PTwitterTracedMessageDescriptor();

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

Register_ClassDescriptor(P2PTwitterTracedMessageDescriptor);

P2PTwitterTracedMessageDescriptor::P2PTwitterTracedMessageDescriptor() : cClassDescriptor("P2PTwitterTracedMessage", "cPacket")
{
}

P2PTwitterTracedMessageDescriptor::~P2PTwitterTracedMessageDescriptor()
{
}

bool P2PTwitterTracedMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<P2PTwitterTracedMessage *>(obj)!=NULL;
}

const char *P2PTwitterTracedMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int P2PTwitterTracedMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount(object) : 10;
}

unsigned int P2PTwitterTracedMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *P2PTwitterTracedMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "groupId",
        "mcastId",
        "senderId",
        "receiverId",
        "tweetID",
        "uName",
        "screen_name",
        "tweet",
        "uId",
        "uTweet_count",
    };
    return (field>=0 && field<10) ? fieldNames[field] : NULL;
}

int P2PTwitterTracedMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "groupId")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "mcastId")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderId")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "receiverId")==0) return base+3;
    if (fieldName[0]=='t' && strcmp(fieldName, "tweetID")==0) return base+4;
    if (fieldName[0]=='u' && strcmp(fieldName, "uName")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "screen_name")==0) return base+6;
    if (fieldName[0]=='t' && strcmp(fieldName, "tweet")==0) return base+7;
    if (fieldName[0]=='u' && strcmp(fieldName, "uId")==0) return base+8;
    if (fieldName[0]=='u' && strcmp(fieldName, "uTweet_count")==0) return base+9;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *P2PTwitterTracedMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OverlayKey",
        "long",
        "int",
        "int",
        "int",
        "string",
        "string",
        "string",
        "int",
        "int",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : NULL;
}

const char *P2PTwitterTracedMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int P2PTwitterTracedMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    P2PTwitterTracedMessage *pp = (P2PTwitterTracedMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string P2PTwitterTracedMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    P2PTwitterTracedMessage *pp = (P2PTwitterTracedMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getGroupId(); return out.str();}
        case 1: return long2string(pp->getMcastId());
        case 2: return long2string(pp->getSenderId());
        case 3: return long2string(pp->getReceiverId());
        case 4: return long2string(pp->getTweetID());
        case 5: return oppstring2string(pp->getUName());
        case 6: return oppstring2string(pp->getScreen_name());
        case 7: return oppstring2string(pp->getTweet());
        case 8: return long2string(pp->getUId());
        case 9: return long2string(pp->getUTweet_count());
        default: return "";
    }
}

bool P2PTwitterTracedMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    P2PTwitterTracedMessage *pp = (P2PTwitterTracedMessage *)object; (void)pp;
    switch (field) {
        case 1: pp->setMcastId(string2long(value)); return true;
        case 2: pp->setSenderId(string2long(value)); return true;
        case 3: pp->setReceiverId(string2long(value)); return true;
        case 4: pp->setTweetID(string2long(value)); return true;
        case 5: pp->setUName((value)); return true;
        case 6: pp->setScreen_name((value)); return true;
        case 7: pp->setTweet((value)); return true;
        case 8: pp->setUId(string2long(value)); return true;
        case 9: pp->setUTweet_count(string2long(value)); return true;
        default: return false;
    }
}

const char *P2PTwitterTracedMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "OverlayKey",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<10) ? fieldStructNames[field] : NULL;
}

void *P2PTwitterTracedMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    P2PTwitterTracedMessage *pp = (P2PTwitterTracedMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getGroupId()); break;
        default: return NULL;
    }
}


