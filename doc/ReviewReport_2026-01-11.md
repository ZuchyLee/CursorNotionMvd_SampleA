# ReviewReport_2026-01-11

- 規範來源（Notion / MVD規範）：`https://www.notion.so/2e43f18e160780f7a2a5ff06887b583a`
- 審查目標：`apps/car_demo_bad/main.cpp`

---

## 審查結果（依 MVD 規範）

> ❌ **架構違規：2.1 僅限使用公開標頭檔**
> - **位置**：`apps/car_demo_bad/main.cpp:15-16`
> - **說明**：MVD 規範要求專案「僅能引用 `include/Automotive/`」的公開標頭；不得引用 `src/` 內部檔案。此處直接 `#include` 共用模組 `src/CarImpl.cpp`、`src/ElectricEngine.cpp`，屬於引用內部實作，會破壞模組邊界並造成後續升級風險。
> - **修正建議**：移除對 `src/` 的 include，改為只 include 公開介面（例如 `#include <Automotive/VehicleFactory.hpp>`），並透過 `Automotive::VehicleFactory::createVehicle(...)` 取得 `ICar`。

> ❌ **架構違規：1.2 禁止直接實例化實作類別（No Direct Instantiation）**
> - **位置**：`apps/car_demo_bad/main.cpp:20-22`
> - **說明**：MVD 規範禁止直接 `new CarImpl()` 或 `make_unique<...Impl>()`，並要求所有車輛物件必須透過 `Automotive::VehicleFactory` 建立。此處直接建立 `Automotive::ElectricEngine` 與 `Automotive::CarImpl`，違反工廠建立原則。
> - **修正建議**：改為：
>   - `auto car = Automotive::VehicleFactory::createVehicle(Automotive::VehicleFactory::CarType::Sedan_EV);`
>   - 並維持以 `std::unique_ptr` 接住回傳結果（避免裸指標長期持有）。

---

## 其他觀察（非阻擋，但可在 review 中備註）

- **符合 2.2 智慧指標管理**：本檔以 `std::unique_ptr` 管理 `ICar`（但前提應先改成透過工廠取得）。
- **符合 3.2 浮點數範圍**：`setThrottle(0.5f)` 落在 0.0~1.0 之間。

---

## 合規參考實作（最小修正版）

```cpp
#include <Automotive/VehicleFactory.hpp>
#include <iostream>

int main() {
    auto car = Automotive::VehicleFactory::createVehicle(
        Automotive::VehicleFactory::CarType::Sedan_EV
    );
    if (!car) return 1;

    car->setPower(true);
    car->setThrottle(0.5f);

    auto state = car->getState();
    std::cout << "Model=" << car->getModelName()
              << " speed=" << state.speed
              << " rpm=" << state.rpm
              << std::endl;
    return 0;
}
```

