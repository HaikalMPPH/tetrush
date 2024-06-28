#include "subscriber-publisher.hpp"
#include <algorithm>

event_subscriber::event_subscriber()
  : notify_fn_ {}
{}

event_subscriber*
event_subscriber::add_notify_callback(const char* key, notify_callback fn) {
  notify_fn_[key] = fn;
  return this;
}

void
event_subscriber::on_notify(const char* key) {
  if (notify_fn_[key] != nullptr) {
    notify_fn_[key]();
  }
}

// ================================================================================

event_publisher::event_publisher()
  : subscribers_ {}
{}

event_publisher*
event_publisher::add_subscriber(event_subscriber* sub) {
  subscribers_.push_back(sub);
  return this;
}
event_publisher* 
event_publisher::remove_subscriber(event_subscriber* sub) {
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

event_publisher*
event_publisher::add_notify_callback_to_all_subscriber(const char* key, notify_callback fn) {
  for (event_subscriber* subs : subscribers_) {
    subs->add_notify_callback(key, fn);
  }
  return this;
}

void
event_publisher::notify_subscriber(const char* key) {
  for (event_subscriber* subs : subscribers_) {
    if (subs != nullptr) {
      subs->on_notify(key);
    }
  }
}
