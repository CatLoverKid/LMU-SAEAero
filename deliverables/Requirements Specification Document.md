Requirements Specification Document
======
## LMU SAE Aero Team, 2019<br>Telemetry and Control System<br>Anthony Keba

<br><br><br>

Table of Contents
------
###  1 . . . [Scope](#1-scope)
###### 1.1 . . [Identification](#11-identification)
###### 1.2 . . [System Overview](#12-system-overview)
###### 1.3 . . [Document Overview](#13-document-overview)
###  2 . . . [Relavent and Applicable Documents](#2-applicable-documents)
###### 2.1 . . [SAE Rules and Regulations](#21-sae-rules-and-regulations)
###  3 . . . [Subsystems Breakdown](#3-subsystems-breakdown)
###  4 . . . [Computing Requirements by Subsystem](#4-computing-requirements-by-subsystem)

<br><br><br>

# §1 Scope
## §1.1 Identification
This Software Requirements Specification (SRS) Documents the requirements for the The LMU SAE Aero Team 2019 Telemetry and Control System, called the Telemetry and Control System (TCS). The document will provide an overview for all required technical and functional requirements for the TCS, along with links to any auxiliary sources for hardware specifications.
<br>
## §1.2 System Overview
The Telemetry and Control System is a multi-platform set of software suites that collectively fulfill the requirements of the [RULES DOCUMENT][SAERulesAndRegulationsDocument]. These programs, in conjunction, will provide the team with telemetry data, fly sub-crafts, and provide wireless communications with the pit crew. The suite has been broken down into several parts, as follows:
### §1.2.1 Primary Aircraft (PA)
The Primary Aircraft (PA) is a manually and remotely-controlled aircraft that will be responsible for the following:
* Delivering all payloads to the drop site
* Flying from/to the landing strip
* communicating wirelessly with the pit crew in order to relay telemetry data

The requirements for the PA software suite, known as the "Digital Acquisition System" (DAS) are as follows:
* The DAS will continually read the craft's altitude
* The DAS will wirelessly transmit the altitude of the craft to the pit crew for scoring purposes
* The DAS will NOT use the same 2.4GHz channel as the PA's control systems
* The DAS will also record the current state of all payloads, in the form of 'primed', and 'released'
* The DAS will be capable of time syncing payload drops and altitude.


### §1.2.2 Colonist Delivery Aircraft (CDA)
The Colonist Deliver Aircraft (CDA) is an autonomously controlled aircraft that is responsible for delivering the 'colonists' (ping-pong balls) from the PA to the landing site (as outlined in section 8.6 of the [RULES DOCUMENT][SAERulesAndRegulationsDocument]). The requirements for this craft's software are as follows:
* The CDA will deliver all colonists to the landing zone
* The CDA will operate autonomously at all times, unless in Manual Override (described below)
* The CDA will have an alternate mode of operation to be used in case of emergencies, known as "Manual Override"
* While in Manual Override, the CDA will pitch fully up immediately

<br>
## §1.3 Document Overview

# §2 Applicable Documents
## §2.1 SAE Rules and Regulations



[SAERulesAndRegulationsDocument]: https://github.com/CatLoverKid/LMU-SAEAero/blob/master/SAE_Aero_Design_Rules_2019.pdf


The Primary Aircraft will feature several Telemetry and Control systems. Namely, Control of the craft will be administered through a commercially available, off-the-shelf, flight controller.  The nature of this controller will be determined at a later time, by the Electrical Engineering team. The requirements regarding the flight controller can be found in §2.6 of the [RULES DOCUMENT][SAERulesAndRegulationsDocument].
<br>
Telemetry onboard the PA will be handled by a Raspberry Pi Zero, which is powered by a small Lithium-Polymer Battery Pack. Telemetry data will be collected from various sensors located around the craft. This data will be filtered, analyzed, and realized on the Raspberry Pi Zero, and then any data that is required will be spent via a 2.4 GHz LoRA antenna to the pit crew.
<b><br>*NEED TABLE EXPLAINING WHAT DATA NEEDS TO BE BEAMED DOWN*</b>
