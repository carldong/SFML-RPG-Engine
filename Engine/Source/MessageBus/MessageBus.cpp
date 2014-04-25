#include <MessageBus.hpp>

Listener::~Listener() {
  if (mMessageBus != nullptr)
    mMessageBus->deregisterListener(this);
}

MessageBus::~MessageBus() {
  std::set<Listener*>::iterator itr;
  for (Listener* listener : mListenerSet) {
    listener->deregister();
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
 */
void MessageBus::registerListener(Listener* listener) {
  std::pair<std::set<Listener*>::iterator, bool> result =
    mListenerSet.insert(listener);
  assert (result.second);
}

/**
   Deregister a listener
 */
void MessageBus::deregisterListener(Listener* listener) {
  std::set<Listener*>::iterator itr =
    mListenerSet.find(listener);
  assert (itr != mListenerSet.end());
  (*itr)->deregister();
  mListenerSet.erase(itr);
}

/**
   Handle the queue stored
 */
void MessageBus::handleQueue() {
  while (!mMessageQueue.empty()) {
    Message* msg = mMessageQueue.front();
    broadcast(msg);
    mMessageQueue.pop();
    // Message is not needed after broadcasting
    delete msg;
  }
}

/**
   Broadcast a message through message bus
 */
void MessageBus::broadcast(Message* message) {
  for (Listener* listener : mListenerSet) {
    listener->notify(message);
  }
}
