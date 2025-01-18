# Missin Possible
Shooter game made in Unreal Engine 5. Consists of stealth elements, AI behaivour, simple inventory UI.

## Aim and Gameplay
Game starts with 2 cameras, 3 hostile enemies, 1 fuse box and a finish point. Cameras are
continuously scanning area within a slight movement range. Upon hearing player’s steps,
camera turns to noise source. After staying in its visibility cone for some time, related
camera sounds an alarm, focuses on player as long as it keeps sight and also alerts all
hostile enemies. Hostile enemies keep patrolling until getting in sight contact with player
which gets them into combat mode or hear the alarm which gets them into search mode.
They shoot as soon as they see the player and then find cover. After a brief wait, they get
into search mode which makes them check last known location. If they are unable to find
player up until that point, they go back into patrolling mode. The fuse box can be used to
disable cameras, rendering them unable to move or let enemies know about location of
player. Simply getting close is enough to trigger this behavior. Finish point is a gate like
structure. Again, getting close when finish conditions are met triggers game end. If an alarm
is ever triggered or any enemy sees the player throughout gameplay, player has to kill every
enemy character to end the game. Another option is stealth which can be achieved by
avoiding contact with any enemy characters and not sounding any alarms. Pro tip: crouching
makes no noise, which is inspired by Counter Strike mechanics.

## Controls
Switch between weapons by pressing 1 or 2, you can also unequip by pressing already
equipped weapon’s key. If low on health, press 4 to use medkit and restore to full health. Left
Ctrl to crouch, Left Shift while moving to sprint. Medkit count,health and weapon ammos are
displayed in the UI, which is designed to work properly on standalone borderless fullscreen
mode so playing in editor would make it look a bit messy.

## Development Process
After reviewing requirements, project is divided into modules which are the following:
* Animations
* Weapon System
* AI Behaviors
* UI
* Map design, sounds and polishing

These tasks are developed separately, keeping everything in mind for proper integration.
Design patterns used and their reasoning are the following:
● Observer, in order to manage interaction between related actors by asynchronous
events, such as cameras broadcasting players location to enemy characters.
● Singleton, to manage game end and death conditions, made use of being able to
access gamemode and gamestate classes from anywhere.
● Component, things like weapon, health and intractability which are used in multiple
classes but serving same purpose with editable differences are implemented by
using this approach.
● Finite State Machine, used to manage transition between animations and in
behavior tree states.

Biggest challenge I faced is managing the behavior trees of AI actors. Camera was a bit
easier than enemy characters since they had only 2 states in my design, scan mode and
focus mode. I started character behavior tree by checking 2 booleans but it got messy
quickly. The solution was dividing their behavior to discrete states; patrol, combat, cover and
search. That way, it was easier to transition between them, also without assuming expected
behavior. Another challenge was the weapon system. Both player and enemies have the
capability but I preferred AI to be less flexible. For that reason, I decided to have a weapon
manager component which both actors would have, then edit their properties depending on
my needs.
