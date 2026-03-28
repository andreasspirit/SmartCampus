# 🌍🏫 Smart Campus (CO2402) — Command-Line Proof of Concept

## ✨ Overview
This project is a command-line proof-of-concept system for a **Smart Campus Network**.  
It models multiple smart devices (e.g., cameras, lighting, air conditioning) that can be controlled through a **menu-driven CLI**.

The system is designed to be **scalable & maintainable** using:
- ✅ Object-Oriented Programming (inheritance, encapsulation, polymorphism)
- ✅ Smart pointers (`unique_ptr`) to help prevent memory leaks
- ✅ Recognised design patterns (Strategy/Polymorphism, Composite-style Rooms, Prototype cloning)

---

## 🧰 Features

### ✅ Must Have (Implemented)
- 🖥️ Command-line interface (menu system)
- 🧩 Device types implemented as classes:
  - 📷 SecurityCamera
  - ❄️ AirConditioning
  - 📽️ Projector
  - 💡 RoomLighting
  - 🔒 DoorLock
- Each device includes:
  - 🆔 Unique ID
  - 🏷️ Device name
  - 🏭 Manufacturer
  - ⚡ `status` (active/inactive, default inactive)
  - 🔛 `Activate()` / 🔻 `Deactivate()`
  - ℹ️ `ViewInfo()` (full device details)
  - 🧑‍💻 `Interaction_Event()` (device-specific interaction)
- Menu options to call methods across devices (bulk operations)

### ✅ Should Have (Implemented)
- 📋 View list of devices
- ➕ Add new device via CLI
- ✏️ Edit device attributes (polymorphic `EditAttributes()`)
- 🗑️ Delete devices via CLI
- 📡 Connection simulation:
  - `CheckConnection()` returns connection state
  - `SetConnection(bool)` toggles state
  - Menu shows connected ✅ / disconnected ❌ device lists

### ✅ Could Have (Implemented)
- 🔎 Search device by ID and perform actions on it
- 🏠 Rooms (grouping devices and controlling devices by room)
- 🧬 Duplicate room:
  - Duplicates a room and all devices inside it
  - New devices get a **new unique ID**
  - Device names append `"_copy"`

---

## 🧠 Design Patterns Used

### 🎯 Strategy (via Polymorphism)
- `Device` defines a common interface using virtual methods.
- Each derived device class implements its own behavior for:
  - `Interaction_Event()`
  - `ViewInfo()`
  - `EditAttributes()`
- The manager calls these methods through base pointers (`Device*` / `unique_ptr<Device>`) without knowing the concrete type.

✅ **Benefit:** Adding a new device type doesn’t require rewriting manager logic.

### 🧩 Composite-style Grouping (Rooms)
- Rooms group devices so actions can apply to a whole room (e.g., activate all devices in one room).

✅ **Benefit:** Supports hierarchical organisation and bulk control.

### 🧬 Prototype (Cloning for Room Duplication)
- `Device::Clone(newID, newName)` allows devices to duplicate themselves polymorphically.
- Room duplication uses `Clone` so the manager doesn’t need long `if/else` chains.

✅ **Benefit:** Duplication stays scalable as more device types are added.

---

## 📄 File Loading (Initialisation)
- Devices are being initialised from a file
### 📌 File name
`smartcampus.txt`

---

## 🧹 Memory Management
- Devices are stored using unique_ptr<Device> ✅ (no memory leaks)
- Rooms store non-owning pointers (Device*) referencing devices owned by the manager
- When deleting a device, it is removed from rooms first to avoid dangling pointers 🧯

---

## 👤 Author

- Name: [Andreas Pnevmatikas]
- Module: CO2402
- Project: Smart Campus Command-Line System 🏫✅
