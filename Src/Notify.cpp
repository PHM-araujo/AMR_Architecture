#include "Notify/Notify.h"

#include <functional>
#include <list>
#include <memory>
#include <vector>

#include "Notify/AnalogObserver.h"
#include "Notify/DigitalObserver.h"
#include "Notify/TimerObserver.h"

std::list<std::function<void(const unsigned int&, const unsigned int&)>>
    Notify::analog_observer_list_;

std::list<std::function<void(const unsigned int&, const bool&)>>
    Notify::digital_observer_list_;

std::list<std::function<void(const unsigned int&)>>
    Notify::timer_observer_list_;

auto Notify::AddListener(AnalogObserver& listener) -> void {
  analog_observer_list_.emplace_back([&listener](auto&& pin, auto&& value) {
    listener.OnAnalogObserver(pin, value);
  });
}

auto Notify::AddListener(DigitalObserver& listener) -> void {
  digital_observer_list_.emplace_back([&listener](auto&& pin, auto&& value) {
    listener.OnDigitalObserver(pin, value);
  });
}

auto Notify::AddListener(TimerObserver& listener) -> void {
  timer_observer_list_.emplace_back(
      [&listener](auto&& timer) { listener.OnTimerObserver(timer); });
}

void Notify::NotifyAnalogObserver(const unsigned int& pin,
                                  const unsigned int& value) {
  for (auto&& observer : analog_observer_list_) {
    observer(pin, value);
  }
}

void Notify::NotifyDigitalObserver(const unsigned int& pin, const bool& value) {
  for (auto&& digital : digital_observer_list_) {
    digital(pin, value);
  }
}

void Notify::NotifyTimerObserver(const unsigned int& timer) {
  for (auto&& timer_call : timer_observer_list_) {
    timer_call(timer);
  }
}
