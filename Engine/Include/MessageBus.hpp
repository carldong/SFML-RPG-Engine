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
  bool registerListener(Listener* listener);
  bool deregisterListener(Listener* listener);

private:
  void handleQueue();
  void broadcast(Message* message);

private:
  std::set<Listener*> mListenerSet;
  std::queue<Message*> mMessageQueue;
};

/**
 */
class Listener {
public:
  Listener() : mMessageBus(nullptr) {}
  Listener(MessageBus* bus) : mMessageBus(bus) {
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
