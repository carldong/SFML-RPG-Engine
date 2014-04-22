#ifndef __MESSAGE_BUS_H__
#define __MESSAGE_BUS_H__

#include <list>
#include <queue>
#include <string>
#include <cassert>
#include <set>

class Message;
class Listener;
class MessageBus;
/**
 */
class Message {
public:
  enum Type {
    LogicTick,
    Type_Count
  };

public:
  Message(Type type, const std::string& desc="") :
    mType(type) {std::hash<std::string> hash; mDesc = hash(desc);} 

public:
  Type mType;
  size_t mDesc;
};

/**
 */
template<typename T>
class RichMessage : public Message{
public:
  RichMessage(Type type, const T& value, const std::string& desc="") :
    Message(type, desc), mValue(value) {}
  
public:
  T mValue;
};


/**
 */
class Listener {
public:
  Listener(MessageBus* bus) : mMessageBus(bus) {assert(bus != nullptr);}
  ~Listener();

  virtual void notify(const Message*) {}
  
private:
  MessageBus* mMessageBus;
};


/**
 */
class MessageBus {
public:
  MessageBus() {}

  // Accessors
  size_t numListeners() const {return mListenerSet.size();}
  size_t queueLength() const {return mMessageQueue.size();}

  // Actions
  void post(Message* message);
  bool registerListener(Listener* listener);
  bool deregisterListener(Listener* listener);

private:
  void handleQueue();
  void broadcast(Message* message);

private:
  std::set<Listener*> mListenerSet;
  std::queue<Message*> mMessageQueue;
};

#endif // __MESSAGE_BUS_H__
