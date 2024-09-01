#ifndef TIMEROBSERVER_H_
#define TIMEROBSERVER_H_

class TimerObserver {
 public:
  virtual ~TimerObserver() = default;
  virtual void OnTimerObserver(const unsigned int& timer) = 0;
};

#endif