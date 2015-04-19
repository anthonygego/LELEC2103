# LELEC2103 Project (2014-2015)
This page contains some reminders about the followed guidelines.

## Specifications
#### Communication
###### PIC32 <-> PIC32

- [x] PIC32 use MIWI to send binary messages to each other.
- [x] MIWI messages have a size up to 2KB

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
- [x] Nios uses double buffering
- [x] Nios can read the values of ADXL registers
- [x] Software sprites can be copied into graphical buffers via SGDMA
- [x] Hardware sprites can display over the screen buffer

###### LT24

- [x] Nios manages the LT24 screen buffer
- [x] Nios can read the values of touch registers

#### Game management

- [x] Game is launched from the website
- [x] Level can be chosen on the website
- [x] Paddle controller can be chosen on the website
- [x] Game status can be seen on the website

#### Gameplay

- [x] LT24 can induce boni/mali to the MTL side
- [x] Paddle can be moved by touching it
- [x] Paddle can be moved thanks to accelerometer
- [x] Paddle can be resized by boni/mali
- [x] Game can be paused by touching the playing area
- [x] Fixed points for brick collision
- [x] Additional points for consecutive brick collision
- [x] Boni/mali can add/remove life
- [x] Boni/mali can speed up/down the ball

#### Levels

- [x] Levels are defined by background image and bricks map
- [x] Bricks map is defined by array of char ( * for empty, numbers for others )
- [x] Bricks need collisions to be destructed
- [x] Boni/mali can add/remove bricks

## Communication protocols
### PIC32 <-> PIC32