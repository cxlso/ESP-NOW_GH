# ESP-NOW_GH
###### A real-time Grasshopper ↔ ESP32 communication workflow using ESP-NOW. Enables simultaneous read/write control of ESP32 swarms with near-zero latency, providing a scalable, Firefly-free alternative for building fully integrated computational design and interactive systems.


## Overview

This project presents a real-time communication workflow between **Grasshopper ↔ ESP32(Master) ↔ ESP32(Slaves)** using the **ESP-NOW** protocol. By streaming data directly into the Grasshopper interface, the workflow allows complete computational pipelines to be constructed around **sensing, actuation, multi-agent coordination, and distributed intelligence**.

With **Firefly deprecated** and constrained by serial-based communication, this approach leverages ESP-NOW to overcome limitations related to latency, scalability, and system architecture. It supports **swarm-based control**, real-time feedback loops, and peer-to-peer communication without relying on traditional Wi-Fi networking or point-to-point serial connections.

### Prerequisite

The Grasshopper integration is **based on the plugin [SuperSerial](https://www.food4rhino.com/en/app/superserial)** by **Fabio D'Agnano**, which is used here as a flexible serial bridge between Grasshopper and the Master ESP32.

Further documentation on SuperSerial is available [here](https://www.masterad.it/superserial-grasshopper-plugin/).

### Features

* Near-zero latency communication
* Simultaneous read/write to multiple ESP32s
* Scalable swarm architecture
* Real-time data streaming in Grasshopper
* ESP-NOW based (no router required)
* Suitable for interactive systems and cyber-physical workflows

## Signal Flow

![SignalFlow](Pictures/SignalFlow.jpg)

## ESP32 Firmware

### Transmitter Node (Master)

### Receiver Nodes (Slave)

### Note on ESP32-C3 / C6 / S2 / S3

The ESP32-C3 (and similarly C6, S2, and S3) differs from many Arduino boards in that **USB serial output is disabled by default**. The Arduino IDE must be explicitly configured to expose the **USB CDC serial port at boot**. Documented [here](https://docs.espressif.com/projects/arduino-esp32/en/latest/tutorials/cdc_dfu_flash.html#usb-cdc)

In the Arduino IDE:

- **Tools → USB CDC On Boot → `Enabled`**

You should now see the serial output from the board as expected.

In this project, the **Receiver node (Master)** acts as a gateway between ESP32 transmitter nodes (Slaves) and Grasshopper, so it **must have USB CDC enabled** to ensure Serial communication.

For **Transmitter nodes**, this setting is only required during development and debugging, as they do not rely on Serial monitoring once deployed and communicate exclusively via ESP-NOW.

**Recommendation:** However, leaving **USB CDC on Boot enabled** simplifies debugging across all nodes.

## Repository Structure

```
espnow-grasshopper-swarm/
├── grasshopper/      # Grasshopper definitions and examples
├── firmware/         # ESP32 firmware (nodes + gateway)
├── docs/             # Protocol and workflow documentation
├── examples/         # Example projects and use cases
└── media/            # Diagrams, screenshots, videos
```

## Applications

* Swarm robotics
* Interactive installations
* Distributed sensing and actuation
* Cyber-physical fabrication
* Architectural intelligence systems

## Contributing

Contributions and suggestions are welcome.
Please submit a pull request or open an issue to discuss improvements.

## License

[![CC BY-NC-SA 4.0][cc-by-nc-sa-shield]][cc-by-nc-sa]

This work is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License][cc-by-nc-sa].

[![CC BY-NC-SA 4.0][cc-by-nc-sa-image]][cc-by-nc-sa]

## Acknowledgements

Special thanks to [Luigi Pacheco](https://luigipacheco.com/), director of the
[Interactive Machines Lab](https://www.instagram.com/imachineslab) at the
[School of Architecture of Florida Atlantic University](https://www.fau.edu/artsandletters/architecture/)
for lending me his RealSense Camera.


<!-- Shields and link definitions -->

[cc-by-nc-sa]: http://creativecommons.org/licenses/by-nc-sa/4.0/
[cc-by-nc-sa-image]: https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png
[cc-by-nc-sa-shield]: https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg
