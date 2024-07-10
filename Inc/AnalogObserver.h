#ifndef ANALOGOBSERVER_H_
#define ANALOGOBSERVER_H_

class AnalogObserver {
 public:
  virtual ~AnalogObserver() = default;
  virtual void OnAnalogObserver(const unsigned int& pin,
                                const unsigned int& value) = 0;
};

#endif