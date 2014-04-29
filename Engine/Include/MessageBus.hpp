#ifndef __MESSAGE_BUS_H__
#define __MESSAGE_BUS_H__

#include <list>
#include <queue>
#include <string>
#include <cassert>
#include <set>
#include <iostream>

class Message;
class Listener;
class MessageBus;

/**
   Class for messages
 */
class Message {
public:
  enum Type {
    LogicTick,
    Pause,
    Quit,
    Rich,
    TypeCount
  };

public:
  Message(Type type_, const std::string& desc_="") :
    type(type_), desc(desc_) {} 

public:
  Type type;
  std::string desc;
};

/**
   An extention of Messages which can contain other data
 */
template<typename T>
class RichMessage : public Message{
public:
  RichMessage(Type type, const T& value_, const std::string& desc_="") :
    Message(type, desc_), value(value_) {assert(type>=Type::Rich);}
  
public:
  T value;
};

/**
   This is the class that enables everything else to communicate.
   It is driven by LogicTicks as clock source. At each LogicTick message
   received, the entire game is updated
 */
class MessageBus {
public:
  MessageBus() {}
  ~MessageBus();

  // Accessors
  size_t numListeners() const {return mListenerSet.size();}
  size_t queueLength() const {return mMessageQueue.size();}

  // Actions
  void post(Message* message);
  void registerListener(Listener* listener);
  void deregisterListener(Listener* listener);

private:
  void handleQueue();
  void broadcast(Message* message);

private:
  std::set<Listener*> mListenerSet;
  std::queue<Message*> mMessageQueue;
};

/**
   The base class for listeners that receives messages from MessageBus
 */
class Listener {
public:
  //Listener() : mMessageBus(nullptr) {}
  Listener(MessageBus* bus) : mMessageBus(nullptr) {
    registerTo(bus);
  }
  ~Listener();

  void registerTo(MessageBus* bus) {
    assert(bus != nullptr);
    if (mMessageBus != nullptr)
      mMessageBus->deregisterListener(this);
    mMessageBus = bus;
    mMessageBus->registerListener(this);
  }
  void deregister() { mMessageBus = nullptr; }
  virtual void notify(Message* msg) {}
  
protected:
  MessageBus* mMessageBus;
};

#endif // __MESSAGE_BUS_H__
