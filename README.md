# ECSVisual

Un petit moteur ECS (Entity‑Component‑System) en C++ avec rendu 2D via **SFML 3.0**.

## Fonctionnalités

- Entités autonomes (Position, Velocity, Color, Size)
- Système d’input clavier adaptatif **AZERTY / QWERTY**
- Collision simple entre le joueur et les autres entités
- Architecture modulaire facilement extensible

## Prérequis

- **Windows** (Visual Studio 2022)
- **SFML 3.0**
  - Copy `SFML/include`, `SFML/lib`, `SFML/bin/*.dll`
  - Lier les `.lib` dans les propriétés du projet

## Comment compiler

1. Cloner le dépôt :
   ```bash
   git clone https://github.com/Ayaelle/ECSVisual.git
2. Ouvrir ECSVisual.sln dans Visual Studio
3. Configurer les chemins SFML (include/lib)
4. Copier les DLL dans Debug/
5. Build & Run !

## What's next ?