#include <MessageBus.hpp>

/**
   Destructor of Listener. Deregisters self
 */
Listener::~Listener() {
  if (mMessageBus != nullptr)
    mMessageBus->deregisterListener(this);
}

/**
   Destructor of MessageBus. Deregisters every listener.
 */
MessageBus::~MessageBus() {
  for (Listener* listener : mListenerSet) {
    listener->deregister();
    delete listener;
  }
  mListenerSet.clear();
}

/**
   Posts a message. If the message is LogicTick, then process queue

   @param message The message to be posted
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

   @param listener The listener to be registered
 */
void MessageBus::registerListener(Listener* listener) {
  std::pair<std::set<Listener*>::iterator, bool> result =
    mListenerSet.insert(listener);
  assert (result.second);
}

/**
   Deregister a listener

   @param listener The listener to be deregistered
 */
void MessageBus::deregisterListener(Listener* listener) {
  std::set<Listener*>::iterator itr =
    mListenerSet.find(listener);
  assert (itr != mListenerSet.end());
  (*itr)->deregister();
  mListenerSet.erase(itr);
}

/**
   Handle the message queue stored. Messages are deleted after broadcasting
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

   @param message The message to be broadcasted
 */
void MessageBus::broadcast(Message* message) {
  for (Listener* listener : mListenerSet) {
    listener->notify(message);
  }
}
