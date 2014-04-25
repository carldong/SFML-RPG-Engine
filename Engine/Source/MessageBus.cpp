#include <MessageBus.hpp>

Listener::~Listener() {
  if (mMessageBus != nullptr)
    mMessageBus->deregisterListener(this);
}

MessageBus::~MessageBus() {
  std::set<Listener*>::iterator itr;
  for (itr=mListenerSet.begin(); itr!=mListenerSet.end();
       ++itr) {
    (*itr)->deregister();
  }
  mListenerSet.clear();
}

/**
   Posts a message. If the message is LogicTick, then process queue
 */
void MessageBus::post(Message* message) {
  assert (message != nullptr);
  mMessageQueue.push(message);
  if (message->type == Message::LogicTick) {
    handleQueue();
  }
}

/**
   Register a listener

   @return Return true if listener is successfully registered
 */
bool MessageBus::registerListener(Listener* listener) {
  std::pair<std::set<Listener*>::iterator, bool> result =
    mListenerSet.insert(listener);
  return result.second;
}

/**
   Deregister a listener

   @return Return true if listener is successfully removed
 */
bool MessageBus::deregisterListener(Listener* listener) {
  std::set<Listener*>::iterator itr =
    mListenerSet.find(listener);
  if (itr == mListenerSet.end()) return false;
  (*itr)->deregister();
  mListenerSet.erase(itr);
  return true;
}

/**
   Handle the queue stored
 */
void MessageBus::handleQueue() {
  while (!mMessageQueue.empty()) {
    Message* msg = mMessageQueue.front();
    broadcast(msg);
    mMessageQueue.pop();
    delete msg;
  }
}

/**
   Broadcast a message through message bus
 */
void MessageBus::broadcast(Message* message) {
  std::set<Listener*>::iterator itr = mListenerSet.begin();
  while (itr != mListenerSet.end()) {
    (*itr)->notify(message);
    ++itr;
  }
}
