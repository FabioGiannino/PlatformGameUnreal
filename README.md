# PlatformGameUnreal
 A platform game for Aiv Exam

Features:
- custom movement component:
 -  add Jump action and linetrace to track the ground
 -  change Input mode with enhanced input class and data input context of default third person character
- Player Ability: shoot
 - When E is pressed, a raycast will spawn from player across his forward. If the raycas hits agains something, there will be two case:
    - if the hitted object implements IHittable Interface (blues objects), then it will get a hit and changes his material. If it is hit again, it will deactivate.
    - if the hitted object doesn't implement IHittable Interface, then it will get an impulse.
- Coin:
  - A collectable item that can only pick up from all the actors with tag "Player"
  - When a Coin is collected, a counter in Player controller will incremented and a Broadcast delegate will be called (and the HUD will show the number of collected coin)
- Save/Load:
  - Save and Load are triggered by pressing the K and L buttons.
  - Their logic are defined in file CustomGameInstance.cpp
  - all the interactable objects in game (coin, hittable or movable objects) can be savable by an interface ISavable
- Elevator:
  - An elevator can be triggered when player puts something on the orange square
    
The only Blueprint I used is to create and show the HUD widget and binding the collect coin event to HUD.
