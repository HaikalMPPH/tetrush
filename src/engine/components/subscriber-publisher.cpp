#include "subscriber-publisher.hpp"
#include <algorithm>

EventSubscriber::EventSubscriber()
  : notify_fn_ {}
{}

EventSubscriber*
EventSubscriber::addNotifyCallback(const char* key, NotifyCallback fn) {
  notify_fn_[key] = fn;
  return this;
}

void
EventSubscriber::onNotify(const char* key) {
  if (notify_fn_[key] != nullptr) {
    notify_fn_[key]();
  }
}

// ================================================================================

EventPublisher::EventPublisher()
  : subscribers_ {}
{}

EventPublisher*
EventPublisher::addSubscriber(EventSubscriber* sub) {
  subscribers_.push_back(sub);
  return this;
}
EventPublisher* 
EventPublisher::removeSubscriber(EventSubscriber* sub) {
  subscribers_.erase(
    std::remove(
      subscribers_.begin(), 
      subscribers_.end(), 
      sub
    ),
    subscribers_.end()
  );

  return this;
}

EventPublisher*
EventPublisher::addNotifyCallbackToAllSubscriber(const char* key, NotifyCallback fn) {
  for (EventSubscriber* subs : subscribers_) {
    subs->addNotifyCallback(key, fn);
  }
  return this;
}

void
EventPublisher::notifySubscriber(const char* key) {
  for (EventSubscriber* subs : subscribers_) {
    if (subs != nullptr) {
      subs->onNotify(key);
    }
  }
}
