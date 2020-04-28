/*
 * opendlv-logic-test-kiwi
 * logic.hpp
 * Zehua Hou
 */

#ifndef BEHAVIOR
#define BEHAVIOR

#include <mutex>

#include "opendlv-standard-message-set.hpp"

class Behavior {
 private:
  Behavior(Behavior const &) = delete;
  Behavior(Behavior &&) = delete;
  Behavior &operator=(Behavior const &) = delete;
  Behavior &operator=(Behavior &&) = delete;

 public:
  Behavior() noexcept;
  ~Behavior() = default;

 public:
  opendlv::proxy::LeftWheelSpeedRequest getLeftWheelSpeedRequest() noexcept;
  opendlv::proxy::RightWheelSpeedRequest getRightWheelSpeedRequest() noexcept;
  void step() noexcept;
  
 private:
   opendlv::proxy::LeftWheelSpeedRequest m_leftWheelSpeedRequest;
   opendlv::proxy::RightWheelSpeedRequest m_rightWheelSpeedRequest;
   std::mutex m_leftWheelSpeedRequestMutex;
   std::mutex m_rightWheelSpeedRequestMutex;
};

#endif
