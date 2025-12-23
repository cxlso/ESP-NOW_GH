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
