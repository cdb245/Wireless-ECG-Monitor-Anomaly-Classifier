# Wireless ECG Monitor and Anomaly Classifier

## Description
This project aims to develop a hardware and software pipeline for acquiring, logging and classifying human ECG data. The signals are captured via an ECG sensor, transmitted wirelessly over serial and then classified by a machine learning model.

## Visuals
* aggiungere foto dell'hardware e dei segnali ottenuti*

## Hardware Requirements
* **Microcontroller:** Arduino Nano (ATmega328P)
* **Sensor:** AD8232 Heart Rate Monitor
* **Wireless Transceiver:** *aggiornare*
* *aggiungere specifiche sulla comunicazione: voltaggi, alimentazione, etc...*

## Software Architecture & Setup
The project is divided into four phases:

1. **Data acquisition (Sensor -> Arduino)**: *da aggiornare con la corretta frequenza di campionamento del segnale*
2. **Wireless transmission (Arduino -> PC)**: the data acquired via the sensor is moved from the NANO to the bluetooth device and to the PC via serial communication
3. **Data logging (PC -> CSV)**: a C script that opens the virtual port, reads the incoming bytes and formats them into a static **.csv** file.
4. **Machine learning classification (CSV->Model)** Machine learning environment for pattern recognition of cardiac anomalies.

## Usage
*da aggiornare insieme all'andamento del progetto*

## Roadmap
- [ ] Phase 1: Hardware validation and wired USB data logging.
- [ ] Phase 2: Bluetooth bridge implementation.
- [ ] Phase 3: Machine Learning dataset generation and model training.
- [ ] Target Completion: October 2026.

## Authors and Acknowledgment
//
