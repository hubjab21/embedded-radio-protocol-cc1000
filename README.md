# Embedded Radio Protocol (CC1000)

Implementation of a custom radio communication protocol based on the **BSKS-P specification**, designed for embedded systems using low-power RF transceivers (e.g. CC1000).

---

## Project Overview

This project implements a **packet-based radio communication protocol** developed for laboratory classes in:

**Wireless Control and Sensor Networks**

The protocol enables reliable wireless communication between embedded nodes using:

- FSK modulation
- UART-based data framing
- custom packet structure
- CRC-based error detection

---

## Protocol Description

The protocol (BSKS-P) is designed for:

- star network topology
- time-based channel access (TDMA)
- optional frequency hopping (FH)
- variable-length packets

Transmission is performed using **UART 8N1 framing** over an RF channel.

---

## Packet Structure

Each transmitted packet consists of:

| Field                   | Description                                           |
| ----------------------- | ----------------------------------------------------- |
| **Preamble**            | Sequence of `0x55` bytes (min. 6) for synchronization |
| **Sync Word**           | `0xFF` – UART synchronization                         |
| **Start Marker**        | `0x3C 0x3C` – beginning of packet                     |
| **Source Address**      | Sender ID                                             |
| **Destination Address** | Receiver ID (`0xFF` = broadcast)                      |
| **Length**              | Size of data field                                    |
| **Data**                | Payload (0–40 bytes)                                  |
| **CRC (Control Field)** | Error detection (CRC-CCITT, 16-bit)                   |

---

## CRC Error Detection (CRC-CCITT)

To ensure data integrity, each packet includes a **16-bit CRC checksum**.

### Algorithm

- CRC type: **CRC-CCITT**
- Initial value: `0xFFFF`
- Computed over:

  - source address
  - destination address
  - data length
  - data payload

### Example Implementation (C)

```c
static uint16_t UpdateCRC(uint8_t byte, uint16_t crc)
{
    byte ^= (uint8_t)(crc & 0x00ff);
    byte ^= (uint8_t)(byte << 4);
    return ((((uint16_t)byte << 8) | (uint8_t)(crc >> 8)) ^
            (uint8_t)(byte >> 4) ^
            ((uint16_t)byte << 3));
}
```

### Usage

#### Transmitter:

1. Initialize:

   ```c
   uint16_t crc = 0xFFFF;
   ```
2. Update for each byte:

   ```c
   crc = UpdateCRC(byte, crc);
   ```
3. Append CRC (2 bytes) to packet

#### Receiver:

1. Recalculate CRC
2. Compare with received value
3. If mismatch → discard packet

---

## Hardware Layer

The protocol is designed for RF transceivers supporting:

- **FSK modulation**
- bitrate: **9600 bps**
- UART communication

Example platform:

- CC1000 radio module
- STM32 microcontroller

---

## - Features

- custom embedded communication protocol
- packet-based transmission
- error detection using CRC
- modular design
- compatible with different RF transceivers

---

## Possible Improvements

- full TDMA scheduler implementation
- frequency hopping support
- retransmission mechanism (ARQ)
- packet acknowledgment system
- better debugging tools (logging)

---

## Project Structure

- `main.c` – main application logic
- protocol implementation files
- configuration files

---

## Academic Context

AGH University of Science and Technology

This project was developed as part of the course:

**Wireless Control and Sensor Networks**

The goal was to implement a low-level communication protocol for embedded wireless systems based on a given specification.

---

## Author

Hubert Jabłoński

