// Keyglove controller source code - KGAPI "bluetooth" protocol command parser implementation
// 2015-07-03 by Jeff Rowberg <jeff@rowberg.net>

/*
================================================================================
Keyglove source code is placed under the MIT license
Copyright (c) 2015 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

================================================================================
*/

/**
 * @file support_protocol_bluetooth.cpp
 * @brief KGAPI "bluetooth" protocol command parser implementation
 * @author Jeff Rowberg
 * @date 2015-07-03
 *
 * This file implements subsystem-specific command processing functions for the
 * "bluetooth" part of the KGAPI protocol.
 *
 * This file is autogenerated. Normally it is not necessary to edit this file.
 */

#include "keyglove.h"
#include "support_bluetooth.h"
#include "support_protocol.h"
#include "support_protocol_bluetooth.h"

/**
 * @brief Command processing routine for "bluetooth" packet class
 * @param[in] rxPacket Incoming KGAPI packet buffer
 * @return Protocol error, if any (0 for success)
 * @see protocol_parse()
 * @see KGAPI command: kg_cmd_bluetooth_get_mode()
 * @see KGAPI command: kg_cmd_bluetooth_set_mode()
 * @see KGAPI command: kg_cmd_bluetooth_reset()
 * @see KGAPI command: kg_cmd_bluetooth_get_mac()
 * @see KGAPI command: kg_cmd_bluetooth_get_pairings()
 * @see KGAPI command: kg_cmd_bluetooth_discover()
 * @see KGAPI command: kg_cmd_bluetooth_pair()
 * @see KGAPI command: kg_cmd_bluetooth_delete_pairing()
 * @see KGAPI command: kg_cmd_bluetooth_clear_pairings()
 * @see KGAPI command: kg_cmd_bluetooth_get_connections()
 * @see KGAPI command: kg_cmd_bluetooth_connect()
 * @see KGAPI command: kg_cmd_bluetooth_disconnect()
 */
uint8_t process_protocol_command_bluetooth(uint8_t *rxPacket) {
    // check for valid command IDs
    uint8_t protocol_error = 0;
    switch (rxPacket[3]) {
        case KG_PACKET_ID_CMD_BLUETOOTH_GET_MODE: // 0x01
            // bluetooth_get_mode()(uint16_t result, uint8_t mode)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t mode;
                uint16_t result = kg_cmd_bluetooth_get_mode(&mode);
        
                // build response
                uint8_t payload[3] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF), mode };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 3, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_BLUETOOTH_SET_MODE: // 0x02
            // bluetooth_set_mode(uint8_t mode)(uint16_t result)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_bluetooth_set_mode(rxPacket[4]);
        
                // build response
                uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_BLUETOOTH_RESET: // 0x03
            // bluetooth_reset()(uint16_t result)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_bluetooth_reset();
        
                // build response
                uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_BLUETOOTH_GET_MAC: // 0x04
            // bluetooth_get_mac()(uint16_t result, macaddr_t address)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t address[6];
                uint16_t result = kg_cmd_bluetooth_get_mac(address);
        
                // build response
                uint8_t payload[8] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF), 0,0,0,0,0,0 };
                memcpy(payload + 2, address, 6);
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 8, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_BLUETOOTH_GET_PAIRINGS: // 0x05
            // bluetooth_get_pairings()(uint16_t result, uint8_t count)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t count;
                uint16_t result = kg_cmd_bluetooth_get_pairings(&count);
        
                // build response
                uint8_t payload[3] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF), count };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 3, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_BLUETOOTH_DISCOVER: // 0x06
            // bluetooth_discover(uint8_t duration)(uint16_t result)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_bluetooth_discover(rxPacket[4]);
        
                // build response
                uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_BLUETOOTH_PAIR: // 0x07
            // bluetooth_pair(macaddr_t address)(uint16_t result)
            // parameters = 6 bytes
            if (rxPacket[1] != 6) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_bluetooth_pair(rxPacket + 4);
        
                // build response
                uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_BLUETOOTH_DELETE_PAIRING: // 0x08
            // bluetooth_delete_pairing(uint8_t pairing)(uint16_t result)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_bluetooth_delete_pairing(rxPacket[4]);
        
                // build response
                uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_BLUETOOTH_CLEAR_PAIRINGS: // 0x09
            // bluetooth_clear_pairings()(uint16_t result)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_bluetooth_clear_pairings();
        
                // build response
                uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_BLUETOOTH_GET_CONNECTIONS: // 0x0A
            // bluetooth_get_connections()(uint16_t result, uint8_t count)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t count;
                uint16_t result = kg_cmd_bluetooth_get_connections(&count);
        
                // build response
                uint8_t payload[3] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF), count };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 3, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_BLUETOOTH_CONNECT: // 0x0B
            // bluetooth_connect(uint8_t pairing, uint8_t profile)(uint16_t result)
            // parameters = 2 bytes
            if (rxPacket[1] != 2) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_bluetooth_connect(rxPacket[4], rxPacket[5]);
        
                // build response
                uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_BLUETOOTH_DISCONNECT: // 0x0C
            // bluetooth_disconnect(uint8_t handle)(uint16_t result)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_bluetooth_disconnect(rxPacket[4]);
        
                // build response
                uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        default:
            protocol_error = KG_PROTOCOL_ERROR_INVALID_COMMAND;
    }
    return protocol_error;
}

/* ============================= */
/* KGAPI COMMAND IMPLEMENTATIONS */
/* ============================= */

/**
 * @brief Get current mode for Bluetooth subsystem
 * @param[out] mode Current Bluetooth mode
 * @return Result code (0=success)
 */
uint16_t kg_cmd_bluetooth_get_mode(uint8_t *mode) {
    if (interfaceBT2Ready) {
        *mode = bluetoothMode;
        return 0; // success
    } else {
        *mode = 0xFF;
        return KG_BLUETOOTH_ERROR_INTERFACE_NOT_READY;
    }
}

/**
 * @brief Set new mode for Bluetooth subsystem
 * @param[in] mode New Bluetooth mode to set
 * @return Result code (0=success)
 */
uint16_t kg_cmd_bluetooth_set_mode(uint8_t mode) {
    char cmdClose[] = "CLOSE 00";

    // validate mode
    if (mode > KG_BLUETOOTH_MODE_MAX) {
        return KG_PROTOCOL_ERROR_PARAMETER_RANGE;
    } else {
        if (interfaceBT2Ready) {
            // update mode if interface is ready and mode is actually different
            if (mode != bluetoothMode) {
                // handle appropriate reconfiguration due to mode switch if interface is ready
                // (if it isn't ready, this will happen automatically based on current mode setting when it becomes ready)
                iwrap_autocall_target = 0;
                switch (mode) {
                    case KG_BLUETOOTH_MODE_DISABLED:
                        // become invisible
                        iwrap_send_command("SET BT PAGE 0", iwrap_mode);
                        iwrap_page_mode = 0;
                        
                        // close any open links
                        for (uint8_t i = 0; i < 16; i++) {
                            if ((bluetoothActiveLinkMask & (1 << i)) != 0) {
                                if (i > 9) {
                                    cmdClose[6] = '1';
                                    cmdClose[7] = i + 38;
                                } else {
                                    cmdClose[6] = i + 48;
                                    cmdClose[7] = 0;
                                }
                                iwrap_send_command(cmdClose, iwrap_mode);
                            }
                        }
                        break;
                        
                    case KG_BLUETOOTH_MODE_VISIBLE:
                        // set discoverable/connectable regardless
                        if (iwrap_page_mode != 3) {
                            iwrap_send_command("SET BT PAGE 3", iwrap_mode);
                            iwrap_page_mode = 3;
                        }
                        break;
                        
                    case KG_BLUETOOTH_MODE_AUTOCALL:
                        // set autocall target to 1 device
                        iwrap_autocall_target = 1;
                        
                        // try (re)connection instantly if possible
                        bluetoothTock = keygloveTock - 10;
                        
                        // ...fall through ON PURPOSE!

                    case KG_BLUETOOTH_MODE_MANUAL:
                        if (iwrap_pairings > 0) {
                            // not connected, but paired, so default to non-discoverable/connectable
                            if (iwrap_page_mode != 2) {
                                iwrap_send_command("SET BT PAGE 2", iwrap_mode);
                                iwrap_page_mode = 2;
                            }
                        } else {
                            // not connected or paired, so default to discoverable/connectable
                            if (iwrap_page_mode != 4) {
                                iwrap_send_command("SET BT PAGE 4", iwrap_mode);
                                iwrap_page_mode = 4;
                            }
                        }
                        break;
                }
                bluetoothMode = (bluetooth_mode_t)mode;
            }

            // send kg_evt_bluetooth_mode packet (if we aren't setting it from an API command)
            if (!inBinPacket) {
                uint8_t payload[1] = { bluetoothMode };
                skipPacket = 0;
                if (kg_evt_bluetooth_mode) skipPacket = kg_evt_bluetooth_mode(payload[0]);
                if (!skipPacket) send_keyglove_packet(KG_PACKET_TYPE_EVENT, 1, KG_PACKET_CLASS_BLUETOOTH, KG_PACKET_ID_EVT_BLUETOOTH_MODE, payload);
            }
        } else {
            return KG_BLUETOOTH_ERROR_INTERFACE_NOT_READY;
        }
    }

    return 0; // success
}

/**
 * @brief Reset Bluetooth subsystem
 * @return Result code (0=success)
 */
uint16_t kg_cmd_bluetooth_reset() {
    if (interfaceBT2Ready) {
        interfaceBT2Ready = false;
        iwrap_initialized = 0;
        
        // send RESET command
        iwrap_send_command("RESET", iwrap_mode);
        return 0; // success
    } else {
        return KG_BLUETOOTH_ERROR_INTERFACE_NOT_READY;
    }
}

/**
 * @brief Get local Bluetooth MAC address
 * @param[out] address Local six-byte Bluetooth MAC address
 * @return Result code (0=success)
 */
uint16_t kg_cmd_bluetooth_get_mac(uint8_t *address) {
    if (interfaceBT2Ready) {
        address[0] = iwrap_module_mac.address[5]; // little-endian byte order
        address[1] = iwrap_module_mac.address[4];
        address[2] = iwrap_module_mac.address[3];
        address[3] = iwrap_module_mac.address[2];
        address[4] = iwrap_module_mac.address[1];
        address[5] = iwrap_module_mac.address[0];
        return 0; // success
    } else {
        return KG_BLUETOOTH_ERROR_INTERFACE_NOT_READY;
    }
}

/**
 * @brief Get a list of all paired devices
 * @param[out] count Number of paired devices
 * @return Result code (0=success)
 */
uint16_t kg_cmd_bluetooth_get_pairings(uint8_t *count) {
    if (interfaceBT2Ready) {
        *count = iwrap_pairings;
                
        // sending pairing entry events
        uint8_t payload[18];
        for (uint8_t i = 0; i < iwrap_pairings; i++) {
            if (iwrap_connection_map[i]) {
                // build event (uint8_t pairing, macaddr_t address, uint8_t priority, uint8_t profiles_supported, uint8_t profiles_active, uint8_t[] handle_list)
                payload[0] = i;    // pairing index
                payload[1] = iwrap_connection_map[i] -> mac.address[5];
                payload[2] = iwrap_connection_map[i] -> mac.address[4];
                payload[3] = iwrap_connection_map[i] -> mac.address[3];
                payload[4] = iwrap_connection_map[i] -> mac.address[2];
                payload[5] = iwrap_connection_map[i] -> mac.address[1];
                payload[6] = iwrap_connection_map[i] -> mac.address[0];
                payload[7] = iwrap_connection_map[i] -> priority;
                payload[8] = iwrap_connection_map[i] -> profiles_supported;
                payload[9] = iwrap_connection_map[i] -> profiles_active;
                payload[10] = 0;
                for (uint8_t j = 0; j < 6; j++) {
                    if (payload[9] & (1 << j)) {
                        uint8_t v;
                        payload[10]++;
                        if (j == 0) v = iwrap_connection_map[i] -> link_hid_control;
                        else if (j == 1) v = iwrap_connection_map[i] -> link_hid_interrupt;
                        else if (j == 2) v = iwrap_connection_map[i] -> link_spp;
                        else if (j == 3) v = iwrap_connection_map[i] -> link_iap;
                        else if (j == 4) v = iwrap_connection_map[i] -> link_hfp;
                        else if (j == 5) v = iwrap_connection_map[i] -> link_avrcp;
                        payload[10 + payload[10]] = v;
                    }
                }

                // queue event
                skipPacket = 0;
                if (kg_evt_bluetooth_pairing_status) skipPacket = kg_evt_bluetooth_pairing_status(payload[0], payload + 1, payload[7], payload[8], payload[9], payload[10], payload + 11);
                if (!skipPacket) queue_keyglove_packet(KG_PACKET_TYPE_EVENT, 11 + payload[10], KG_PACKET_CLASS_BLUETOOTH, KG_PACKET_ID_EVT_BLUETOOTH_PAIRING_STATUS, payload);
            } else {
                // this should NEVER happen, but if it does, I want to know
                return KG_PROTOCOL_ERROR_NULL_POINTER;
            }
        }
        return 0; // success
    } else {
        return KG_BLUETOOTH_ERROR_INTERFACE_NOT_READY;
    }
}

/**
 * @brief Perform Bluetooth inquiry to locate nearby devices
 * @param[in] duration Number of seconds to run discovery process
 * @return Result code (0=success)
 */
uint16_t kg_cmd_bluetooth_discover(uint8_t duration) {
    if (interfaceBT2Ready) {
        // validate duration
        if (duration < 5 || duration > 30) {
            return KG_PROTOCOL_ERROR_PARAMETER_RANGE;
        }

        // check for other pending operations
        if (iwrap_state == IWRAP_STATE_PENDING_CALL || iwrap_state == IWRAP_STATE_PENDING_INQUIRY || iwrap_state == IWRAP_STATE_PENDING_PAIR) {
            // can't initiate an outgoing inquiry when there is another pending BT radio operation
            return KG_BLUETOOTH_ERROR_INTERFACE_BUSY;
        } else {
            char cmd[] = "INQUIRY 00 NAME";
            if (duration < 10) {
                cmd[9] = duration + 0x30;
            } else {
                cmd[8] = ((duration / 10) % 10) + 0x30;
                cmd[9] = (duration % 10) + 0x30;
            }
            iwrap_send_command(cmd, iwrap_mode);
            return 0; // success
        }
    } else {
        return KG_BLUETOOTH_ERROR_INTERFACE_NOT_READY;
    }
}

/**
 * @brief Initiate pairing request to remote device
 * @param[in] address Six-byte Bluetooth MAC address of remote device to pair with
 * @return Result code (0=success)
 */
uint16_t kg_cmd_bluetooth_pair(uint8_t *address) {
    if (interfaceBT2Ready) {
        // check for other pending operations
        if (iwrap_state == IWRAP_STATE_PENDING_CALL || iwrap_state == IWRAP_STATE_PENDING_INQUIRY || iwrap_state == IWRAP_STATE_PENDING_PAIR) {
            // can't initiate an outgoing pairing request when there is another pending BT radio operation
            return KG_BLUETOOTH_ERROR_INTERFACE_BUSY;
        } else {
            char cmd[] = "PAIR 00:00:00:00:00:00";
            char *cptr = cmd + 5;
            iwrap_bintohexstr((uint8_t *)(address), 6, &cptr, ':', 0);
            iwrap_send_command(cmd, iwrap_mode);
            iwrap_state = IWRAP_STATE_PENDING_PAIR;
            return 0; // success
        }
    } else {
        return KG_BLUETOOTH_ERROR_INTERFACE_NOT_READY;
    }
}

/**
 * @brief Remove a specific pairing entry
 * @param[in] pairing Index of pairing to delete
 * @return Result code (0=success)
 */
uint16_t kg_cmd_bluetooth_delete_pairing(uint8_t pairing) {
    if (interfaceBT2Ready) {
        // validate pairing index
        if (pairing >= iwrap_pairings) {
            return KG_PROTOCOL_ERROR_PARAMETER_RANGE;
        }
        if (iwrap_connection_map[pairing] == 0) {
            // this should NEVER happen, but if it does, I want to know
            return KG_PROTOCOL_ERROR_NULL_POINTER;
        }
        char cmd[] = "SET BT PAIR 00:00:00:00:00:00";
        char *cptr = cmd + 12;
        iwrap_bintohexstr((uint8_t *)(iwrap_connection_map[pairing] -> mac.address), 6, &cptr, ':', 0);
        iwrap_send_command(cmd, iwrap_mode);

        // close any open links for this pairing entry
        char cmdClose[] = "CLOSE 00";
        for (uint8_t i = 0; i < 16; i++) {
            if ((bluetoothActiveLinkMask & (1 << i)) != 0) {
                if (find_pairing_from_link_id(i) == pairing) {
                    if (i > 9) {
                        cmdClose[6] = '1';
                        cmdClose[7] = i + 38;
                    } else {
                        cmdClose[6] = i + 48;
                        cmdClose[7] = 0;
                    }
                    iwrap_send_command(cmdClose, iwrap_mode);
                }
            }
        }

        // free this entry and shift any below it up one position
        free(iwrap_connection_map[pairing]);
        iwrap_pairings--;
        for (uint8_t i = pairing; i < iwrap_pairings; i++) {
            iwrap_connection_map[i] = iwrap_connection_map[i + 1];
        }
        iwrap_connection_map[iwrap_pairings] = 0;
        
        // change Bluetooth page mode if we just deleted the last pairing
        if (iwrap_pairings == 0 && (bluetoothMode == KG_BLUETOOTH_MODE_MANUAL || bluetoothMode == KG_BLUETOOTH_MODE_AUTOCALL)) {
            // not connected or paired, so default to discoverable/connectable
            if (iwrap_page_mode != 4) {
                iwrap_send_command("SET BT PAGE 4", iwrap_mode);
                iwrap_page_mode = 4;
            }
        }

        // adjust active device indexes if necessary
        if (bluetoothSPPDeviceIndex >= pairing) bluetoothSPPDeviceIndex--;
        if (bluetoothIAPDeviceIndex >= pairing) bluetoothIAPDeviceIndex--;
        if (bluetoothHIDDeviceIndex >= pairing) bluetoothHIDDeviceIndex--;
        if (bluetoothRawHIDDeviceIndex >= pairing) bluetoothRawHIDDeviceIndex--;
        if (bluetoothHFPDeviceIndex >= pairing) bluetoothHFPDeviceIndex--;
        if (bluetoothAVRCPDeviceIndex >= pairing) bluetoothAVRCPDeviceIndex--;
        
        return 0; // success
    } else {
        return KG_BLUETOOTH_ERROR_INTERFACE_NOT_READY;
    }
}

/**
 * @brief Remove all pairing entries
 * @return Result code (0=success)
 */
uint16_t kg_cmd_bluetooth_clear_pairings() {
    if (interfaceBT2Ready) {
        iwrap_pairings = 0;
        iwrap_send_command("SET BT PAIR *", iwrap_mode);

        // close any open links
        char cmdClose[] = "CLOSE 00";
        for (uint8_t i = 0; i < 16; i++) {
            if ((bluetoothActiveLinkMask & (1 << i)) != 0) {
                if (i > 9) {
                    cmdClose[6] = '1';
                    cmdClose[7] = i + 38;
                } else {
                    cmdClose[6] = i + 48;
                    cmdClose[7] = 0;
                }
                iwrap_send_command(cmdClose, iwrap_mode);
            }
        }

        // change Bluetooth page mode if we are in the right mode
        if (bluetoothMode == KG_BLUETOOTH_MODE_MANUAL || bluetoothMode == KG_BLUETOOTH_MODE_AUTOCALL) {
            // not connected or paired, so default to discoverable/connectable
            if (iwrap_page_mode != 4) {
                iwrap_send_command("SET BT PAGE 4", iwrap_mode);
                iwrap_page_mode = 4;
            }
        }

        return 0; // success
    } else {
        return KG_BLUETOOTH_ERROR_INTERFACE_NOT_READY;
    }
}

/**
 * @brief Get a list of all open or pending connections
 * @param[out] count Number of open or pending connections
 * @return Result code (0=success)
 */
uint16_t kg_cmd_bluetooth_get_connections(uint8_t *count) {
    if (interfaceBT2Ready) {
        *count = iwrap_active_connections;
        
        // queue connection status packets
        uint16_t activeLinks = bluetoothActiveLinkMask;
        uint8_t curId = 0, i;
        uint8_t pairing_index;
        while (activeLinks) {
            // build connection status event payload
            uint8_t payload[10] = { curId, 0, 0, 0, 0, 0, 0, 0, 0, 2 };
            for (i = 0; i < iwrap_pairings; i++) {
                if (iwrap_connection_map[i]) {
                    if (iwrap_connection_map[i] -> link_avrcp == curId) {
                        payload[8] = BLUETOOTH_PROFILE_MASK_AVRCP;
                        break;
                    }
                    if (iwrap_connection_map[i] -> link_hfp == curId) {
                        payload[8] = BLUETOOTH_PROFILE_MASK_HFP;
                        break;
                    }
                    if (iwrap_connection_map[i] -> link_hid_control == curId) {
                        payload[8] = BLUETOOTH_PROFILE_MASK_HID_CONTROL;
                        break;
                    }
                    if (iwrap_connection_map[i] -> link_hid_interrupt == curId) {
                        payload[8] = BLUETOOTH_PROFILE_MASK_HID_INTERRUPT;
                        break;
                    }
                    if (iwrap_connection_map[i] -> link_iap == curId) {
                        payload[8] = BLUETOOTH_PROFILE_MASK_IAP;
                        break;
                    }
                    if (iwrap_connection_map[i] -> link_spp == curId) {
                        payload[8] = BLUETOOTH_PROFILE_MASK_SPP;
                        break;
                    }
                } else {
                    // this should NEVER happen, but if it does, I want to know
                    return KG_PROTOCOL_ERROR_NULL_POINTER;
                }
            }

            if (i == iwrap_pairings) {
                // no link match found, only reason this should happen is if we
                // deleted the pairing without closing the link (which is possible,
                // if this API command is called at exactly the right time);
                memset(payload + 1, 0xFF, 8);
            } else {
                // found a matching paired device
                pairing_index = i;
                payload[1] = iwrap_connection_map[pairing_index] -> mac.address[5]; // little-endian byte order
                payload[2] = iwrap_connection_map[pairing_index] -> mac.address[4];
                payload[3] = iwrap_connection_map[pairing_index] -> mac.address[3];
                payload[4] = iwrap_connection_map[pairing_index] -> mac.address[2];
                payload[5] = iwrap_connection_map[pairing_index] -> mac.address[1];
                payload[6] = iwrap_connection_map[pairing_index] -> mac.address[0];
                payload[7] = pairing_index;
            }

            // queue kg_evt_bluetooth_connection_status(...)
            skipPacket = 0;
            if (kg_evt_bluetooth_connection_status) skipPacket = kg_evt_bluetooth_connection_status(payload[0], payload + 1, payload[7], payload[8], payload[9]);
            if (!skipPacket) queue_keyglove_packet(KG_PACKET_TYPE_EVENT, 10, KG_PACKET_CLASS_BLUETOOTH, KG_PACKET_ID_EVT_BLUETOOTH_CONNECTION_STATUS, payload);

            activeLinks >>= 1;
            curId++;
        }
        return 0; // success
    } else {
        return KG_BLUETOOTH_ERROR_INTERFACE_NOT_READY;
    }
}

/**
 * @brief Attempt to open a connection to a specific paired device using a specific profile
 * @param[in] pairing Index of pairing to use
 * @param[in] profile Profile to use for connection
 * @return Result code (0=success)
 */
uint16_t kg_cmd_bluetooth_connect(uint8_t pairing, uint8_t profile) {
    if (interfaceBT2Ready) {
        // validate pairing index
        if (pairing >= iwrap_pairings) {
            return KG_PROTOCOL_ERROR_PARAMETER_RANGE;
        }
        
        // check for other pending operations
        if (iwrap_state == IWRAP_STATE_PENDING_CALL || iwrap_state == IWRAP_STATE_PENDING_INQUIRY || iwrap_state == IWRAP_STATE_PENDING_PAIR) {
            // can't initiate an outgoing call when there is another pending BT radio operation
            return KG_BLUETOOTH_ERROR_INTERFACE_BUSY;
        } else if (!iwrap_connection_map[pairing]) {
            // this should NEVER happen, but if it does, I want to know
            return KG_PROTOCOL_ERROR_NULL_POINTER;
        } else {
            char cmd[] = "CALL 00:00:00:00:00:00 0011 HID\0\0\0";
            char *cptr = cmd + 5;
            iwrap_bintohexstr((uint8_t *)(iwrap_connection_map[pairing] -> mac.address), 6, &cptr, ':', 0);
            switch (profile) {
                case BLUETOOTH_PROFILE_MASK_AVRCP:
                    cmd[26] = '7'; // 0017
                    cmd[28] = 'A'; // AVRCP
                    cmd[29] = 'V';
                    cmd[30] = 'R';
                    cmd[31] = 'C';
                    cmd[32] = 'P';
                    break;
                case BLUETOOTH_PROFILE_MASK_HFP:
                    cmd[23] = '1'; // 111F
                    cmd[24] = '1';
                    cmd[26] = 'F';
                    cmd[29] = 'F'; // HFP
                    cmd[30] = 'P';
                    break;
                case BLUETOOTH_PROFILE_MASK_IAP:
                    cmd[23] = '*'; // *
                    cmd[24] = ' '; // IAP
                    cmd[25] = 'I'; // IAP
                    cmd[26] = 'A';
                    cmd[27] = 'P';
                    cmd[28] = 0;
                    break;
                case BLUETOOTH_PROFILE_MASK_SPP:
                    cmd[23] = '1'; // 1101
                    cmd[24] = '1';
                    cmd[25] = '0';
                    cmd[28] = 'A'; // RFCOMM
                    cmd[29] = 'V';
                    cmd[30] = 'R';
                    cmd[31] = 'C';
                    cmd[32] = 'P';
                    break;
                //default:
                    // USE HID, LEAVE COMMAND UNCHANGED
                    //break;
            }
            iwrap_send_command(cmd, iwrap_mode);
            return 0; // success
        }
    } else {
        return KG_BLUETOOTH_ERROR_INTERFACE_NOT_READY;
    }
}

/**
 * @brief Close a specific Bluetooth connection
 * @param[in] handle Link ID of connection to close
 * @return Result code (0=success)
 */
uint16_t kg_cmd_bluetooth_disconnect(uint8_t handle) {
    if (interfaceBT2Ready) {
        // validate pairing index
        if (!(bluetoothActiveLinkMask & (1 << handle))) {
            return KG_PROTOCOL_ERROR_PARAMETER_RANGE;
        }

        // send CLOSE command
        char cmdClose[] = "CLOSE 00";
        if (handle > 9) {
            cmdClose[6] = '1';
            cmdClose[7] = handle + 38;
        } else {
            cmdClose[6] = handle + 48;
            cmdClose[7] = 0;
        }
        iwrap_send_command(cmdClose, iwrap_mode);

        return 0; // success
    } else {
        return KG_BLUETOOTH_ERROR_INTERFACE_NOT_READY;
    }
}

/* ==================== */
/* KGAPI EVENT POINTERS */
/* ==================== */

/* 0x01 */ uint8_t (*kg_evt_bluetooth_mode)(uint8_t mode);
/* 0x02 */ uint8_t (*kg_evt_bluetooth_ready)();
/* 0x03 */ uint8_t (*kg_evt_bluetooth_inquiry_response)(uint8_t *address, uint8_t *cod, int8_t rssi, uint8_t status, uint8_t pairing, uint8_t name_len, uint8_t *name_data);
/* 0x04 */ uint8_t (*kg_evt_bluetooth_inquiry_complete)(uint8_t count);
/* 0x05 */ uint8_t (*kg_evt_bluetooth_pairing_status)(uint8_t pairing, uint8_t *address, uint8_t priority, uint8_t profiles_supported, uint8_t profiles_active, uint8_t handle_list_len, uint8_t *handle_list_data);
/* 0x06 */ uint8_t (*kg_evt_bluetooth_pairing_failed)(uint8_t *address);
/* 0x07 */ uint8_t (*kg_evt_bluetooth_pairings_cleared)();
/* 0x08 */ uint8_t (*kg_evt_bluetooth_connection_status)(uint8_t handle, uint8_t *address, uint8_t pairing, uint8_t profile, uint8_t status);
/* 0x09 */ uint8_t (*kg_evt_bluetooth_connection_closed)(uint8_t handle, uint16_t reason);
