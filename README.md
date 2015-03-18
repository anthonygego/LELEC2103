# LELEC2103 Project (2014-2015)
This page contains some reminders about the followed guidelines.

## Specifications
#### Communication
###### PIC32 <-> PIC32

- [x] PIC32 use MIWI to send binary messages to each other.
- [x] MIWI messages have a size up to 2KB
- [ ] MIWI connection status can be asked when running

###### Nios <-> PIC32

- [x] Nios/PIC32 can send binary messages of any size (within limits) to PIC32/Nios
- [x] Nios/PIC32 can send RPC messages to PIC32/Nios
- [x] PIC32 redirects RPC messages to RPC handler routines
- [x] When MIWI RPC is sent to PIC32, it redirects the contained message to other PIC32
- [x] When File RPC is sent to PIC32

###### Nios <-> Nios

- [x] Nios can send RPC message to other Nios
- [x] RPC messages are received in background

#### Screen, touch and accelerometer
###### MTL

- [x] Nios manages the Frame Reader buffer
- [x] Nios can read the values of multi-touch registers
- [ ] Nios uses double buffering
- [ ] Blitter unit can memcopy sprites by applying bitwise operations
- [ ] Hardware sprites can display over the screen buffer

###### LT24

- [x] Nios manages the LT24 screen buffer
- [x] Nios can read the values of touch registers

###### ADXL345

- [x] Nios can read the values of ADXL registers

#### Game management

- [ ] Game is launched from the website
- [ ] Level can be chosen on the website

#### Gameplay

- [ ] LT24 can induce boni/mali to the MTL side
- [ ] Paddle can be moved by touching it
- [ ] Paddle can be moved thanks to accelerometer
- [ ] Paddle can be resized by boni/mali
- [ ] Game can be paused by touching the playing area
- [ ] Fixed points for brick collision
- [ ] Additional points for consecutive brick collision

#### Levels

- [ ] Levels are defined by background image and bricks map
- [ ] Bricks map is defined by array of char ( * for empty, numbers for others )
- [ ] Bricks need i collisions to be destructed
- [ ] Highscore can be stored
- [ ] Boni/mali can add/remove bricks

## Communication protocols
### PIC32 <-> PIC32