#pragma once
#include <cstdint>
#include <array>

#include "error.hpp"

namespace pci {
// PCI configuration space access ports
const uint16_t kConfigAddress = 0x0cf8;
const uint16_t kConfigData = 0x0cfc;

// PCI configuration space access functions
void WriteAddress(uint32_t address);
void WriteData(uint32_t data);
uint32_t ReadData();

// Functions to read specific fields from the PCI configuration space
uint16_t ReadVendorId(uint8_t bus, uint8_t device, uint8_t function);
uint16_t ReadDeviceId(uint8_t bus, uint8_t device, uint8_t function);
uint8_t ReadHeaderType(uint8_t bus, uint8_t device, uint8_t function);
uint32_t ReadClassCode(uint8_t bus, uint8_t device, uint8_t function);
uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function);

// Function to check if a PCI device is a single-function device
bool IsSingleFunctionDevice(uint8_t header_type);

// Structure to represent a PCI device
struct Device {
  uint8_t bus, device, function, header_type;
};

// Global variables to store the list of detected PCI devices and the number of
// devices
inline std::array<Device, 32> devices;
inline int num_device;

// Function to scan all PCI buses and populate the devices array with detected
// devices
Error ScanAllBus();
} 