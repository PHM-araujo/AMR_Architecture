#ifndef NOTIFY_H_
#define NOTIFY_H_

#include <memory>
#include <vector>

#include "AnalogObserver.h"

class Notify {
 public:
  void Attach(std::shared_ptr<AnalogObserver> observer) {
    analog_observer_.push_back(observer);
  }

  void NotifyAnalogObserver(const unsigned int& pin,
                            const unsigned int& value) {
    for (const auto& observer : analog_observer_) {
      observer->OnAnalogObserver(pin, value);
    }
  }

 private:
  std::vector<std::shared_ptr<AnalogObserver>> analog_observer_;
};

#endif /* NOTIFY_H_ */
