#ifndef APPLYOBSERVER_H_
#define APPLYOBSERVER_H_

#include "Notify/AnalogObserver.h"
#include "Notify/DigitalObserver.h"
#include "Notify/Notify.h"
#include "Notify/TimerObserver.h"

class ApplyObserver : public AnalogObserver,
                      public DigitalObserver,
                      public TimerObserver {
 private:
  void OnAnalogObserver(const unsigned int& pin,
                        const unsigned int& value) override {
    printf("OnAnalogObserver\n");
  }

  void OnDigitalObserver(const unsigned int& pin, const bool& value) override {
    printf("OnDigitalObserver\n");
  }

  void OnTimerObserver(const unsigned int& timer) override {
    printf("OnTimerObserver\n");
  }

 public:
  explicit ApplyObserver() {
    Notify::AddListener(*static_cast<AnalogObserver*>(this));
    Notify::AddListener(*static_cast<DigitalObserver*>(this));
    Notify::AddListener(*static_cast<TimerObserver*>(this));
  }

  ~ApplyObserver() = default;
};

#endif