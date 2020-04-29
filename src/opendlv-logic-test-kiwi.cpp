#include "cluon-complete.hpp"
#include "opendlv-standard-message-set.hpp"
#include "logic.hpp"

int32_t main(int32_t argc, char **argv) {
  int32_t retCode{0};
  auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);
  if (0 == commandlineArguments.count("cid") || 0 == commandlineArguments.count("freq")) {
    std::cerr << argv[0] << " tests the Kiwi platform by sending actuation commands and reacting to sensor input." << std::endl;
    std::cerr << "Usage:   " << argv[0] << " --freq=<Integration frequency> --cid=<OpenDaVINCI session> [--verbose]" << std::endl;
    std::cerr << "Example: " << argv[0] << " --freq=10 --cid=111" << std::endl;
    retCode = 1;
  } else {
    bool const VERBOSE{commandlineArguments.count("verbose") != 0};
    uint16_t const CID = std::stoi(commandlineArguments["cid"]);
    float const FREQ = std::stof(commandlineArguments["freq"]);

    Behavior behavior;
    cluon::OD4Session od4{CID};

    auto atFrequency{[&VERBOSE, &logic, &od4]() -> bool
      {
        logic.step();
        auto leftWheelSpeedRequest = logic.getLeftWheelSpeedRequest();
        auto rightWheelSpeedRequest = logic.getRightWheelSpeedRequest();

        cluon::data::TimeStamp sampleTime = cluon::time::now();
        od4.send(leftWheelSpeedRequest, sampleTime, 0);
        od4.send(rightWheelSpeedRequest, sampleTime, 0);
        if (VERBOSE) {
          std::cout << "Left wheel speed is " << leftWheelSpeedRequest.speed()
            << " and right wheel speed is " << rightWheelSpeedRequest.speed() << std::endl;
        }

        return true;
      }};

    od4.timeTrigger(FREQ, atFrequency);
  }
  return retCode;
}
