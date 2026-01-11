#include <Automotive/VehicleFactory.hpp>

#include <iostream>

int main() {
    auto car = Automotive::VehicleFactory::createVehicle(
        Automotive::VehicleFactory::CarType::Sedan_EV
    );

    if (!car) {
        std::cerr << "[CarDemo_Good] Failed to create vehicle." << std::endl;
        return 1;
    }

    car->setPower(true);

    // 介面參數範圍（合規）：Throttle/Brake 0.0~1.0，Steering -1.0~1.0
    car->setThrottle(0.6f);
    car->setSteering(-0.2f);

    auto state = car->getState();
    std::cout << "[CarDemo_Good] Model=" << car->getModelName()
              << " speed=" << state.speed
              << " rpm=" << state.rpm
              << std::endl;

    car->setBrake(1.0f);
    car->setPower(false);
    return 0;
}

