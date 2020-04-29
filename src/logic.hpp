/*
 * opendlv-logic-test-kiwi
 * logic.hpp
 * Zehua Hou
 */

#ifndef LOGIC
#define LOGIC

#include <mutex>

#include "opendlv-standard-message-set.hpp"

class Logic {
 private:
  Logic(Logic const &) = delete;
  Logic(Logic &&) = delete;
  Logic &operator=(Logic const &) = delete;
  Logic &operator=(Logic &&) = delete;

 public:
  Logic() noexcept;
  ~Logic() = default;

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
