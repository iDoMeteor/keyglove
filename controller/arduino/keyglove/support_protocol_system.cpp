// Keyglove controller source code - KGAPI "system" protocol command parser implementation
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
 * @file support_protocol_system.cpp
 * @brief KGAPI "system" protocol command parser implementation
 * @author Jeff Rowberg
 * @date 2015-07-03
 *
 * This file implements subsystem-specific command processing functions for the
 * "system" part of the KGAPI protocol.
 *
 * This file is autogenerated. Normally it is not necessary to edit this file.
 */

#include "keyglove.h"
#include "support_board.h"
#include "support_touch.h"
#include "support_protocol.h"
#include "support_protocol_system.h"

/**
 * @brief Command processing routine for "system" packet class
 * @param[in] rxPacket Incoming KGAPI packet buffer
 * @return Protocol error, if any (0 for success)
 * @see protocol_parse()
 * @see KGAPI command: kg_cmd_system_ping()
 * @see KGAPI command: kg_cmd_system_reset()
 * @see KGAPI command: kg_cmd_system_get_info()
 * @see KGAPI command: kg_cmd_system_get_capabilities()
 * @see KGAPI command: kg_cmd_system_get_memory()
 * @see KGAPI command: kg_cmd_system_get_battery_status()
 * @see KGAPI command: kg_cmd_system_set_timer()
 */
uint8_t process_protocol_command_system(uint8_t *rxPacket) {
    // check for valid command IDs
    uint8_t protocol_error = 0;
    switch (rxPacket[3]) {
        case KG_PACKET_ID_CMD_SYSTEM_PING: // 0x01
            // system_ping()(uint32_t uptime)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint32_t uptime;
                /*uint16_t result =*/ kg_cmd_system_ping(&uptime);
        
                // build response
                uint8_t payload[4] = { (uint8_t)(uptime & 0xFF), (uint8_t)((uptime >> 8) & 0xFF), (uint8_t)((uptime >> 16) & 0xFF), (uint8_t)((uptime >> 24) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 4, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_SYSTEM_RESET: // 0x02
            // system_reset(uint8_t mode)(uint16_t result)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_system_reset(rxPacket[4]);
        
                // build and send response if needed
                if (result != 0xFFFF) {
                    // build response
                    uint8_t payload[2] = { (uint8_t)(result & 0xFF), (uint8_t)((result >> 8) & 0xFF) };
        
                    // send response
                    send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
                }
            }
            break;
        
        case KG_PACKET_ID_CMD_SYSTEM_GET_INFO: // 0x03
            // system_get_info()(uint16_t major, uint16_t minor, uint16_t patch, uint16_t protocol, uint32_t timestamp)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t major;
                uint16_t minor;
                uint16_t patch;
                uint16_t protocol;
                uint32_t timestamp;
                /*uint16_t result =*/ kg_cmd_system_get_info(&major, &minor, &patch, &protocol, &timestamp);
        
                // build response
                uint8_t payload[12] = { (uint8_t)(major & 0xFF), (uint8_t)((major >> 8) & 0xFF), (uint8_t)(minor & 0xFF), (uint8_t)((minor >> 8) & 0xFF), (uint8_t)(patch & 0xFF), (uint8_t)((patch >> 8) & 0xFF), (uint8_t)(protocol & 0xFF), (uint8_t)((protocol >> 8) & 0xFF), (uint8_t)(timestamp & 0xFF), (uint8_t)((timestamp >> 8) & 0xFF), (uint8_t)((timestamp >> 16) & 0xFF), (uint8_t)((timestamp >> 24) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 12, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_SYSTEM_GET_CAPABILITIES: // 0x04
            // system_get_capabilities(uint8_t category)(uint16_t count)
            // parameters = 1 byte
            if (rxPacket[1] != 1) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t count;
                /*uint16_t result =*/ kg_cmd_system_get_capabilities(rxPacket[4], &count);
        
                // build response
                uint8_t payload[2] = { (uint8_t)(count & 0xFF), (uint8_t)((count >> 8) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_SYSTEM_GET_MEMORY: // 0x05
            // system_get_memory()(uint32_t free_ram, uint32_t total_ram)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint32_t free_ram;
                uint32_t total_ram;
                /*uint16_t result =*/ kg_cmd_system_get_memory(&free_ram, &total_ram);
        
                // build response
                uint8_t payload[8] = { (uint8_t)(free_ram & 0xFF), (uint8_t)((free_ram >> 8) & 0xFF), (uint8_t)((free_ram >> 16) & 0xFF), (uint8_t)((free_ram >> 24) & 0xFF), (uint8_t)(total_ram & 0xFF), (uint8_t)((total_ram >> 8) & 0xFF), (uint8_t)((total_ram >> 16) & 0xFF), (uint8_t)((total_ram >> 24) & 0xFF) };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 8, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_SYSTEM_GET_BATTERY_STATUS: // 0x06
            // system_get_battery_status()(uint8_t status, uint8_t level)
            // parameters = 0 bytes
            if (rxPacket[1] != 0) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint8_t status;
                uint8_t level;
                /*uint16_t result =*/ kg_cmd_system_get_battery_status(&status, &level);
        
                // build response
                uint8_t payload[2] = { status, level };
        
                // send response
                send_keyglove_packet(KG_PACKET_TYPE_COMMAND, 2, rxPacket[2], rxPacket[3], payload);
            }
            break;
        
        case KG_PACKET_ID_CMD_SYSTEM_SET_TIMER: // 0x07
            // system_set_timer(uint8_t handle, uint16_t interval, uint8_t oneshot)(uint16_t result)
            // parameters = 4 bytes
            if (rxPacket[1] != 4) {
                // incorrect parameter length
                protocol_error = KG_PROTOCOL_ERROR_PARAMETER_LENGTH;
            } else {
                // run command
                uint16_t result = kg_cmd_system_set_timer(rxPacket[4], rxPacket[5] | (rxPacket[6] << 8), rxPacket[7]);
        
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
 * @brief Test communication with Keyglove device and get current runtime
 * @param[out] runtime Number of seconds since last boot/reset
 * @return Result code (0=success)
 */
uint16_t kg_cmd_system_ping(uint32_t *runtime) {
    *runtime = keygloveTock;
    return 0; // success
}

/**
 * @brief Reset Keyglove device
 * @param[in] mode Type of reset to perform
 * @return Result code (0=success)
 */
uint16_t kg_cmd_system_reset(uint8_t mode) {
    // validate type
    if (mode < 1 || mode > 2) {
        return KG_PROTOCOL_ERROR_PARAMETER_RANGE;
    }

    // send response
    uint8_t payload[] = { 0x00, 0x00 };
    send_keyglove_packet(KG_PACKET_TYPE_COMMAND, sizeof(payload), KG_PACKET_CLASS_SYSTEM, KG_PACKET_ID_CMD_SYSTEM_RESET, payload);

    // reboot Keyglove
    systemResetFlags = 0xFF; // reset everything
    reset_keyglove_rx_packet(); // clear packet status
    if (mode == KG_SYSTEM_RESET_MODE_KGONLY) {
        systemResetFlags = 0; // don't reset anything except the main core system
    }
    setup();
    return 0xFFFF; // success, but DON'T send response packet (already done)
}

/**
 * @brief Get firmware build info
 * @param[out] major Firmware major version number
 * @param[out] minor Firmware minor version number
 * @param[out] patch Firmware patch version number
 * @param[out] protocol API protocol version
 * @param[out] timestamp Build timestamp
 * @return Result code (0=success)
 */
uint16_t kg_cmd_system_get_info(uint16_t *major, uint16_t *minor, uint16_t *patch, uint16_t *protocol, uint32_t *timestamp) {
    *major = KG_FIRMWARE_VERSION_MAJOR;
    *minor = KG_FIRMWARE_VERSION_MINOR;
    *patch = KG_FIRMWARE_VERSION_PATCH;
    *protocol = KG_PROTOCOL_VERSION;
    *timestamp = KG_BUILD_TIMESTAMP;
    return 0; // success
}

/**
 * @brief Get capabilities designed into this unit
 * @param[in] category Category of capabilities to report (0x00 for all)
 * @param[out] count Number of capability reports to expect
 * @return Result code (0=success)
 */
uint16_t kg_cmd_system_get_capabilities(uint8_t category, uint16_t *count) {
    *count = 0;
    if (!category || category == KG_CAPABILITY_CATEGORY_PLATFORM) {
        // TLV { 1, 1, KG_BOARD }
        // TLV { 2, 1, KG_HAND }
        // TLV { 3, 1, KG_DUALGLOVE }

        // increment expected report count
        (*count)++;

        uint8_t payload[11];
        payload[0] = KG_CAPABILITY_CATEGORY_PLATFORM;
        payload[1] = 0x09;
        payload[2] = 0x01;
        payload[3] = 0x01;
        payload[4] = KG_BOARD;
        payload[5] = 0x01;
        payload[6] = 0x02;
        payload[7] = KG_HAND;
        payload[8] = 0x01;
        payload[9] = 0x03;
        payload[10] = KG_DUALGLOVE;

        // queue event
        skipPacket = 0;
        if (kg_evt_system_capability) skipPacket = kg_evt_system_capability(payload[0], payload[1], payload + 2);
        if (!skipPacket) queue_keyglove_packet(KG_PACKET_TYPE_EVENT, 11, KG_PACKET_CLASS_SYSTEM, KG_PACKET_ID_EVT_SYSTEM_CAPABILITY, payload);
    }
    if (!category || category == KG_CAPABILITY_CATEGORY_HOSTIF) {
        // TLV { 1, 1, KG_HOSTIF }

        // increment expected report count
        (*count)++;

        uint8_t payload[5];
        payload[0] = KG_CAPABILITY_CATEGORY_HOSTIF;
        payload[1] = 0x03;
        payload[2] = 0x01;
        payload[3] = 0x01;
        payload[4] = KG_HOSTIF;

        // queue event
        skipPacket = 0;
        if (kg_evt_system_capability) skipPacket = kg_evt_system_capability(payload[0], payload[1], payload + 2);
        if (!skipPacket) queue_keyglove_packet(KG_PACKET_TYPE_EVENT, 5, KG_PACKET_CLASS_SYSTEM, KG_PACKET_ID_EVT_SYSTEM_CAPABILITY, payload);
    }
    if (!category || category == KG_CAPABILITY_CATEGORY_FEEDBACK) {
        // TLV { 1, 1, KG_FEEDBACK }

        // increment expected report count
        (*count)++;

        uint8_t payload[5];
        payload[0] = KG_CAPABILITY_CATEGORY_FEEDBACK;
        payload[1] = 0x03;
        payload[2] = 0x01;
        payload[3] = 0x01;
        payload[4] = KG_FEEDBACK;

        // queue event
        skipPacket = 0;
        if (kg_evt_system_capability) skipPacket = kg_evt_system_capability(payload[0], payload[1], payload + 2);
        if (!skipPacket) queue_keyglove_packet(KG_PACKET_TYPE_EVENT, 5, KG_PACKET_CLASS_SYSTEM, KG_PACKET_ID_EVT_SYSTEM_CAPABILITY, payload);
    }
    if (!category || category == KG_CAPABILITY_CATEGORY_TOUCH) {
        // TLV { 1, 1, KG_TOTAL_SENSORS }
        // TLV { 2, KG_BASE_COMBINATIONS*2+1, ... }

        // increment expected report count
        (*count)++;

        uint8_t payload[7 + (KG_BASE_COMBINATIONS * 2)];
        payload[0] = KG_CAPABILITY_CATEGORY_TOUCH;
        payload[1] = 5 + (KG_BASE_COMBINATIONS * 2);
        payload[2] = 0x01;
        payload[3] = 0x01;
        payload[4] = KG_TOTAL_SENSORS;
        payload[5] = 0x02;
        payload[6] = (KG_BASE_COMBINATIONS * 2);

        // queue event
        skipPacket = 0;
        if (kg_evt_system_capability) skipPacket = kg_evt_system_capability(payload[0], payload[1], payload + 2);
        if (!skipPacket) queue_keyglove_packet(KG_PACKET_TYPE_EVENT, 7 + (KG_BASE_COMBINATIONS * 2), KG_PACKET_CLASS_SYSTEM, KG_PACKET_ID_EVT_SYSTEM_CAPABILITY, payload);
    }
    if (!category || category == KG_CAPABILITY_CATEGORY_MOTION) {
        // TLV { 1, 1, KG_MOTION }

        // increment expected report count
        (*count)++;

        uint8_t payload[5];
        payload[0] = KG_CAPABILITY_CATEGORY_MOTION;
        payload[1] = 0x03;
        payload[2] = 0x01;
        payload[3] = 0x01;
        payload[4] = KG_MOTION;

        // queue event
        skipPacket = 0;
        if (kg_evt_system_capability) skipPacket = kg_evt_system_capability(payload[0], payload[1], payload + 2);
        if (!skipPacket) queue_keyglove_packet(KG_PACKET_TYPE_EVENT, 5, KG_PACKET_CLASS_SYSTEM, KG_PACKET_ID_EVT_SYSTEM_CAPABILITY, payload);
    }
    if (!category || category == KG_CAPABILITY_CATEGORY_FLEX) {
        // TLV { 1, 1, KG_FLEX }

        // increment expected report count
        (*count)++;

        uint8_t payload[5];
        payload[0] = KG_CAPABILITY_CATEGORY_FLEX;
        payload[1] = 0x03;
        payload[2] = 0x01;
        payload[3] = 0x01;
        payload[4] = KG_FLEX;

        // queue event
        skipPacket = 0;
        if (kg_evt_system_capability) skipPacket = kg_evt_system_capability(payload[0], payload[1], payload + 2);
        if (!skipPacket) queue_keyglove_packet(KG_PACKET_TYPE_EVENT, 5, KG_PACKET_CLASS_SYSTEM, KG_PACKET_ID_EVT_SYSTEM_CAPABILITY, payload);
    }
    if (!category || category == KG_CAPABILITY_CATEGORY_PRESSURE) {
        // TLV { 1, 1, KG_PRESSURE }

        // increment expected report count
        (*count)++;

        uint8_t payload[5];
        payload[0] = KG_CAPABILITY_CATEGORY_PRESSURE;
        payload[1] = 0x09;
        payload[2] = 0x01;
        payload[3] = 0x01;
        payload[4] = KG_PRESSURE;

        // queue event
        skipPacket = 0;
        if (kg_evt_system_capability) skipPacket = kg_evt_system_capability(payload[0], payload[1], payload + 2);
        if (!skipPacket) queue_keyglove_packet(KG_PACKET_TYPE_EVENT, 5, KG_PACKET_CLASS_SYSTEM, KG_PACKET_ID_EVT_SYSTEM_CAPABILITY, payload);
    }
    return 0; // success
}

/**
 * @brief Get system memory usage
 * @param[out] free_ram Free RAM
 * @param[out] total_ram Total RAM
 * @return Result code (0=success)
 */
uint16_t kg_cmd_system_get_memory(uint32_t *free_ram, uint32_t *total_ram) {
    extern int __heap_start, *__brkval; 
    int v;
    // thanks, Adafruit! https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory
    *free_ram = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
    *total_ram = 8*1024;
    return 0; // success
}

/**
 * @brief Get battery status
 * @param[out] status Battery status
 * @param[out] level Charge level (0-100)
 * @return Result code (0=success)
 */
uint16_t kg_cmd_system_get_battery_status(uint8_t *status, uint8_t *level) {
    *status = keygloveBatteryStatus;
    *level = keygloveBatteryLevel;
    return 0; // success
}

/**
 * @brief Set a timer interval to trigger future behavior
 * @param[in] handle Timer handle (0-7)
 * @param[in] interval Interval (10ms units)
 * @param[in] oneshot Repeating (0) or one-shot (1)
 * @return Result code (0=success)
 */
uint16_t kg_cmd_system_set_timer(uint8_t handle, uint16_t interval, uint8_t oneshot) {
    if (handle > 7) {
        return KG_PROTOCOL_ERROR_PARAMETER_RANGE;
    }
    if (interval == 0) {
        // stop this timer
        keygloveSoftTimers &= ~(1 << handle);
    } else {
        // schedule/reschedule this timer
        keygloveSoftTimers |= (1 << handle);
        if (oneshot) keygloveSoftTimersRepeat &= ~(1 << handle);
        else keygloveSoftTimersRepeat |= (1 << handle);
        keygloveSoftTimerInterval[handle] = interval;
        keygloveSoftTimerSec[handle] = keygloveTock + (interval / 100);
        keygloveSoftTimer10ms[handle] = keygloveTick + (interval % 100);
        if (keygloveSoftTimer10ms[handle] > 99) {
            keygloveSoftTimer10ms[handle] -= 100;
            keygloveSoftTimerSec[handle]++;
        }
    }
    return 0; // success
}

/* ==================== */
/* KGAPI EVENT POINTERS */
/* ==================== */

/* 0x01 */ uint8_t (*kg_evt_system_boot)(uint16_t major, uint16_t minor, uint16_t patch, uint16_t protocol, uint32_t timestamp);
/* 0x02 */ uint8_t (*kg_evt_system_ready)();
/* 0x03 */ uint8_t (*kg_evt_system_error)(uint16_t code);
/* 0x04 */ uint8_t (*kg_evt_system_capability)(uint8_t category, uint8_t record_len, uint8_t *record_data);
/* 0x05 */ uint8_t (*kg_evt_system_battery_status)(uint8_t status, uint8_t level);
/* 0x06 */ uint8_t (*kg_evt_system_timer_tick)(uint8_t handle, uint32_t seconds, uint8_t subticks);
