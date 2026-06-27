# Wireless ECG Monitor and Anomaly Classifier

## Description
This project aims to develop a hardware and software pipeline for acquiring, logging and classifying human ECG data. The signals are captured via an ECG sensor, transmitted wirelessly over serial and then classified by a machine learning model.

## Safety warnings
This DIY build does not conform to IEC 60601 medical safety standards, to ensure that the person attached to the electrodes is safe he Arduino setup must **only** be powered by batteries.

Hardware Fail-Safes: The AD8232 features an internal input impedance of 10 gigaOhm. In the event of a chip failure, physical 180 kΩ resistors placed in series with the electrodes act as a physical fail-safe, bottlenecking any potential fault current to microAmpere levels (well below the threshold of human sensation).

<figure>
  <img width="362" height="297" alt="image" src="https://github.com/user-attachments/assets/aeb2b16b-1b4b-490c-b42a-8442be13b843" ">
  <figcaption>Source: AD8232 datasheet</figcaption>
</figure>

## Visuals
* aggiungere foto dell'hardware e dei segnali ottenuti*


## Hardware Requirements
* **Microcontroller:** Arduino Nano (ATmega328P)
* **Sensor:** AD8232 Heart Rate Monitor
* **Wireless Transceiver:** *aggiornare*

## Software Architecture and Setup
The project is divided into four phases:

1. **Data acquisition (Sensor -> Arduino)**: The optimal sampling frequency is 250Hz (src: https://pmc.ncbi.nlm.nih.gov/articles/PMC6085204/), this means one sample every 4ms (T=1/f=1/250 s = 0.004s)
2. **Wireless transmission (Arduino -> PC)**: the data acquired via the sensor is moved from the NANO to the bluetooth device and to the PC via serial communication
3. **Data logging (PC -> CSV)**: a C script that opens the virtual port, reads the incoming bytes and formats them into a static **.csv** file.
4. **Machine learning classification (CSV->Model)** Machine learning environment for pattern recognition of cardiac anomalies.

## Usage
*da aggiornare insieme all'andamento del progetto*

## Roadmap
- [ ] Phase 1: Hardware validation and wired USB data logging.
- [ ] Phase 2: Bluetooth bridge implementation.
- [ ] Phase 3: Machine Learning dataset generation and model training.
- [ ] Target Completion: first week of October 2026.

## Authors and Acknowledgment
//
