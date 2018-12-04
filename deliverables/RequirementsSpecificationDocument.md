Requirements Specification Document
======
## LMU SAE Aero Team, 2019<br>Telemetry and Control System<br>Anthony Keba

<br><br><br>

Table of Contents
------
###  1 . . . [Scope](#1-scope)
###### 1.1 . . [Identification](#11-identification)
###### 1.2 . . [System Overview](#12-system-overview)
###  2 . . . [Relavent and Applicable Documents](#2-applicable-documents)
###### 2.1 . . [SAE Rules and Regulations](#21-sae-rules-and-regulations)
###  3 . . . [Subsystems Breakdown](#3-subsystems-breakdown)
###  4 . . . [Requirements by Subsystem](#4-system-requirements)
###### 4.1 . . [CDA Requirements](#41-cda-subsystem-requirements)


<br><br><br>

# §1 Scope
## §1.1 Identification
This Software Requirements Specification (SRS) Documents the requirements for the The LMU SAE Aero Team 2019 Telemetry and Control System, called the Telemetry and Control System (TCS). The document will provide an overview for all required technical and functional requirements for the TCS, along with links to any auxiliary sources for hardware specifications.
<br>
## §1.2 System Overview
The Telemetry and Control System is a multi-platform set of software suites that collectively fulfill the requirements of the [RULES DOCUMENT][SAERulesAndRegulationsDocument]. These programs, in conjunction, will provide the team with telemetry data, fly sub-crafts, and provide wireless communications with the pit crew. The suite has been broken down into several parts, as follows:
### §1.2.1 Primary Aircraft (PA)
The Primary Aircraft (PA) is a manually and remotely-controlled aircraft that will be responsible for communicating wirelessly with the pit crew in order to relay telemetry data. Additionally, the primary aircraft will feature an off-the-shelf RC airplane control loop, that will feature no additional software, in correspondence with section 8.10 of the [RULES DOCUMENT][SAERulesAndRegulationsDocument], which prohibits autonomous flight of the PA.

The requirements for the PA software suite, known as the "Digital Acquisition System" (DAS) are as follows:
* The DAS will continually read the craft's altitude
* The DAS will wirelessly transmit the altitude of the craft to the pit crew
* The DAS will NOT use the same 2.4GHz channel as the PA's control systems
* The DAS will also record the current state of all payloads, in the form of 'primed', and 'released'
* The DAS will be capable of time syncing payload drops and altitude.


### §1.2.2 Colonist Delivery Aircraft (CDA)
The Colonist Deliver Aircraft (CDA) is an autonomously controlled aircraft that is responsible for delivering the 'colonists' (ping-pong balls) from the PA to the landing site (as outlined in section 8.6 of the [RULES DOCUMENT][SAERulesAndRegulationsDocument]). The requirements for this craft's software are as follows:
* The CDA will deliver all colonists to the landing zone
* The CDA will operate autonomously at all times, unless in Manual Override (described below)
* The CDA will have an alternate mode of operation to be used in case of emergencies, known as "Manual Override"
* While in Manual Override, the CDA will pitch fully up immediately

<br><br><br>

# §2 Applicable Documents
Section 2 contains overviews of all included documents, and their application for this project.
## §2.1 SAE Rules and Regulations
  Sections 8.10-8.16 directly pertain to the requirements of the TCS. Section 8 as a whole pertains to the Advanced Division.
<br>
# §3 Subsystems Breakdown
## §3.1 CDA Controls Software:
The CDA Controls Software (CDACS) will feature the following specifications:
* The CDACS will communicate wirelessly with the pit
* The CDACS will feature a Wireless Serial Interface for receiving the command to initiate a Manual Override
* The CDACS will actuate either two or three servo motors, in order to full rule

# §4 System Requirements
## §4.1 CDA subsystem requirements
  - The CDA will feature an Arduino Nano, powered by an ATmega328p.
  - The ATmega328p will be responsible for all onboard computations and handling of CDA code execution
  - The Nano will handle all General Purpose IO (GPIO), Analog to Digital Conversion (ADC), reading of sensors (via GPIO pins), and actuation of control surfaces (via GPIO/ADC pins)
  - The Nano will be connected via GPIO to any number of Voltage Regulators that will manage the power for any number of Servo motors, which will be responsible for actuating the control surfaces of the CDA.
  - The Nano will be connected to an XBee Wireless communications shield
  - The XBee Wireless communications shield will be responsible for communicating with both the PA, and with the Pit crew.
  - The XBee Wireless communications shield will be responsible for receiving input from the pits
  - The Nano will be connected to a GPS Module
  - The GPS Module will provide the Nano will real-time (sub .5Hz) data concerning the CDA's X,Y,Z coordinates, Altitude, Heading, Speed, and orientation
  - The Nano will be connected to an Accelerometer/Gyroscope Module
  - The Accelerometer/Gyroscope module will provide the Nano with real-time (Sub 0.5Hz) data concerning the CDA's Pitch, Yaw, Roll, X acceleration, Y acceleration, and Z acceleration.
  - These data points will be used to generate a flight path that will guide the CDA from its current position to the goal zone.

[SAERulesAndRegulationsDocument]: https://github.com/CatLoverKid/LMU-SAEAero/blob/master/SAE_Aero_Design_Rules_2019.pdf
