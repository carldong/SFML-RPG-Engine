#include <MessageBus.hpp>

Listener::~Listener() {
  if (mMessageBus != nullptr)
    mMessageBus->deregisterListener(this);
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
  size_t result = mListenerSet.erase(listener);
  return result == 1;
}

/**
   Handle the queue stored
 */
void MessageBus::handleQueue() {
  while (!mMessageQueue.empty()) {
    Message* msg = mMessageQueue.front();
    broadcast(msg);
    mMessageQueue.pop();
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
