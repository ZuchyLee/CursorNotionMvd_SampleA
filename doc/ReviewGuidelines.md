# ReviewGuidelines（MVD規範快照）

- 產出日期：2026-01-11
- 規範來源（Notion）：`https://www.notion.so/2e43f18e160780f7a2a5ff06887b583a`

---

## Automotive Core Module - AI Code Review 規範指南（摘錄/同步）

本文件旨在提供給 AI 審查員（Code Reviewer）作為標準，用於檢核「使用 `LibAutomotive` 共用模組」的專案代碼是否符合架構規範。

## 1. 核心禁令 (Strict Prohibitions)

### 1.1 禁止改動共用模組 (Module Integrity)

- **規則**：禁止修改 `CommonModule/include/` 或 `CommonModule/src/` 下的任何檔案。
- **檢核點**：如果專案 PR (Pull Request) 中包含對共用模組路徑檔案的更動，應立即標記為「不通過」。
- **例外**：除非該 PR 的目的明確是「升級或修正共用模組本身」。

### 1.2 禁止直接實例化實作類別 (No Direct Instantiation)

- **規則**：開發者禁止直接使用 `new CarImpl()` 或 `std::make_unique<ElectricCarImpl>()`。
- **檢核點**：搜尋代碼中是否出現具體的實現類別名稱。所有車輛物件必須透過 `Automotive::VehicleFactory` 建立。

---

## 2. 介面使用規範 (Interface Usage)

### 2.1 僅限使用公開標頭檔

- **規則**：專案僅能引用 `include/Automotive/` 目錄下的標頭檔。
- **檢核點**：檢查 `#include` 路徑。若引用了 `src/` 內部的私人標頭檔，應要求修正。

### 2.2 智慧指標管理

- **規則**：所有從工廠獲取的 `ICar` 物件必須由智慧指標（如 `std::unique_ptr` 或 `std::shared_ptr`）管理。
- **檢核點**：檢查是否有手動 `delete` 或是將智慧指標轉換為裸指標（Raw Pointer）並長期持有。

---

## 3. 程式碼風格與安全 (Code Style & Safety)

### 3.1 狀態檢查

- **規則**：在對車輛進行操作（如 `setThrottle`）前，應檢查電源狀態或物件是否有效。
- **檢核點**：檢查調用 `ICar` 方法前是否有適當的空指標檢查。

### 3.2 浮點數範圍

- **規則**：傳入介面的參數必須符合 `AutomotiveModule_Design.md` 定義的範圍。
  - `setThrottle(position)`: 0.0 ~ 1.0
  - `setBrake(force)`: 0.0 ~ 1.0
  - `setSteering(angle)`: -1.0 ~ 1.0
- **檢核點**：檢查硬編碼的數值或變數邏輯是否可能超出此範圍。

---

## 4. 擴展性規範 (Extensibility)

### 4.1 增加新車型

- **規則**：若需支援新車型，應修改 `VehicleFactory` 的枚舉並在模組內部實作，而非在外部專案中自行實作 `ICar` 介面（除非該專案是作為插件開發）。
- **檢核點**：檢查是否有專案私自繼承 `ICar` 卻未回饋至共用模組。

---

## 5. AI Review 回覆模板

當 AI 發現違規時，請使用以下格式回覆：

> ❌ **架構違規：[規則名稱]**
> - **位置**：`file_path:line_number`
> - **說明**：[具體說明違反了哪一項規範]
> - **修正建議**：[給出正確的代碼範例]

