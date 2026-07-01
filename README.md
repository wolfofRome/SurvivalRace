# 🏃 Race For Survival

> A fast-paced 2-player online survival minigame built with **Unreal Engine 5** — outlast your opponent while the world tries to kill you both.

---

## 📖 About

**Race For Survival** is a competitive multiplayer minigame where two players fight not against each other directly, but against time and a constantly increasing difficulty. Your health drains continuously — collect **Med Kits** to stay alive, rack up **points**, and survive longer than your opponent.

The game uses **Epic Online Services (EOS)** for matchmaking and session management, and **Gameplay Ability System (GAS)** for all attribute and effect logic.

---

## 🎮 Gameplay

- **2 players** connect via EOS matchmaking
- Your **health drains** passively at an increasing rate over time
- **Med Kits** spawn randomly around the map — grab them to heal
- **Jump Pads** are scattered across the arena for traversal
- **Points accumulate** the longer you survive
- The player who **outlasts** the other (or has more points when both die) wins
- Results are saved to a **local leaderboard** (top 10)

---

## ⚙️ Technical Stack

| System             | Technology                          |
| ------------------ | ----------------------------------- |
| Engine             | Unreal Engine 5                     |
| Language           | C++                                 |
| Networking         | EOS (Epic Online Services)          |
| Multiplayer Plugin | Custom `MultiplayerSessions` plugin |
| Ability System     | Gameplay Ability System (GAS)       |
| UI                 | UMG (Unreal Motion Graphics)        |
| Effects            | Niagara                             |
| Input              | Enhanced Input System               |
| Save System        | `USaveGame` (local persistence)     |

---

## 🏗️ Project Structure

```
Source/RaceForSurvival/
├── Character/          # Player character class
├── Player/             # PlayerState & PlayerController (GAS integration)
├── GAS/                # Attribute Set, ASC, Gameplay Effect Calculations
│   ├── RFSAttributeSetBase         # Health, MaxHealth, Points, DamageRate, TimeElapsed
│   ├── RFSAbilitySystemComponent   # Custom ASC
│   └── RFSIncreaseDifficultyExecCalculation  # Scales damage rate over time
├── Actors/             # In-world interactables
│   ├── RFSMedKit       # Collectible — applies heal GE on overlap
│   ├── RFSJumpPad      # Launch pad — applies impulse on overlap (server-authoritative)
│   ├── RFSSpawnManager # Handles timed random spawning of objects
│   └── RFSBaseActor    # Base class for all world actors
├── Game/               # Core game framework
│   ├── RaceForSurvivalGameMode
│   ├── RFSGameInstance     # Persistent ranking storage
│   └── RFSSaveGame         # Serialization for leaderboard
├── UI/                 # UMG widget C++ classes
│   ├── RFSHUDWidget        # In-game HUD (health, points, time)
│   ├── RFSMainMenuWidget   # Main menu + EOS login/session flow
│   ├── RFSRankingWidget    # Leaderboard screen
│   └── RFSRankingPlaceWidget  # Single leaderboard entry
└── Interfaces/
    └── RFSDespawnableInterface  # Interface for actors that notify on despawn

Plugins/MultiplayerSessions/    # Custom EOS session management plugin
├── MultiplayerSessionsSubsystem  # Create/Find/Join/Destroy sessions + EOS login
└── Menu                          # Session browser UI
```

---

## 🔌 GAS Attributes

All player state is driven through GAS attributes replicated via `RFSAttributeSetBase`:

| Attribute            | Description                              |
| -------------------- | ---------------------------------------- |
| `Health`             | Current player health                    |
| `MaxHealth`          | Maximum health cap                       |
| `HealthDamageRate`   | Passive drain rate (increases over time) |
| `Points`             | Score accumulated over time              |
| `PointsIncreaseRate` | Rate at which points accumulate          |
| `TimeElapsed`        | Total survival time                      |

Difficulty scales automatically via `RFSIncreaseDifficultyExecCalculation` — a custom `GameplayEffectExecutionCalculation` that raises `HealthDamageRate` as `TimeElapsed` grows.

---

## 🌐 Multiplayer & EOS Setup

The project uses a custom **MultiplayerSessions** plugin that wraps EOS Online Subsystem functionality:

- `Login()` — authenticates via EOS DevAuth or Exchange Code
- `CreateSession()` — hosts a 2-player session
- `FindSessions()` — searches for available sessions
- `JoinSession()` — connects to a found session
- `DestroySession()` / `StartSession()` — lifecycle management

To run with EOS, you need to configure your credentials in `DefaultEngine.ini` under `[OnlineSubsystemEOS]`.

---

## 🏆 Leaderboard

The top 10 scores are saved **locally** using Unreal's `USaveGame` system. Each entry stores:

- Player name
- Points scored
- Unique player GUID

Rankings are sorted by points (descending) and persist between sessions.

---

## 🚀 Getting Started

### Prerequisites

- Unreal Engine 5.1+
- Visual Studio 2022 (Windows) or Xcode (Mac)
- Epic Games account (for EOS DevAuth credentials)

### Build

1. Clone the repository
2. Right-click `RaceForSurvival.uproject` → _Generate Visual Studio project files_
3. Open the `.sln` and build in `Development Editor` configuration
4. Open the project in Unreal Editor

### EOS Configuration

In `Config/DefaultEngine.ini`, fill in your EOS credentials:

```ini
[OnlineSubsystemEOS]
bEnabled=true
ProductId=YOUR_PRODUCT_ID
SandboxId=YOUR_SANDBOX_ID
DeploymentId=YOUR_DEPLOYMENT_ID
ClientCredentialsId=YOUR_CLIENT_ID
ClientCredentialsSecret=YOUR_CLIENT_SECRET
```

---

## 📝 Notes

This was built as a **learning project** exploring:

- EOS integration in Unreal Engine 5
- Gameplay Ability System for networked attribute management
- Server-authoritative multiplayer mechanics
- Custom plugin architecture for session management

---

## 📄 License

This project is for educational and portfolio purposes.
