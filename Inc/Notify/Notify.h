#ifndef NOTIFY_H_
#define NOTIFY_H_

#include <functional>
#include <list>
#include <memory>
#include <vector>

#include "AnalogObserver.h"
#include "DigitalObserver.h"
#include "TimerObserver.h"

class Notify {
 public:
  static auto AddListener(AnalogObserver& listener) -> void;

  static auto AddListener(DigitalObserver& listener) -> void;

  static auto AddListener(TimerObserver& listener) -> void;

  static void NotifyAnalogObserver(const unsigned int& pin,
                                   const unsigned int& value);

  static void NotifyDigitalObserver(const unsigned int& pin, const bool& value);

  static void NotifyTimerObserver(const unsigned int& timer);

 private:
  static std::list<
      std::function<void(const unsigned int&, const unsigned int&)>>
      analog_observer_list_;

  static std::list<std::function<void(const unsigned int&, const bool&)>>
      digital_observer_list_;

  static std::list<std::function<void(const unsigned int&)>>
      timer_observer_list_;
};

#endif /* NOTIFY_H_ */