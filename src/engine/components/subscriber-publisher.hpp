#ifndef SUBSCRIBER_PUBLISHER_HPP
#define SUBSCRIBER_PUBLISHER_HPP

#include <functional>
#include "../utils/typedefs.hpp"

class EventSubscriber {
public:
  using NotifyCallback = std::function<void()>;

private:
  UnorderedMap<const char*, NotifyCallback> notify_fn_;

public:
  EventSubscriber();

public:
  EventSubscriber* addNotifyCallback(const char* key, NotifyCallback fn);

  // WARNING: DO NOT USE THIS DIRECTLY!
  void onNotify(const char* key);
};

// ================================================================================

class EventPublisher {
private:
  using NotifyCallback = EventSubscriber::NotifyCallback;
  Vector<EventSubscriber*> subscribers_;

public:
  EventPublisher();

public:
  EventPublisher* addSubscriber(EventSubscriber* sub);
  EventPublisher* removeSubscriber(EventSubscriber* sub);
  EventPublisher* addNotifyCallbackToAllSubscriber(const char* key, NotifyCallback fn);
  void notifySubscriber(const char* key);
};

#endif // SUBSCRIBER_PUBLISHER_HPP
