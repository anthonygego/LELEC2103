# LELEC2103 Project (2014-2015)
This page contains some reminders about the followed guidelines.

## Progression
### LT24 side
- [x] Basic LT24 Qsys project
- [x] Basic software to launch
- [ ] PIC32 communication

### MTL side
- [ ] Basic MTL Qsys project
- [ ] Basic software to launch
- [ ] PIC32 communication

### PIC32s side
- [x] Basic PIC32 software
- [ ] Final MyMIWI transmission protocol
- [ ] New SPI for improved communication with Nios II

## Application-layer protocol
### Basic communication format
JSON (BSON ?) messages of three possibles types depending on the action to be taken by the receiver :

- requests : Data is requested from the receiver by the sender
- answers : Data is given replied back in response to a request
- advertisements : Data is given for information, to update status or else...

### List of possible requests
### List of possible advertisements