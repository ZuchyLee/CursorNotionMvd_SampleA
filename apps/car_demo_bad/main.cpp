// 這支程式「刻意」用來觸發 AutomotiveModule_Review_Guidelines.md 的違規檢核點：
// - 違規(2.1)：引用 external/CommonModule 的 src/ 內部檔案（禁止 include src/）
// - 違規(1.2)：直接實例化實作類別（禁止 new/make_unique CarImpl/ElectricEngine）
//
// 目的：讓你可以用 Cursor + Notion 展示 code review 流程。

#include <Automotive/ICar.hpp>
#include <Automotive/IEngine.hpp>

#include <iostream>
#include <memory>
#include <utility>

// ❌ 違規(2.1)：直接 include 共用模組內部實作（src/）
#include "../../external/CursorNotionMvd_CommonModule/src/CarImpl.cpp"
#include "../../external/CursorNotionMvd_CommonModule/src/ElectricEngine.cpp"

int main() {
    // ❌ 違規(1.2)：禁止直接實例化實作類別，必須透過 VehicleFactory
    auto engine = std::make_unique<Automotive::ElectricEngine>();
    std::unique_ptr<Automotive::ICar> car =
        std::make_unique<Automotive::CarImpl>("BadCar - DirectImpl", std::move(engine));

    car->setPower(true);
    car->setThrottle(0.5f);

    auto state = car->getState();
    std::cout << "[CarDemo_Bad] Model=" << car->getModelName()
              << " speed=" << state.speed
              << " rpm=" << state.rpm
              << std::endl;
    return 0;
}

