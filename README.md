## Simulated Audio Playback Controller
>Designed by Cameron Williams, B.S ECE spec. BME

The objective of this project was to create a simulated audio playback controller using a **Tiva C Series Microcontroller**. 

By using a peripheral button module (PMOD), the controller was able to play/pause the given audio file, restart the audio file from the beginning, skip forward a certain amount of seconds, and skip back a certain amount of seconds. 

The controller simulates an audio playback controller via a virtual terminal and allow for similar basic control similar to what can be seen in platforms
like Windows Media Player (legacy) and YouTube.

## Block Diagram
![Block Diagram](https://drive.google.com/file/d/1Czb3amkzAuwW3Lakj-6neb6yRdmsj_Za/view?usp=drive_link)

## Proof of Concept
[Proof of Concept Video](https://drive.google.com/file/d/1C5ZuwYTkT2P83YuSmVBJ3hzLGpKehiuy/view?usp=drive_link)

## Background
**General-Purpose Input/Output (GPIO)** is used for lighting an LED in response to an external push button module, as well as modifying a counter based on the status of any given push button in the module. 

In addition to GPIO, the **SysTick Timer** interrupt functionality is used to signal changes in the processor at very specific instances, allowing for micro-control, even when using peripheral devices and modules. 

This project will utilize both of these concepts, as well as the Microcontroller’s **Universal Asynchronous Receiver/Transmitter (UART)** capabilities.

The **Keil Microvision** software will be used as the (Integrated Development Environment) IDE for this project. The Tera Terminal application will be used to display the output of the “audio file”, simulating playback software. As this project utilizes both push buttons, time-based functions, and analog data transmission, the following embedded systems functions will be applied:

General-Purpose Input/Output:
In order for the peripheral push buttons to be programmed and recognized.
- The outcome of the GPIO functionality was to allow the inputs of 4 PMOD buttons to be recognized in the system. When a button is pressed, it performs a single action once, no matter the length of the press. If conflicting buttons are pressed, nothing should occur, much like other audio players.
> Cannot skip forward and backward at the same time.
>Skipping while paused is allowed.

SysTick Timers:
In order to allow for the manipulation of the simulated audio file at any instance.
- The expected outcome of the Timers functionality was to allow the Microcontroller to know the current “audio file” duration (where in the counter we currently are) and be able to manipulate it based on that information. A pause mechanic, for example, required a SysTick-centric interrupt program to support that functionality.
>Polling was not used.

Universal Asynchronous Receiver/Transmitter:
In order to allow the audio-location data to be received from the microcontroller and
displayed on the virtual terminal, UART was utilized.
- The expected outcome of the UART functionality is to allow the Microcontroller to receive the “audio file” data from the microcontroller, interpret its “position”, and display the updated data, whether it has been impacted by the PMOD or not.

The order of instruction goes from Button -> Microcontroller -> Terminal.

## Table of Components
| Component                                  | Quantity |
|--                                          |--        |
| Tiva C Series TM4C123GH6PM Microcontroller | 1x       |
| EduBase V2 Solderless Breadboard           | 1x       |
| Digilent BTN PMOD                          | 1x       |
| Male-Female Jump Cables                    | 6x       |
| USB-Micro-B to USB-A Cable                 | 1x       |

## Pinout
| Function | Brief         | BTN PMOD Pin | Tiva Pin |
|--        |--             |--            |--        |
| BTN0     | Push Button 0 | 1            | PA2      |
| BTN1     | Push Button 1 | 2            | PA3      |
| BTN2     | Push Button 2 | 3            | PA4      |
| BTN3     | Push Button 3 | 4            | PA5      |
| GND      | Ground        | 5            | GND      |
| VCC      | Power (3.3V)  | 6            | +3.3V    |

GPIO Port A was used for the PMOD BTN functionality and counter response.
GPIO Port B was used to initialize the EduBase LEDs for user visual response.

## Developer Comments
While seemingly simple to a viewer, little quirks in display functionality was the most time-consuming aspect of the project. When iterating a counter in time format, multiple edge-case scenarios were accounted for.
- When the second counter is less than 10, a zero must be added to the left of the number in order to maintain format.
	- Without it, displays: Playing - 0:1
	- WIth it, displays: Playing - 0:01
- When the counter iterates back past zero seconds, overflow occurs. Therefore, any number greater than a certain value (71 actual) needs to be manually set to zero.
- Preventing miscounting when skipping over a minute marker, or back a minute marker.

Originally, the project scope was to make an audio player + controller using an external DAC and Speaker system. The DAC I order was sourced from Shanghai, China, and was lost in international shipping.

However, a quick pivot allowed the project to function as a simulated version of the project’s objective, which proves the Tiva C Series’ capabilities to act as an audio playback controller. This form of thinking and adjustment is the
hallmark of a successful engineer within a fast-paced working environment.

## Potential Improvements

This design has room for expansion, with adding additional functionality, such as skipping the song and adding multiple tracks of different length. Adding a DAC and speaker system would allow actual audio to play from a stored file, and Bluetooth functionality would allow modular audio playback from a user’s cellular or mobile device.

These audio playback systems are used widely within consumer electronics, especially in cellular devices and music controllers, such as an iPod. By combining the extensive Tiva peripherals with external audio modules, the basics of a market-competitive music player could most certainly be created using the framework designed within this project.
