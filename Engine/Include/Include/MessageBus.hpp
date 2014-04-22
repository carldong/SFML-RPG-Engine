#ifndef __MESSAGE_BUS_H__
#define __MESSAGE_BUS_H__

#include <list>
#include <queue>

/**
 */
class Message {
public:
  enum Type {
    Type_Count,
  };

public:
  Message(Type type, const std::string& desc="") :
    mType(type), mDesc(std::hash<std::string>(desc));

public:
  Type mType;
  size_t mDesc;
};

/**
 */
template<T>
class RichMessage : public Message{
public:
  RichMessage(Type type, const T& value, const std::string& desc="") :
    Message(type, desc), mValue(value);
  
public:
  T mValue;
};

/**
 */
class Listener {
public:
  Listener(MessageBus* bus) : mMessageBus(bus) {assert(bus != nullptr);}
  ~Listener() {assert(mMessageBus!=nullptr); mMessageBus.deregister(this);}

  virtual void notify(const Message*);
  
private:
  MessageBus* mMessageBus;
};

/**
 */
class MessageBus {
public:
  MessageBus();

  void post(const Message*);
  void register(const Listener* listener);
  void deregister(const Listener* listener);

private:
  void handleQueue();
  void broadcast();

private:
  std::list<Listener*> mListenerList;
  std::queue<Listener*> mRegisterQueue;
  std::queue<Listener*> mDeregisterQueue;
  std::queue<Message*> mMessageQueue;
};

#endif // __MESSAGE_BUS_H__
