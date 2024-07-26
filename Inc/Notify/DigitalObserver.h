#ifndef DIGITALOBSERVER_H_
#define DIGITALOBSERVER_H_

class DigitalObserver {
 public:
  virtual ~DigitalObserver() = default;
  virtual void OnDigitalObserver(const unsigned int& pin,
                                 const bool& value) = 0;
};

#endif