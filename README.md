# 🎲 Monte Carlo Monopoly Strategy Engine

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
![Simulation](https://img.shields.io/badge/Simulation-Monte%20Carlo-blueviolet)

> A high-performance C++ backend designed to simulate millions of Monopoly games to derive optimal strategic metrics, ROI curves, and landing probabilities.

<p align="center">
  <img src="Public/Monopoly_game_logo.svg.png" alt="Monopoly Logo" width="400"/>
</p>

## 🚀 Overview

**Monte Carlo Monopoly** is more than just a game simulation; it's a strategic analysis tool. By utilizing Monte Carlo methods, the engine executes thousands of iterations to model the complex economics of Monopoly. It provides the data necessary to drive a real-time analytics dashboard, helping players understand which properties offer the best yield under varying risk tolerances.

### Key Features

*   **Monte Carlo Simulation Engine**: Run thousands of games in seconds to capture statistical significance.
*   **Lead Strategist (AGENT_01)**: A sophisticated AI agent with a parameterized risk tolerance (`alpha`).
*   **Dynamic ROI Analytics**: Calculates Realized Return on Investment for every property group.
*   **Board Heatmapping**: Statistical landing probabilities across all 40 squares.
*   **JSON API Output**: Structured payload designed for direct integration with React-based frontend dashboards.
*   **Rule Customization**: Toggle specialized rules like Free Parking Windfalls, Rapid Auctions, and Mortgage Leverage.

## 🛠️ Performance & Strategy

The engine utilizes a specialized **Decision Tree logic** for agents. The `alpha` parameter (0.0 to 1.0) dictates an agent's risk appetite:
- **Low Alpha (Conservative)**: Maintains higher cash reserves, avoids aggressive property builds.
- **High Alpha (Aggressive)**: Reinvests liquidity immediately into houses/hotels to maximize rent yields.

## 💻 CLI Documentation

The executable supports a variety of flags to customize the simulation environment:

| Flag | Description | Default |
| :--- | :--- | :--- |
| `--sims <int>` | Number of game iterations to run | `1` |
| `--agents <int>` | Number of AI agents (2-8) | `4` |
| `--liquidity <int>`| Starting cash for all agents | `1500` |
| `--alpha <float>` | Risk tolerance for AGENT_01 (0.0 to 1.0) | `0.5` |
| `--json` | Enable structured JSON output mode | `false` |
| `--free-parking-windfall` | Enables cash collection on Free Parking | `false` |
| `--stochastic-rent` | Adds variance to rent payments | `false` |

## 📦 Building & Execution

### Prerequisites
- **CMake** (3.15+)
- **C++17 Compiler** (GCC, Clang, or MSVC)

### Instructions
1. **Clone the repository**:
   ```bash
   git clone https://github.com/godking123/Monte-Carlo-Monopoly.git
   ```
2. **Build the project**:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build . --config Release
   ```
3. **Run the Simulation**:
   ```bash
   ./MonteCarlo-Monopoly --sims 1000 --json --alpha 0.8
   ```

## 📊 JSON API Structure

When running with the `--json` flag, the engine emits a payload containing:
- `boardHeatmap`: Frequency of landings for all 40 positions.
- `propertyEfficiency`: Real-time ROI and landing probability per property.
- `strategyEngine`: Winning probabilities, ROI curves (Aggressive vs. Conservative), and optimal property weightings.
- `propertyMatrix`: High-fidelity data for the dashboard (Live logs, agent net worth, and property ownership).

---
*Developed for advanced game theory analysis and statistical modeling.*