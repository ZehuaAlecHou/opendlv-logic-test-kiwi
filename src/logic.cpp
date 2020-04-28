/* opendlv-logic-test-kiwi
 * behavior.cpp
 * Zehua Hou
 */
 
#include "behavior.hpp"

Behavior::Behavior() noexcept:
  m_leftWheelSpeedRequest{},
  m_rightWheelSpeedRequest{},
  m_leftWheelSpeedRequestMutex{},
  m_rightWheelSpeedRequestMutex{},
  m_currentTimeUsMutex{},
{
}

opendlv::proxy::LeftWheelSpeedRequest Behavior::getLeftWheelSpeedRequest() noexcept
{
  std::lock_guard<std::mutex> lock(m_leftWheelSpeedRequestMutex);
  return m_leftWheelSpeedRequest;
}
opendlv::proxy::RightWheelSpeedRequest Behavior::getRightWheelSpeedRequest() noexcept
{
  std::lock_guard<std::mutex> lock(m_rightWheelSpeedRequestMutex);
  return m_rightWheelSpeedRequest;
}

void Behavior::step() noexcept
{
  cluon::data::TimeStamp currentTime = cluon::time::now();
  int64_t currentTimeUs = cluon::time::toMicroseconds(currentTime);
  float leftWheelSpeed = 0.0f;
  float rightWheelSpeed = 0.0f;
  float t1 = 3.0f;
  float t2 = 10.0f;
  float v0 = 0.5f;
  
  if (currentTimeUs <= t1) {
    rightWheelSpeed = v0*currentTimeUs/t1;
  } else {
    if (currentTimeUs <= t2) {
    leftWheelSpeed = v0*(currentTimeUs-t1)/t2;
    rightWheelSpeed = v0;
    }
  }
  
  std::lock_guard<std::mutex> lock1(m_leftWheelSpeedRequestMutex);
  std::lock_guard<std::mutex> lock2(m_rightWheelSpeedRequestMutex);
  
  opendlv::proxy::LeftWheelSpeedRequest LeftWheelSpeedRequest;
  leftWheelSpeedRequest.speed(leftWheelSpeed);
  m_leftWheelSpeedRequest = leftWheelSpeedRequest;
  
  opendlv::proxy::RightWheelSpeedRequest RightWheelSpeedRequest;
  rightWheelSpeedRequest.speed(rightWheelSpeed);
  m_rightWheelSpeedRequest = rightWheelSpeedRequest;
 }
}
