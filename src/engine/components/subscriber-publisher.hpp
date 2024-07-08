#ifndef SUBSCRIBER_PUBLISHER_HPP
#define SUBSCRIBER_PUBLISHER_HPP

#include <functional>
#include "../utils/typedefs.hpp"

class event_subscriber {
public:
  using notify_callback = std::function<void()>;

private:
  map<const char*, notify_callback> notify_fn_;
  friend class event_publisher;

public:
  event_subscriber();

public:
  event_subscriber* add_notify_callback(const char* key, notify_callback fn);

private:
  // WARNING: DO NOT USE THIS DIRECTLY!
  void on_notify(const char* key);
};

// ================================================================================

class event_publisher {
private:
  using notify_callback = event_subscriber::notify_callback;
  vector<event_subscriber*> subscribers_;

public:
  event_publisher();

public:
  event_publisher* add_subscriber(event_subscriber* sub);
  event_publisher* remove_subscriber(event_subscriber* sub);
  event_publisher* add_notify_callback_to_all_subscriber(const char* key, notify_callback fn);
  void notify_subscriber(const char* key);
};

#endif // SUBSCRIBER_PUBLISHER_HPP
