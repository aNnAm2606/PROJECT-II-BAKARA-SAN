# ExorQuest

## Description

ExorQuest is a 2D Turn-based RPG with strategy elements.

The world of ExorQuest is one of religion and mysticism, where demons and spirits are an objective fact. In this world, there are 4 Kingdoms: Primus Mundis, The Land of Faith; Nikoku, The Land of Tradition; Mintredje, The Land of Brotherhood; and Isiné, The Land of Creation. These four Kingdoms lived in peace, each venerating their own Gods, and fighting evil in their unique ways. One day, the arrival of a strange merchant and his powerful inventions put this peace in danger. These fateful inventions, named "Soul Relics", ended up letting the creatures of the underworld free, giving demons, spirits and ghouls complete acces to our world, and raging a war which noone was prepared for. It's up to the 4 brave exorcists to clean up this mess, and to destroy the four Demonic Kings that have taken control of the regions.

Gameplay-wise, ExorQuest isn't your standard RPG. The turn-based combat takes position into account, using a 4x2 grid. When attacking and taking defense in this grid, you'll need to take your position into account, as well as the position of your party members and enemies. Beating enemies with this combat system is so satisfying!

## Key Features

 - Positional Movement in Combat! 
 - Soul Relics - a way to spice up combat encounters with a bit of personalization.
 - Boss Relics - these powerful relics will do massive damage in combat
 - Possessed State - be careful! Some corrupted relics might give you a lot of power, but you'll lose control if you use them too often!
 
## Controls

General:
- "W A S D" for movement.
- "E" for interaction with the NPCs.
- "ESC" for the pause panel.

Inventory, character and quest:
- "Q" for opening the inventory, character and quest panel.
- "left click the mouse": select.

Win&Lose:
- "I": go to the victory panel.
- "O": close the victory panel.
- "k": go to the lose panel.
- "L": close the lose panel.

Worldmap:
- "1": go to the forest scene.
- "2": go to the town scene.
- "3": go to the dungeon scene.

Battle scene:
- "left click the mouse": select.

Debug:
-  "F1": check collisions.

## General

Game resolution: 1280x720px@60fps, support for windowed mode and fullscreen
❏ Maximum memory usage must be under 256 MB (RAM)

❏ Turn-based battle system

❏ Team logo: custom art, avoid plain text

❏ AUDIO: Sound FX characteristic for the logo

❏ AUDIO: Sound FX characteristic for the title appearing

❏ AUDIO: Music track specific for the screen

❏ UI: Main game menu (custom font): START - CONTINUE - OPTIONS - EXIT

❏ UI: AUDIO: Buttons/controls fx feedback sounds

## SCREEN: GAMEPLAY

❏ Implemented TOWN map with 3 locations to visit ( House, Shop,
Sanctuary.)

❏ Implemented 2 Playable Characters, available as the base Team Party

❏ Implemented 3 NPC Characters (town person, shopkeeper, nun)

❏ Implemented 4 Dialogs with branching with NPC characters 

❏ INPUTS: Keyboard/Gamepad inputs supported

❏ UI: PAUSE menu available on pause

❏ AUDIO: Music track specific for the screen

❏ AUDIO: Music effects fade-in/fade-out, lower volume on PAUSE

❏ Implemented 3 Types of Enemies with different stats

❏ Implemented turn-based combat system, players and enemies alternate attacks

❏ UI: Implement a minimal menu to choose the next player's actions.

## SPECIAL FEATURES

We even have each character using a priority queue. It is a list that adds elements, but if you add an element
with a priority, it will check the priority of all the other elements and put it in its place, that way each turn
the fastest characters attack first (the enemies attack automatically)and for now, the characters only have
one ability, so you can only select one.

In the battle system, we have two base abilities: melee and range, two characters for the player, and two enemies,
one being melee and another being range. The melees and ranged have a similar ability, they change a bit by 
being player or enemy. Before attacking it will show you the active character abilities
The enemies will instantly attack one after another because they are faster. If two characters are at the same speed,
they will attack in order. Then you select the melee's attack and then it will show the ranged, after the next 
turn will begin, the enemies will attack, and then its ur turn again.

## Developers

 - Jose Antonio Atencia Ordóñez: Game Designer, Q&A.
   Github Account: JedTyde
 - Fernando Freixinet Garcia: Game Designer, Coder.
   Github Account: rastabrandy02
 - Pau García Quiroga: Game Designer, Writer.
   Github Account: PaGaQi
 - Pablo Llorente del Castillo: Lead Coder.
   Github Account: Xymaru
 - Anna Metreveli: Team Leader, Lead Artist, Managment.
   Github Account: aNnAm2606
 - Miguel Tamaño Garon: UI, Artist, Coder.
   Github Account: migon25
 - Hang Xue: Music Artist, UI.
   Github Account: Patronum129

## Trailer

<iframe width="560" height="315" src="https://www.youtube.com/embed/YMVeioFv2Lo" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## License

This project is licensed under an unmodified MIT license, which is an OSI-certified license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.

{AdditionalLicenses}
